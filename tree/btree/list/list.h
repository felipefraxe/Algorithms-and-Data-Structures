#ifndef LIST_H
#define LIST_H

#include "../structs.h"

// Prototypes for stack (linked list) functions
list* new_node(Btree **root);
void push(list **stack, list *node);
void pull(list **stack);
void deallocate_stack(list *stack);

#endif