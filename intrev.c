/*
 * FILENAME:	intrev.c
 * AUTHORS:	Matthew Ziemer		Section 1
 *  		Michael Gilsdorf	Section 2
 * Date:	September 19, 2013
 * Description: Reads a file of ints, flips their order and writes them to a 
 * 		new file.
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
	if(argc != 3)
	{
		fprintf(stderr, "usage: intrev <originalfile> <newfile>\n");
		exit(1);
	}

	/*Open file*/
	char *infile = argv[1];
	int fp = open(infile, O_RDONLY);
	if(fp < 0)
	{
		fprintf(stderr, "error: Unable to open file %s.\n", infile);
	        exit(1);
	}
	
	/*Read line from file into array*/
	struct stat *fs = malloc(sizeof(struct stat));
	assert(fstat(fp, fs) ==0);

	int *p = malloc(fs->st_size);
	int linesRead;

	linesRead = read(fp, p, INT_LENGTH);
	
	

	int num = 1;
	/* read infile to array*/
	while (linesRead !=0)
	{
		linesRead = read(fp, p+num, INT_LENGTH);
		num++;
	}
	
	/*backup num to last integer*/
	num = num-2;

	/* creates output file*/
	char *outfile = argv[2];
	int fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	assert(fd > -1);

	/* print to output file in reverse order*/
	while(num >= 0)
	{
		int rc = write(fd, p+num, sizeof(int));
		assert(rc == sizeof(int));
		num--;
	}

	close(fd);
	close(fp);

	return 0;
}
