#include "linkedlist.h"


LList_Data *llist_create_data(int key)
{
    LList_Data *data = malloc(sizeof(LList_Data));
    if(data == NULL)
    {
        fprintf(stderr, "Mem allocation error\n");
        exit(1);
    }
    data->key = key;
    return data;
}


void llist_deallocate_data(LList_Data *data)
{
    free(data);
}

LList_Node *llist_create_node(LList_Data *data)
{
    LList_Node *node = malloc(sizeof(LList_Node));
    if(node == NULL)
    {
        fprintf(stderr, "Mem allocation error\n");
        exit(1);
    }

    node->data = data;
    node->next = NULL;
    return node;
}


void llist_insert_node_start(LList_Node **head, LList_Node *node)
{
    node->next = *head;
    *head = node;
}


void llist_insert_node_end(LList_Node **head, LList_Node *node)
{
    if(*head == NULL)
    {
        *head = node;
        return;
    }

    LList_Node *tmp = *head;
    while(tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = node;
}


LList_Data *llist_search_node(LList_Node **head, void *key, int (*cmp)(const void *, const void *))
{
    for(LList_Node *curr = *head; curr != NULL; curr = curr->next)
    {
        if(cmp(&curr->data->key, key) == 0)
            return curr->data;
    }
    return NULL;
}


void llist_remove_node(LList_Node **head, void *key, int (*cmp)(const void *, const void *))
{
    LList_Node *curr = *head, *prev = NULL;
    if(cmp(&curr->data->key, key) == 0)
    {
        *head = curr->next;
        llist_deallocate_data(curr->data);
        free(curr);
        return;
    }

    for(prev = curr, curr = curr->next; curr != NULL; prev = curr, curr = curr->next)
    {
        if(cmp(&curr->data->key, key) == 0)
        {
            prev->next = curr->next;
            llist_deallocate_data(curr->data);
            free(curr);
            return;
        }
    }
}


void llist_reverse(LList_Node **head)
{
    if(*head == NULL)
        return;

    LList_Node *prev = NULL, *next = (*head)->next;
    while(next != NULL)
    {
        (*head)->next = prev;
        prev = *head;
        *head = next;
        next = next->next;
    }
    (*head)->next = prev;
}


size_t llist_length(LList_Node **head)
{
    size_t len = 0;
    for(LList_Node *tmp = *head; tmp != NULL; tmp = tmp->next)
        len++;
    return len;
}


void llist_deallocate(LList_Node **head)
{
    LList_Node *tmp = *head;
    while(tmp)
    {
        tmp = tmp->next;
        llist_deallocate_data((*head)->data);
        free(*head);
        *head = tmp;
    }
}