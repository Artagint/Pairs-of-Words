// Artem Tagintsev, CS360, hw1, 09/04/2024
/*
 * Holds the struct for the array and also holds all the function prototypes that are used for the array
 * with the addition of also have the compareNumbers function needed for qsort() which relates to arrays
 * since it is meant to be used with arrays.
 */
#include "hash.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Struct that holds the word pair and count of word pair
struct arrayEntry {
	void *arrayData;
	int arrayCount;
};

// Count the total number of data entries in the hashtable so that we can determin the size of our array
int countTotalData(struct hashEntry *hashTable);

// Take all the data from the hash table and put it into an array
struct arrayEntry *tableToArray(struct hashEntry *hashTable);

// Simply prints the array
void printArray(struct arrayEntry *array, int dataCount, int number);

// Function needed for qsort(), set up to sort in descending order
int compareNumbers(const void *passNum1, const void *passNum2);

// Free the array
void freeArray(struct arrayEntry *array, int dataCount);





