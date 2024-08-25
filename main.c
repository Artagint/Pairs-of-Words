// Artem Tagintsev, CS360, 09/03/2024, hw1
#include "list.h"
#include "hash.h"

int main(int argc, char *argv[]){
	
	// Make sure the user provides 2 or more arguments
	if(argc < 2){
		fprintf(stderr, "ERROR: Provide 2 or more arguments!\n");
		return 1;
	}

	// Check if the first character of argv[1] is a '-' or a number, if its a number throw up an error
	if(isdigit(argv[1][0])){
		fprintf(stderr, "ERROR: number must be trailed by a dash, <-number>\n");
		return 1;
	}

	int number = 0; // Store the number the user provides
	int startReadingFiles = 1; // By default start reading the files from argv[1]

	// If user inputs a number for argv[1] then then make sure the number is valid
	if(argv[1][0] == '-'){
		// If a number is given, make sure user provided 3 or more arguments
		if(argc < 3){
			fprintf(stderr, "ERROR: provide file(s) after the number!\n");
			return 1;
		}
		for(int i = 1; argv[1][i] != '\0'; i++){
			// If input isn't a number, throw an error
			if(!isdigit(argv[1][i])){
				fprintf(stderr, "ERROR: Make sure you input a number after the dash, <-number>\n");
				return 1;
			}
		}
		// If number is valid, then convert input to an int and store in 'number', then update startReadingFiles to 2 so the program knows to start reading files from argv[2]
		number = atoi(argv[1] + 1);
		if(number == 0){
			fprintf(stderr, "ERROR: make sure your number is greater than '0'\n");
			return 1;
		}
		printf("%d\n", number);
		startReadingFiles = 2;
	}

	//TODO: read files and make sure they aren't empty

	for(int i = startReadingFiles; i < argc; i++) {
		printf("%s\n", argv[i]);
	}



	return 0;
}
