/*
* FILENAME: strgen.c
* DESCRIPTION: This program will create a file of random numbers.
*
*/
#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

long int random(void);
void srandom(unsigned int seed);

/* The first arg is the file name to write to.
*  The second arg is how many numbers whould be generated.
* The third arg is  is a random number seed. By changing this value, 
* you can put a different set of randomly-generated numbers into the file.
*/
int main(int argc, char *argv[])
{
    if (argc != 4) {
	fprintf(stderr, "usage: strgen <file> <count> <seed>\n");
	exit(1);
    }
    char *infile = argv[1];
    int count    = atoi(argv[2]); // need to call atoi() to CONVERT string to an integer
    int seed     = atoi(argv[3]);
    assert(count > 0);

    (void) srandom(seed);

    FILE *fp = fopen(infile, "w");
    assert(fp != NULL);

    int i;
    for (i = 0; i < count; i++) {
	int value = (random() % 50000) - 25000;
	if (value < 0) {
	    fprintf(fp, "- %d\n", -value);
	} else {
	    fprintf(fp, "%d\n", value);
	}
    }

    fclose(fp);

    return 0;
}

