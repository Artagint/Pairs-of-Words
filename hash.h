// Artem Tagintsev, CS360, hw1
#include "list.h"

struct hashEntry{
	struct node **buckets;
	int tableSize;
	// maybe add a collision counter later
};

// Creates and initializes a hashtable
struct hashEntry *initHash(int sizeOfTable);

// Add the word pair and their count to the hash table
void addToTable(struct hashEntry *hashTable, void *data);

// Print the hash table
void printTable(struct hashEntry *hashTable);

// Free all memory associated with the hash table
void freeHash(struct hashEntry *hashTable);
