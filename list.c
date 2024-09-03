// Artem Tagintsev, CS360, hw1, 09/04/2024
/*
 * This file contains all the functions that are used for the linked lists which are contained in the hash table buckets
 */
#include "list.h"

/*
 *  Initialize the sentinel node for the linked list and set the data and next pointer to NULl, and count to 0
 *  The sent node is in the beginning of the list of each bucket
 */
struct node *initNode(){
	struct node *sent = malloc(sizeof(struct node));
	sent->data = NULL;
	sent->count = 0;
	sent->next = NULL;
	return(sent);
}

/*
 *  Adds new nodes to the linked list after the sentinel node and when a newNode is added then increment the count to 1 since a
 *  word pair now exists atleast once.
 */
void addToList(struct node *sent, void *data){
	struct node *temp = sent; // This doesn't really do anything but its easier for me to track, its the way I did it when learning DSA
	struct node *newNode = malloc(sizeof(struct node));
	newNode->data = data; // Assign the data we have passed to the data field of the new node
	newNode->count = 1; // Since node is made, the count by default not becomes 1
	// Insert newNode into beginnin of linked list after sentinel node
	newNode->next = temp->next; 
	temp->next = newNode;
}

/* This was just used for testing, don't need it in the code but still decided to keep it but commented out 
void printList(struct node *sent){
	struct node *temp = sent;
	temp = temp->next;
	while(temp != NULL){
		printf("%10d %s\n", temp->count, (char *)temp->data);
		temp = temp->next;
	}
}
*/

// Frees every node in the linked list when freeTable is called in hash.c
void freeList(struct node *sent){
	// Loop through all the nodes and free them
	while(sent != NULL){
		struct node *temp = sent;
		sent = sent->next;
		free(temp->data);
		free(temp);
	}
}
