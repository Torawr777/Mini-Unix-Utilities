//===================
// cs460 project 1 
// my-uniq.c program
// Team: Kevin, Ed, Eric
// date: 2/1/2023
// This program is similar to Linux utility uniq, it reads line by line of 
// input file(s) and ignores duplicate lines. 
// To execute the program:
// ./my-uniq  [without argument, it will let the user freely make sentences]
// ./my-uniq file1 <file2> <file3> ...
//===================


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define FILECOUNT 100
#define MAX 4096
#define NUM_LINES 1000

char *searchDup(char *currentLine, char *prevLine) {

	/* Duplicate line, don't print */
	if(strcmp(currentLine, prevLine) == 0) {
	}

	else {
		printf("%s", currentLine);
	}
	
	prevLine = currentLine;
	return currentLine;
} 

void readThis(FILE* stream) {

	int x = 0;
	char *currentLine = "", *prevLine = "";
	char arr[NUM_LINES][MAX];

	/* Read line by line in file until EOF ('ctrl + d' for stdin) */
	while((fgets(arr[x], sizeof(arr), stream)) != NULL) {
		x++;
	}

	/* Check for duplicate adj lines */
	for(int k = 0; k < x; k++) {
		currentLine = arr[k];
		prevLine = searchDup(currentLine, prevLine);
		currentLine = NULL;
	}

	/* Spacing out the results */
	printf("\n");
}


void processFile(const char* fileName[FILECOUNT], int fileNum) {

	for(int n = 0; n < fileNum; n++) {
		FILE *file = fopen(fileName[n], "r");
	
		/* Check if file can be open */
		if(file == NULL) {
			fprintf(stderr, "my-uniq: cannot open file\n");
			exit(1);
		}

		/* Read file */
		readThis(file);

		/* Close current file */
		if(fclose(file)) {
			perror("fclose error");
		}
	}
}

int main(int argc, char const *argv[]) {

	int fileNum = 0, n = 1;
	const char *fileName[FILECOUNT];

	/* Read input */
	while(n < argc && argc > 1) {
		fileName[fileNum] = argv[n];
		fileNum = fileNum + 1;
		n++;
	}

	/* No file(s) specified, read from stdin */
	if(argc == 1) {
		readThis(stdin);
	}

	processFile(fileName, fileNum);
	return 0;
}