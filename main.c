// Artem Tagintsev, CS360, 09/03/2024, hw1
#include "CheckErrors.h"
#include "getWord.h"
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
		if(checkNumber(argv[1], argc)){
			return 1;
		}
		else{
			number = atoi(argv[1] + 1); // convert argv[1] to a number
			if(number == 0){
				fprintf(stderr, "ERROR: make sure your number is great than '0'\n");
				return 1;
			}
			startReadingFiles = 2; // Since we were given a number, increment startReadingFiles to start readin from argv[2]
			// printf("%d\n", number);
		}
	}

	FILE *fp;
	char *fileName;
	char str1[200]; // Stores string 1
	char str2[200]; // Stores string 2
	int toggleString = 0; // Used to toggle between str1 and str2, when str1 is made, go to str2 and vice versa
	char *word; // Pointer that allocates memory for where we store the next word
	
	// Before processing contents of a file, checks if all files are valid and exits if even just one is not a valid file
	if(checkFile(argv, argc, startReadingFiles))  return 1;

	// Initialize hashTable with a starting size of 200 buckets
	struct hashEntry *hashTable = initHash(200);

	// Start reading files and pulling out and passing words pairs
	for(int i = startReadingFiles; i < argc; i++){
		fileName = argv[i];

		fp = fopen(fileName, "r");

		while((word = getNextWord(fp)) != NULL){ // Loop until the end of the file is reached
			// If toggleString is 0, copy the word into str1, then set toggleString to 1 to then get another word into str2
			if(toggleString == 0){
				strcpy(str1, word);
				toggleString = 1;
			}
			// If toggleString is 1, copy the word into str2
			else{
				strcpy(str2, word); 

				// This is where memory gets allocated for the word pair, and passed to the hash function
				char *wordPair;
				wordPair = malloc(strlen(str1) + strlen(str2) + 2); // Allocated memory for str1 + str2 + space + null terminator
				strcpy(wordPair, str1);
				strcat(wordPair, " ");
				strcat(wordPair, str2);

				addToTable(hashTable, wordPair);
				strcpy(str1, str2); // Move down a word, so copy str2 into str1 to continue to the next pair of words
				toggleString = 1; // Keep toggleString set to 1 so we can continue moving down words and copying str2 to str1
			}
			free(word);
		}
		fclose(fp);
		// After file is closed set toggleString back to 0, this is crucial because if you don't do this then the first 
		// word of the new file will be paired with the last word of the previous file esentially creating an extra word pair
		toggleString = 0;
	}
	printTable(hashTable);
	freeHash(hashTable);
	return 0;
}
