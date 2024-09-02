// Artem Tagintsev, CS360, hw1
#include "arr.h"

// Count total number of data entries in the hash table so that we can determine the size of the array
int countTotalData(struct hashEntry *hashTable){
	int dataCount = 0;
	// Loop through every node in the linked list of every bucket in the hashtable (except the sentinel nodes)
	for(int i = 0; i < hashTable->tableSize; i++){
		struct node *temp = hashTable->buckets[i]->next; // We point to the next node so that we don't count the sentinel node (sent)
		while(temp != NULL){
			dataCount++;
			temp = temp->next;
		}
	}
	return dataCount;
}

// Take all the data from the hash table and put it into the array
struct arrayEntry *tableToArray(struct hashEntry *hashTable){
	// Call the function that counted total entries in hash table so that we can properly allocated memory for the array
	int dataCount = countTotalData(hashTable);
	struct arrayEntry *array = malloc(dataCount * sizeof(struct arrayEntry));
	
	// Move all the data from the hash table to a spot in the array
	int spotInArray = 0;
	int whichBucket = 0;
	while(whichBucket < hashTable->tableSize){
		struct node *temp = hashTable->buckets[whichBucket]->next; // We point to the next node so that we don't include the sentinel node
		while(temp !=NULL){
			// Move the data and count from hash table into arrayData and arrayCount respectively
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

// Check for user number argument and then print arrat accordingly
void printArray(struct arrayEntry *array, int dataCount, int number){
	// We don't want extra loops if user inputs bigger number than total amount of word pairs, so just set number = dataCount to print whole table
	if(number > dataCount){
		number = dataCount;
	}
	// Checks if the user provided a number in the input
	if(number > 0){
		dataCount = number;
	}
	// Go through the array and print its contents
	for(int i = 0; i < dataCount; i++){
		printf("%10d %s\n", array[i].arrayCount, (char *)array[i].arrayData);
	}
}

// Sort the array from qsort()
int compareNumbers(const void *passNum1, const void *passNum2){
	struct arrayEntry *num1 = (struct arrayEntry *)passNum1;
	struct arrayEntry *num2 = (struct arrayEntry *)passNum2;
	return (num2->arrayCount - num1->arrayCount); // Sort array from largest to smallest number
}

// Free the array
void freeArray(struct arrayEntry *array, int dataCount){
	for(int i = 0; i < dataCount; i++){
		free(array[i].arrayData);
	}
	free(array);
}


