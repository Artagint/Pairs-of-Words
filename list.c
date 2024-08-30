// Artem Tagintsev, CS360, hw1
#include "list.h"

struct node *initNode(){
	struct node *sent = malloc(sizeof(struct node));
	sent->data = NULL;
	sent->count = 0;
	sent->next = NULL;
	return(sent);
}

void addToList(struct node *sent, void *data){
	struct node *temp = sent; // This doesn't really do anything but its easier for me to track, its the way I did it when learning DSA
	struct node *newNode = malloc(sizeof(struct node));
	newNode->data = data; // Assign the data we have passed to the data field of the new node
	newNode->count = 1; // Since node is made, the count by default not becomes 1
	// Insert newNode into beginnin of linked list after sentinel node
	newNode->next = temp->next; 
	temp->next = newNode;
}
/*
void printList(struct node *sent){
	struct node *temp = sent;
	temp = temp->next;
	while(temp != NULL){
		printf("%10d %s\n", temp->count, (char *)temp->data);
		temp = temp->next;
	}
}
*/
void freeList(struct node *sent){
	// Loop through all the nodes and free them
	while(sent != NULL){
		struct node *temp = sent;
		sent = sent->next;
		// printf("address when freeing datia: %p\n", temp->data);
		free(temp->data);
		free(temp);
	}
}
