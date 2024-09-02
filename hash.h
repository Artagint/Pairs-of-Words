// Artem Tagintsev, CS360, hw1
#include "list.h"

struct hashEntry{
	struct node **buckets; // Pointer to what is in the buckets
	int tableSize; // Tracks the amount of buckets that the table has
	int bucketsFilled; // Tracks how many buckets are filled, important for rehashing
};

// Creates and initializes a hashtable
struct hashEntry *initHash(int sizeOfTable);

// Add the word pair and their count to the hash table
void addToTable(struct hashEntry *hashTable, void *data);

// Grows the table by updating its size 3x and also rehashing all the values
void growTable(struct hashEntry *hashTable);

// Print the hash table
void printTable(struct hashEntry *hashTable);

// Free all memory associated with the hash table
void freeHash(struct hashEntry *hashTable);
