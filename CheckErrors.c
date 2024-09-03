// Artem Tagintsev, CS360, hw1
// This file simply holds the functions for error checking code that includes input I/O and file I/O
#include "CheckErrors.h"

// Make sure the user provides 2 or more arguments
int checkArgumentsFirst(int argc){
	if (argc < 2){
		fprintf(stderr, "ERROR: Provide 2 or more arguments!\n");
		return 1;
	}
	return 0;
}

// Check if the number is valid after the '-' if a number is even given
int checkNumber(char *argv, int argc){
	// Check if the first character of argv[1] is a '-' or a number, if its a number throw up an error
	if(isdigit(argv[0])){
		fprintf(stderr, "ERROR: number must be trailed by a dash, <-number>\n");
	       	return 1;	
	}

	// If user inputs a number for argv[1] then make sure the number is valid
	if(argv[0] == '-'){
		// If a number is given, make sure user provided 3 or more arguments on the command line
		if(argc < 3){
			fprintf(stderr, "ERROR: provide file(s) after the number!\n");
			return 1;
		}
		for(int i = 1; argv[i] != '\0'; i++){
			// If input isn't a number, throw an error
			if(!isdigit(argv[i])){
				fprintf(stderr, "ERROR: Make sure you input a number after the dash, <-number>\n");
				return 1;
			}
		}
	}
	return 0;
}

// This check loops through every file and checks if it exists or not, returns 1 if it doesn't and exists the program
int checkFile(char **argv, int argc, int startReadingFiles){
	FILE *fp;
	char *fileName;
	for(int i = startReadingFiles; i < argc; i++){
		fileName = argv[i];
		fp = fopen(fileName, "r");
		if(fp == NULL){
			fprintf(stderr, "ERROR: file <%s> is invalid!\n", fileName);
			return 1;
		}
		fclose(fp);
	}
	return 0;
}
