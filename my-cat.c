//===================
// cs460 project 1 
// my-cat.c program
// Team: Kevin, Ed, Eric
// date: 1/28/2023
// This program is similar to Linux utitliy cat, it reads line by line of 
// input file(s) and print each line to stdout.  
// To execute the program:
// ./my-cat  [without argument will do nothing and return]
// ./my-cat file1 <file2> <file3> ...
//===================

#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

#define  MAX_LEN  256

int main(int argc, char* argv[]) {

    char buffer[MAX_LEN + 1];

    //no argument given, program exit with 0
	if (argc == 1) {
		return 0;
	}

    //program name is argv[0], but come out with ./ at the beginning
    //remove the ./
    char progName[20] = "";
    int len = strlen(argv[0]);
    strncpy(progName, &argv[0][2], (len -2));

    //one or more arguments of filenames given
    //open each file for reading and print content to stdout
    for (int i = 1; i < argc; i++) {

		FILE* file = fopen(argv[i], "r");

        /* if fopen returns 0, exit 1 */
		if (file == 0)
		{
			fprintf(stderr, "%s: cannot open file\n", progName);
			exit(1);
		}

        while ((fgets(buffer, MAX_LEN, file)) != NULL){   
            printf("%s", buffer);
        }

        printf("\n");

        if (fclose(file))
            perror("fclose error");
    }

    return 0;

}
