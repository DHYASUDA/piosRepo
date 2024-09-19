#ifndef LIST_H
#define LIST_H

 struct node{
 void *data;
 struct node *next;

};

  void add(struct node **head, void *data, struct node *after);
  
  void removeN(struct node **head, void *data);
#endif
