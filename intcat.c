/*
 * FILENAME:    intcat.c
 * AUTHORS:     Michael Gilsdorf        Section 2
 * 		Matthew Ziemer          Section 1
 * DATE:        September 19,2013
 * DESCRIPTION: This program reads binary numbers from a file and prints it on the screen.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_SIZE 100
#define INT_LENGTH 4

int main (int argc, char *argv[])
{
	 /*check for the correct number of arguments*/
	 if (argc != 2)
	 {
		fprintf(stderr, "usage: intcat <file>\n");
		exit(1);
	 }

	/*Open file*/
	char  *infile = argv[1];
	int fp = open(infile, O_RDONLY);
	if (fp < 0)
	{
		fprintf(stderr, "error: Unable to open file %s.\n", infile);
		exit(1);
	}

	/*Read line from file*/
	int line;
	int *pline;
	pline = &line;
	int linesRead;
	
	linesRead = read(fp, pline, INT_LENGTH);
	
	while (linesRead !=0)
	{

		if (line < 0)
		{
			line = line * -1;
			printf("- %d\n", line);
		}
		else
		{
			printf("%d\n", line);
		}

		linesRead = read(fp, pline, INT_LENGTH);
	}

	close(fp);

	return 0;
}

