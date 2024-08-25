// Artem Tagintsev, CS360, 09/03/2024, hw1
#include "CheckErrors.h"
#include "list.h"
#include "hash.h"

int main(int argc, char *argv[]){	
	// Make sure the user provides 2 or more arguments
	if(checkArgumentsFirst(argc)) return 1;

	int number = 0; // Store the number the user provides
	int startReadingFiles = 1; // By default start reading the files from argv[1]
	int skipNumCheck = 0; // Flag for skipping the number checking function

	// If argv[1][0] is a '-' or a number, set flag to skip number checking function
	if(argv[1][0] != '-' && !isdigit(argv[1][0]) ) skipNumCheck = 1;

	// If flag isn't set, proceed to call function that checks if a number is valid
	if(!skipNumCheck){
		// If checkNumber returns 1, also return 1 in main to exit program
		if(checkNumber(argv[1], argc)) {
			return 1;
		}else {
			number = atoi(argv[1] + 1); // convert argv[1] to a number
			if(number == 0){
				fprintf(stderr, "ERROR: make sure your number is great than '0'\n");
				return 1;
			}
			startReadingFiles = 2; // Since we were given a number, increment startReadingFiles to start readin from argv[2]
			printf("%d\n", number);
		}
	}

	FILE *fp;
	char *fileName;
	for(int i = startReadingFiles; i < argc; i++) {
		fileName = argv[i];

		fp = fopen(fileName, "r");
		if(fp == NULL){
			fprintf(stderr, "ERROR: file <%s> is invalid!\n", fileName);
			return 1;
		}
		printf("%s\n", fileName);
		fclose(fp);
	}



	return 0;
}
