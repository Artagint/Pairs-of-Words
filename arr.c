// Artem Tagintsev, CS360, hw1, 09/04/2024
/*
 * This file holds all the functions associated with the big array we have at the end and also a function for qsort() which is 'compareNumbers'
 * The other functions include counting the total amount of data (or nodes) in the hash table to then use that number to allocate memory for 
 * the array in 'tableToArray'. Then we also print the array depending on if the user provided a number in the command line.
 */
#include "arr.h"

// Count total number of data entries in the hash table so that we can use the returned int to determine the size of the array
int countTotalData(struct hashEntry *hashTable){
	int dataCount = 0;
	// Loop through every node in the linked list of every bucket in the hashtable (except the sentinel nodes since there isn't data in them)
	for(int i = 0; i < hashTable->tableSize; i++){
		struct node *temp = hashTable->buckets[i]->next; // Point to the next node so that we don't count the sentinel node (sent)
		while(temp != NULL){
			dataCount++;
			temp = temp->next;
		}
	}
	return dataCount;
}

// Take all the data from the hash table and put it into the array which includes the word pair and its count the returnt the pointer to the array
struct arrayEntry *tableToArray(struct hashEntry *hashTable){
	// Call the function that counted total entries in hash table so that we can properly allocated memory for the array
	int dataCount = countTotalData(hashTable);
	struct arrayEntry *array = malloc(dataCount * sizeof(struct arrayEntry));
	
	// Move all the data from the hash table to a spot in the array
	int spotInArray = 0;
	int whichBucket = 0;

	// Loop through each bucket in the hash table and go through each node in the linked list and add it to the array
	while(whichBucket < hashTable->tableSize){
		struct node *temp = hashTable->buckets[whichBucket]->next; // We point to the next node so that we don't include the sentinel node
		// Loop through the linked list and move all the data to its spot in the array
		while(temp !=NULL){
			char *wordPair = (char *)temp->data;
			array[spotInArray].arrayData = strdup(wordPair);
			array[spotInArray].arrayCount = temp->count;
			spotInArray++;
			temp = temp->next;
		}
		whichBucket++;
	}
	return array;
}

/*
 *  Checks if the user provided a number on the command line and also checks to make sure that number isn't bigger than the amount of word pairs
 *  that we have because that would cause errors. Then print the wordPairs (either the whole array) or just the top 'n' amount that the user provided
 *  on the command line.
 */
void printArray(struct arrayEntry *array, int dataCount, int number){
	// We don't want extra loops if user inputs bigger number than total amount of word pairs, so just set number = dataCount to print whole table
	if(number > dataCount) number = dataCount;

	// Checks if the user provided a number in the input
	if(number > 0) dataCount = number;

	// Go through the array and print its contents
	for(int i = 0; i < dataCount; i++){
		printf("%10d %s\n", array[i].arrayCount, (char *)array[i].arrayData);
	}
}

// Compare parts of an array to pass into qsort() and sort in descending order
int compareNumbers(const void *passNum1, const void *passNum2){
	struct arrayEntry *num1 = (struct arrayEntry *)passNum1;
	struct arrayEntry *num2 = (struct arrayEntry *)passNum2;
	return (num2->arrayCount - num1->arrayCount); // Sort array from largest to smallest number
}

// Loop through and free each part of the array
void freeArray(struct arrayEntry *array, int dataCount){
	for(int i = 0; i < dataCount; i++){
		free(array[i].arrayData);
	}
	free(array);
}


