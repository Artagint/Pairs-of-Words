// Artem Tagintsev, CS360, hw1
#include "list.h"

struct node *initNode(){
	struct node *sent = malloc(sizeof(struct node));
	sent->data = NULL;
	sent->count = 0;
	sent->next = NULL;
	return(sent);
}
