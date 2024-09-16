#ifndef LIST_H
#define LIST_H

 struct node{
 void *data;
 struct node *next;

};

  void add(struct node **head, void *data);
  
  void remove(struct node **head, void *data, int (*cmp)(void *, void *));
#endif
