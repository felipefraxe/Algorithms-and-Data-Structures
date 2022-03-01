#ifndef LINKED_H
#define LINKED_H

// prototypes for linked lists operations and struct definition
typedef struct list
{
  int key;
  struct list *next;
  struct list *previous;
}
list;

list *head = NULL;
list *tail = NULL;

list* create_node(int key);
void insert_node_front(list **head, list **tail, list *node);
void insert_node_back(list **head, list **tail, list *node);
void remove_node(list **head, list **tail, int key);
list* search(list *head, list *tail, int key);
void printf_list(list *head);
void printf_list_reverse(list *tail);
void deallocate_list(list *head);

#endif