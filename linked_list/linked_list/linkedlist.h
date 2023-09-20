#ifndef LINKED_H
#define LINKED_H

#include <stdio.h>
#include <stdlib.h>

typedef struct LList_Data
{
    int key;
}
LList_Data;


typedef struct LList_Node
{
    LList_Data *data;
    struct LList_Node *next;
}
LList_Node;


LList_Data *llist_create_data(int key);
LList_Node *llist_create_node(LList_Data *data);
void llist_insert_node_start(LList_Node **head, LList_Node *node);
void llist_insert_node_end(LList_Node **head, LList_Node *node);
LList_Data *llist_search_node(LList_Node **head, void *key, int (*cmp)(const void *, const void *));
void llist_remove_node(LList_Node **head, void *key, int (*cmp)(const void *, const void *));
void llist_reverse(LList_Node **head);
size_t llist_length(LList_Node **head);
void llist_deallocate(LList_Node **head);

#endif