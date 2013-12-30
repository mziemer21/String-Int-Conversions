/*
 * FILENAME:     strcat.c
 * AUTHORS:      Michael Gilsdorf	Section 2
 *		 Matt Ziemer		Section 1
 * DATE:         September 19, 2013
 * DESCRIPTION:  This program reads text from a file and prints it on the screen.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_LENGTH 100

int main (int argc, char *argv[])
{
	/*check for the correct number of arguments*/
	if (argc != 2)
	{
		fprintf(stderr, "usage: strcat <file>\n");
		exit(1);
	}
	
	/*Open file*/
	char *infile = argv[1];
	FILE *fp = fopen(infile, "r");
	if (fp == NULL)
	{
		fprintf(stderr, "error: Unable to open file %s.\n", infile);
		exit(1);
        }


	/*Read lines from file*/
	char line[MAX_LENGTH];

	while (fgets(line, MAX_LENGTH, fp))
	{
		/*print line*/
		printf("%s",line);
	}

	/*close file*/
	fclose(fp);

	return 0;
}
