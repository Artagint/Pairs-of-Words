// Artem Tagintsev, CS360, hw1, 09/04/2024
/*
 * This is the file that holds all the functions that are for the hash table, this also includes explaining why I chose to grow the hash table
 * when the load factor is 75% or more (which I explain in the comment block above 'growTable'.
 */
#include "hash.h"
#include "crc64.h"

// Returns a pointer to the hashtable after if has been initialized
struct hashEntry *initHash(int sizeOfTable){
	// Allocate memory for hashtable itself and also the array of buckets we will be using
	struct hashEntry *hashTable = malloc(sizeof(struct hashEntry)); 
	hashTable->buckets = malloc(sizeOfTable*sizeof(struct node *));
	hashTable->tableSize = sizeOfTable;
        hashTable->bucketsFilled = 0;	

	// Initialize each bucket of the table with a sentinel node for the linked list 
	for(int i = 0; i < sizeOfTable; i++){
		hashTable->buckets[i] = initNode();
	}
	return hashTable;
}

/*
 *  Adds data to the hash table (in this case a wordPair), and if the wordPair already exists then increment its count in the node.
 *  Also keep track of the load factor here so that it doesn't exceed 75% (I explain why in the 'growTable' function), if the size
 *  of the table does exceed 75% of buckets filled, then the 'growTable' function is called.
 */ 
void addToTable(struct hashEntry *hashTable, void *data){
	// Get hash value and then determine which bucket it goes into
	unsigned long long hashValue = crc64(data);
       	int tableSize = hashTable->tableSize;	
	int whichBucket = (hashValue % tableSize);
	struct node *listInBucket = hashTable->buckets[whichBucket]; // Grab the sent node in the bucket we are in
	struct node *current = listInBucket->next; // Skip the sentinel node (for insertion)
	
	// If the bucket we are filling is empty, then increment the count of bucketsFilled to keeep track of the load factor
	if(current == NULL) hashTable->bucketsFilled++;
	
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
	// If wordPair wasn't found in the linked list, then add it to the end of the list
	addToList(listInBucket, data);

	// Check the load factor and call growTable if 75% or more of the buckets are filled in the hashtable
	// printf("BEFORE: %d <> %d\n", hashTable->tableSize, hashTable->bucketsFilled);
	int fullBuckets = hashTable->bucketsFilled;
	int sizeOfTable = ((hashTable->tableSize*75)/100);
	if(fullBuckets >= sizeOfTable){
		// printf("AFTER: %d <> %d\n", hashTable->tableSize, hashTable->bucketsFilled);
		growTable(hashTable);
	}
}

/*
 * This is where we grow the hash table when 'growTable' is called in the 'addToTable' function if the load factors is 75% or more.
 * How this works is a new hash table is made and all the data gets rehashed and put into the new respective buckets, then after that
 * we want to update the oldTable (since newTable is temporary) with the newTable information but giving all its data like the wordPair,
 * bucketsFilled, and tableSize. The reason I chose load factor and specifically 75% is due to my testing. At first I wanted to grow the table
 * if a chain in a bucket matched the length of the tableSize, but that didn't seem like the most efficient use of a hashtable. So then I went 
 * to load factor and at first thought about growing the table when all buckets are filled but when I tested that it took a lot of data to fill 
 * all the buckets of the table. I then thought about doing 50% filled but that just seem like too much growing. So I simply stuck witht the 
 * middle ground of 75% since when that much of the buckets are filled the performance of the hash table is still relatively good and it can 
 * then grow 3x in size over and over as many times needed. We then don't have to return anything in this function since we update the pointer 
 * 'oldTable' with our temporary 'newTable' data.
 */
void growTable(struct hashEntry *oldTable){
	int newTableSize = (oldTable->tableSize*3); // 3x the size of oldTable
	struct hashEntry *newTable = initHash(newTableSize); // Make a temporary newTable
	int oldTableSize = oldTable->tableSize;

	// Loop through every bucket in the oldTable and rehash, determine what bucket data goes into and insert into the linked list in that bucket
	for(int i = 0; i < oldTableSize; i++){
		struct node *current = oldTable->buckets[i]->next; // Skip the sent node
		// Loop through the linked list in the bucket and add the data to the newTable's linked list in the bucket
		while(current != NULL){
			unsigned long long hashValue = crc64(current->data);
			int whichBucket = (hashValue % newTableSize);
			addToList(newTable->buckets[whichBucket], current->data); // Call the addToList with the current bucket and data to add
			// Save a pointer to the next node before freeing current then free after moving to the next node
			struct node *temp = current;
			current = current->next;
			free(temp);
		}
		free(oldTable->buckets[i]); // Free the bucket after we are done with it
	}
	free(oldTable->buckets);
	// Update oldTable with the data of newTable
	oldTable->buckets = newTable->buckets;
	oldTable->tableSize = newTableSize;
	oldTable->bucketsFilled = newTable->bucketsFilled;
	free(newTable);
}	

/* I used this function for testing the hash table during development, don't need it anymore but still thought I should keep it in the code but commented out
void printTable(struct hashEntry *hashTable){
	for(int i = 0; i < hashTable->tableSize; i++){
		printList(hashTable->buckets[i]);
	}
}
*/

// Loop through every bucket in the hash table call freeList to free the linked lists in those buckets, then free the buckets and the hash table itself
void freeHash(struct hashEntry *hashTable){
	for(int i = 0; i < hashTable->tableSize; i++){
		freeList(hashTable->buckets[i]);
	}
	free(hashTable->buckets);
	free(hashTable);
}
