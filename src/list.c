#include <stdlib.h>
#include "list.h"

 void add(struct node **head, void data){
 struct node *newNode = (struct node *)malloc(sizeOf(struct node));
 
  if(newNode == NULL){
  return;
}
  newNode->data = data;
  newNode->next = *head;
  *head = newNode;
}

void remove(0;20;15M0;20;15m)
