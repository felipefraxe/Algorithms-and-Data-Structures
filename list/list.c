/*
  Code written by Felipe Fraxe Filho
  Just for learning
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "list.h"

static list_node_t *node_alloc(int data)
{
    list_node_t *node = malloc(sizeof(list_node_t));
    node->data = data;
    return node;
}

static void unlink_node(list_node_t *node)
{
    node->prev->next = node->next;
    node->next->prev = node->prev;
    free(node);
}

static void link_node(list_node_t *anchor, list_node_t *node)
{
    anchor->prev->next = node;
    node->prev = anchor->prev;
    node->next = anchor;
    anchor->prev = node;
}

static list_node_t *node_at(list_t *list, size_t pos)
{
    list_node_t *curr;
    if (pos > list->length / 2)
    {
        curr = list->sentinel->prev;
        for (size_t i = list->length - 1; i > pos; i--)
            curr = curr->prev;
    }
    else
    {
        curr = list->sentinel->next;
        for (size_t i = 0; i < pos; i++)
            curr = curr->next;
    }

    return curr;
}

inline bool list_empty(list_t *list)
{
    return list->length == 0;
}

void list_free(list_t *list)
{
    list_node_t *node = list->sentinel->next;
    while (node != list->sentinel)
    {
        list_node_t *next = node->next;
        free(node);
        node = next;
    }
    free(list->sentinel);
}

void list_init(list_t *list)
{
    list->sentinel = malloc(sizeof(list_node_t));
    list->length = 0;

    list->sentinel->next = list->sentinel;
    list->sentinel->prev = list->sentinel;
}

void list_remove_all(list_t *list)
{
    list_node_t *node = list->sentinel->next;
    while (node != list->sentinel)
    {
        list_node_t *next = node->next;
        free(node);
        node = next;
    }

    list->sentinel->next = list->sentinel;
    list->sentinel->prev = list->sentinel;
    list->length = 0;
}

void list_insert_at(list_t *list, int data, size_t pos)
{
    if (pos > list->length)
        return;

    list_node_t *anchor = node_at(list, pos);
    list_node_t *node = node_alloc(data);
    link_node(anchor, node);
    list->length++;
}

void list_push_back(list_t *list, int data)
{
    list_node_t *node = node_alloc(data);
    link_node(list->sentinel, node);
    list->length++;
}

void list_push_front(list_t *list, int data)
{
    list_node_t *head = list->sentinel->next;
    list_node_t *node = node_alloc(data);
    link_node(head, node);
    list->length++;
}

void list_remove_at(list_t *list, size_t pos)
{
    if (list_empty(list) || pos >= list->length)
        return;

    list_node_t *node = node_at(list, pos);
    unlink_node(node);
    list->length--;
}

void list_pop_back(list_t *list)
{
    if (list_empty(list))
        return;

    list_node_t *tail = list->sentinel->prev;
    unlink_node(tail);
    list->length--;
}

void list_pop_front(list_t *list)
{
    if (list_empty(list))
        return;

    list_node_t *head = list->sentinel->next;
    unlink_node(head);
    list->length--;
}

void list_remove_data(list_t *list, int data)
{
    list_node_t *curr = list->sentinel->next;
    while (curr != list->sentinel)
    {
        if (data == curr->data)
        {
            unlink_node(curr);
            list->length--;
            return;
        }

        curr = curr->next;
    }
}

int list_data_at(list_t *list, size_t pos)
{
    if (pos >= list->length)
        return 0;

    list_node_t *node = node_at(list, pos);
    return node->data;
}

void list_print(list_t *list)
{
    list_node_t *node = list->sentinel->next;
    while (node != list->sentinel)
    {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

void list_reverse(list_t *list)
{
    list_node_t *curr = list->sentinel;
    do
    {
        list_node_t *tmp = curr->next;
        curr->next = curr->prev;
        curr->prev = tmp;
        curr = tmp;
    } while (curr != list->sentinel);
}
