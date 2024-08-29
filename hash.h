// Artem Tagintsev, CS360, hw1
#include "list.h"

struct hashEntry{
	struct node **buckets;
	int tableSize;
	// maybe add a collision counter later
};

// Creates and initializes a hashtable
struct hashEntry *initHash(int sizeOfTable);
