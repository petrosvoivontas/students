#ifndef LIST_H
#define LIST_H

typedef struct _list* list;
typedef struct _node* node;
typedef struct student* student;

struct _list
{
  node head, tail;
  int size;
};

struct _node
{
  node next;
  student s;
};

// Creates an empty list
list list_create();

// Frees memory allocated to a list
void list_destroy(list l);

// Adds a node to a list as the last node of that list and returns the status of the operation
int push(list l, node node_to_push);

// Deletes a specific node from a list and returns the status of the operation
int delete_entry(list l, node node_to_delete);

#endif
