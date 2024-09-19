#include <stdlib.h>
#include <stdio.h>
#include "list.h"

 void add(struct node **head, void *data, struct node *after){
 struct node *newNode = (struct node *)malloc(sizeof(struct node));
 
  if(newNode == NULL){
  return;
}

  newNode->data = data;
  //beginning of linked list
  if(after == NULL){
  newNode->next = *head;
  *head = newNode;
} else {
    newNode->next = after->next;
    after->next = newNode;
}
}
  
 
//remove
  void removeN(struct node **head, void *data){
  if(*head == NULL){
	return;
}
	struct node *current = *head;
	struct node *prev = NULL;

	if(current->data == data){
	*head = current->next;
	free(current);
	return;
}
	while(current != NULL && current-> data != data){
	prev = current;
	current = current->next;
}
	if(current ==NULL){
	 return;
}
	prev->next = current->next;

	free(current);
}
 
