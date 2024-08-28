// Artem Tagintsev, CS360, hw1
#include "list.h"

// Struct that holdes array of pointers to linked lists and number of buckets in the hash table
struct hashTable{
	struct node **bucket;
	int tableSize;
};
