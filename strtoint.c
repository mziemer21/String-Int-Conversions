/*
 * FILENAME:	strtoint.c
 * AUTHORS:	Michael Gilsdorf	Section 2
 * 		Matthew Ziemer		Section 1
 * DATE:	September 19,2013	
 * DESCRIPTION:	This program reads in a file of strings and outputs them to a new file as integers.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_LENGTH 100

int main (int argc, char *argv[])
{
	/*check for the correct number of arguments*/
	if (argc != 3)
	{
		fprintf(stderr, "usage: strtoint <strFile> <intFile>\n");
		exit(1);
	}

        /*Open string file*/
	char *infile = argv[1];
	FILE *fp = fopen(infile, "r");
	assert(fp != NULL);

	/*Open or create int file*/
	char *outfile = argv[2];
	int fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	assert(fd > -1);

	char line[MAX_LENGTH];
	
	while (fgets(line, MAX_LENGTH, fp))
	{
		int value;
		if (line[0] == '-')
		{
			value = atoi(line+1);
			value = value * -1;
		}
		else
		{
			value = atoi(line);
		}

		int rc = write(fd, &value, sizeof(int));
		assert(rc == sizeof(int));
	}
	
	close(fd);
	fclose(fp);

	return 0;
}
