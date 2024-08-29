// Artem Tagintsev, CS360, hw1
#include "hash.h"

// Call initHash function with specified size of the hash table, will be '500' in this case
struct hashEntry *initHash(int sizeOfTable){
	// Allocate memory for hashtable itself and also the array of buckets we will be using
	struct hashEntry *hashTable = malloc(sizeof(struct hashEntry)); 
	hashTable->buckets = malloc(sizeOfTable*sizeof(struct node *));
	hashTable->tableSize = sizeOfTable; 

	// Initialize each bucket of the table with a sentinel node for the linked list 
	for(int i = 0; i < sizeOfTable; i++){
		hashTable->buckets[i] = initNode();
	}
	return hashTable; // Return pointer to hashEntry
}
