#include <stdio.h>
#include "list.h"
int main(){
struct node *head = NULL;

	add(&head, "first", NULL);
	struct node * first = head;
	add(&head, "second", first);
	add(&head, "third", first);

	//print
	struct node * current = head;
	while(current != NULL){
	printf("%s\n", (char *) current ->data);
	current = current->next;
	}

	removeN(&head, "second");
	
	printf("Removed element ");
	current = head;
	while(current != NULL){
	printf("%s\n", (char *)current->data);
	current = current->next;

	}
	return 0;
}
