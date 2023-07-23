//===================
// CS460 Project 1 
// my-sed.c program
// Team: Kevin, Ed, Eric
// Date: 2/1/2023
// This program is similar to Linux utility sed, it finds and replace line 
// by line of input file(s) and print the output
// To execute the program:
// ./my-sed  [Throws an error if no arguments are made]
// ./my-sed <searchWord> <replaceWord> <file1> ...
//===================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define FILECOUNT 1000
#define MAX 4096

void replaceStr();

int search(const char *find, const char *replace, char *buffer) {
	
	/* Get length */
	int findLen = strlen(find);
	int bufferLen = strlen(buffer);
	int pos = 0, offset = 0, targetPos = 0;
	char currStr[findLen];

	while(pos + findLen <= bufferLen && offset < findLen) {

		int n = 0;

		/* Reach each word from the buffer */
		while(n < findLen) {
			currStr[offset] = buffer[pos + offset];
			offset = offset + 1;
			n = n + 1;
		}

		currStr[offset] = '\0';

		/* Compares current string to target string */
		if(strcmp(find, currStr) == 0) {
			targetPos = pos;
			replaceStr(bufferLen, findLen, targetPos, replace, buffer);
			return 0;
		}

		offset = 0;
		pos = pos + 1;
	}

	return 1;
} 

/* Replaces the given string */
void replaceStr(int bufferLen, int findLen, int targetPos, const char *replace, char *buffer) {

	int n = 0;
	int replaceLength = findLen - 1;

	while(n < bufferLen) {

		if(n == targetPos) {
			printf("%s", replace);
			n = n + replaceLength;
		}

		else { 
			printf("%c", buffer[n]); 
		}

		n = n + 1;
	}
}

void fileReader(const char *find, const char *replace, const char* fileName[FILECOUNT], int fileNum) {

	char *buffer = 0;
	size_t size = 0;
	
	/* Loop through depending on many files were inputted */
	for(int x = 0; x < fileNum; x++) {
		FILE *file = fopen(fileName[x], "r");

		/* Check if file can open */
		if(file == NULL) {
			fprintf(stderr, "my-sed: cannot open file\n");
			fprintf(stderr, "%s\n", strerror(errno));
			exit(1);
		}

		/* Goes through and replace with our specified arguments */
		while(getline(&buffer, &size, file) != -1) {
			if(search(find, replace, buffer) == 1) {
				printf("%s", buffer);
			}
		}

		/* Prevents multiple file content overlapping */
		printf("\n");

		if(fclose(file)) {
			perror("fclose error");
		}
	}

	free(buffer);
}


int main(int argc, char const *argv[]) {

	int fileNum = 0, n = 1;
	const char *find, *replace;
	const char *fileName[FILECOUNT];
	char line[MAX];

	/* Missing arguments check */
	if(argc < 3) {
		fprintf(stderr, "my-sed: find_term replace_term [file ...]\n");
		exit(1);
	}

	/* Read input */
	while(n < argc && argc > 1) {

		if(n == 1) {
			find = argv[n];
		}

		else if(n == 2) {
			replace = argv[n];
		}

		else {
			fileName[fileNum] = argv[n];
			fileNum = fileNum + 1;
		} 
		n = n + 1;
	}

	/* No file(s) specified, read from stdin */
	if(argc == 3) {

		while(fgets(line, sizeof(line), stdin)) {

			if(search(find, replace, line) == 1) {
				printf("%s", line);
			}
		}
	}

	fileReader(find, replace, fileName, fileNum);
	return 0;
}