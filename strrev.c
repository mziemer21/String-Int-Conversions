/*
 * FILENAME:	strrev.c
 * AUTHORS:	Michael Gilsdorf	Section 2
 * 		Matthew Ziemer		Section 1
 * DATE:	September 19, 2013
 * DESCRIPTION:	This program reads a file of strings, slips their order and writes them to a new file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define MAX_LENGTH 100

/*build stack*/
typedef struct node{
        char *string;
	struct node *next;
} Node;

Node* push(Node *stptr, char *line);
char* pop();

int main (int argc, char *argv[])
{
      int index;
	/*check for the correct number of arguments*/
	if (argc != 3)
	{
		fprintf(stderr, "usage: strrev <originalfile> <newfile>\n");
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

	/*initialize linked list*/
	Node *top;
	top = NULL;

	/*read lines from file*/
	char line[MAX_LENGTH];

        while (fgets(line, MAX_LENGTH, fp))
        {
		/*store line in stack*/
		top = push(top, line);
		assert(top);
	}

	/*open or create output file*/
	char *outfile = argv[2];
	FILE *fo = fopen(outfile, "w");
	if (fo == NULL)
	{
		fclose(fp);
		fprintf(stderr, "error: Unable to open file %s.\n", outfile);
	        exit(1);
	}
	
	/*print values to the output file*/
        index = 0;
	while (top !=NULL)
	{
		fprintf(fo, "%s", pop(&top));
	}

	fclose(fp);
	fclose(fo);

	return 0;
}

/*Adds a new node to the top of the stack*/
Node*  push(Node* stptr, char *line)
{
	/*allocate memory for the new node*/
	Node *newNode = (Node *)malloc(sizeof(Node));
	newNode->string = malloc(sizeof(100));
	/*copy the line into the memory saved for the newnode*/
	strcpy(newNode->string, line);

	/*update the pointer nodes for the pop*/
	if (stptr == NULL)
	{
		newNode->next = NULL;
		stptr = newNode;
	}
	else
	{
		newNode->next = stptr;
		stptr = newNode;
	}
	
	return stptr;
}

/*Removes the top node from the stack*/
char* pop(Node** stptr)
{
	if (*stptr == NULL)
	{
		return NULL;
        }	

	char *rptr = (*stptr)->string;
	*stptr = (*stptr)->next;

	return rptr;
}
