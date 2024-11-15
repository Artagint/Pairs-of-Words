// Artem Tagintsev, CS360, 09/03/2024, hw1, 09/04/2024
// Holds the linked list struct and all the function prototypes for the linked lists
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Struct that holds word pair, count of word pair, and pointer to next node
struct node{
	void *data;
	int count;
	struct node *next;
};

// Function to initialize a sentinel node
struct node *initNode();

// Function that adds a new node
void addToList(struct node *sent, void *data);

// Print the list
// void printList(struct node *sent);

// Free all memory from every node in the linked list
void freeList(struct node *sent);

