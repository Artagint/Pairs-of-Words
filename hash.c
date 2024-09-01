// Artem Tagintsev, CS360, hw1
#include "hash.h"
#include "crc64.h"

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

// Adds node to the bucket in the hash table
void addToTable(struct hashEntry *hashTable, void *data){
	// Get hash value and then determine which bucket it goes into
	unsigned long long hashValue = crc64(data); 
	int whichBucket = (hashValue%hashTable->tableSize);

	struct node *listInBucket = hashTable->buckets[whichBucket]; // Grab the sent node in the bucket we are in
	struct node *current = listInBucket->next; // Make a var for simplicity starting after the sentinel node
	
	// Loop through and check if node already exists, if it does then increment count, if not then add node to the list
	while(current != NULL){
		// Compares data we are trying to add to the data in the current node
		char *dataInNode = (char *)current->data;
		char *dataToAdd = (char *)data;
		if(strcmp(dataInNode, dataToAdd) == 0){
			current->count++;
			free(dataToAdd);
			return;
		}
		current = current->next;
	}
	addToList(listInBucket, data);
}

void printTable(struct hashEntry *hashTable){
	for(int i = 0; i < hashTable->tableSize; i++){
		printList(hashTable->buckets[i]);
	}
}


void freeHash(struct hashEntry *hashTable){
	for(int i = 0; i < hashTable->tableSize; i++){
		freeList(hashTable->buckets[i]);
	}
	free(hashTable->buckets);
	free(hashTable);
}
