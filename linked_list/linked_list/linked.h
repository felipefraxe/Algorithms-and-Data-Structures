#ifndef LINKED_H
#define LINKED_H

// prototypes for linked lists operations and struct definition
typedef struct list
{
  int key;
  struct list *next;
}
list;

list *head = NULL;

list* create_node(int key);
list* insert_node(list *head, list *node);
list* remove_node(list *head, int key);
list* search(list *head, int key);
void printf_list(list *head);
void deallocate_list(list *head);

#endif