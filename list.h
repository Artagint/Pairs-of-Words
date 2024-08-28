// Artem Tagintsev, CS360, 09/03/2024, hw1
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

