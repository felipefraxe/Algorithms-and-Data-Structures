/*
  Code written by Felipe Fraxe Filho
  Just for learning
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "list.h"

static list_node_t *node_alloc(int key)
{
    list_node_t *node = malloc(sizeof(list_node_t));
    node->key = key;
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

static list_node_t *list_node_at(list_t *list, size_t pos)
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

list_t list_init(void)
{
    list_t list = {.sentinel = malloc(sizeof(list_node_t)), .length = 0};
    list.sentinel->next = list.sentinel;
    list.sentinel->prev = list.sentinel;

    return list;
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

void list_insert_at(list_t *list, int key, size_t pos)
{
    if (pos > list->length)
        return;

    list_node_t *anchor = list_node_at(list, pos);
    list_node_t *node = node_alloc(key);
    link_node(anchor, node);
    list->length++;
}

void list_push_back(list_t *list, int key)
{
    list_node_t *node = node_alloc(key);
    link_node(list->sentinel, node);
    list->length++;
}

void list_push_front(list_t *list, int key)
{
    list_node_t *head = list->sentinel->next;
    list_node_t *node = node_alloc(key);
    link_node(head, node);
    list->length++;
}

void list_remove_at(list_t *list, size_t pos)
{
    if (list_empty(list) || pos >= list->length)
        return;

    list_node_t *node = list_node_at(list, pos);
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

void list_remove_key(list_t *list, int key)
{
    list_node_t *curr = list->sentinel->next;
    while (curr != list->sentinel)
    {
        if (key == curr->key)
        {
            unlink_node(curr);
            list->length--;
            return;
        }

        curr = curr->next;
    }
}

int list_key_at(list_t *list, size_t pos)
{
    if (pos >= list->length)
        return 0;

    list_node_t *node = list_node_at(list, pos);
    return node->key;
}

void list_print(list_t *list)
{
    for (list_node_t *node = list->sentinel->next; node != list->sentinel; node = node->next)
        printf("%d ", node->key);
    printf("\n");
}

/* void list_reverse(list_t *list)
{
    list_node_t *curr = list->head;
    list_node_t *tmp = nullptr;

    while (curr != nullptr)
    {
        tmp = curr->prev;
        curr->prev = curr->next;
        curr->next = tmp;
        curr = curr->prev;
    }

    tmp = list->head;
    list->head = list->tail;
    list->tail = tmp;
} */

/* static list_node_t *list_merge(list_node_t *first, list_node_t *second)
{
    list_node_t dummy = {0, nullptr, nullptr};
    list_node_t *curr = &dummy;

    while (first != nullptr && second != nullptr)
    {
        if (first->key < second->key)
        {
            curr->next = first;
            first->prev = curr;
            first = first->next;
        }
        else
        {
            curr->next = second;
            second->prev = curr;
            second = second->next;
        }

        curr = curr->next;
    }

    if (first != nullptr)
    {
        curr->next = first;
        first->prev = curr;
    }

    if (second != nullptr)
    {
        curr->next = second;
        second->prev = curr;
    }

    return dummy.next;
} */

/* static list_node_t *list_split(list_node_t *head)
{
    if (head == nullptr || head->next == nullptr)
        return nullptr;

    list_node_t *fast = head;
    list_node_t *slow = head;
    while (fast->next != nullptr && fast->next->next != nullptr)
    {
        fast = fast->next->next;
        slow = slow->next;
    }

    list_node_t *second = slow->next;
    slow->next = nullptr;
    if (second != nullptr)
        second->prev = nullptr;

    return second;
} */

/* static list_node_t *list_msort(list_node_t *node)
{
    if (node == nullptr || node->next == nullptr)
        return node;

    list_node_t *second = list_split(node);

    list_node_t *first = list_msort(node);
    second = list_msort(second);

    return list_merge(first, second);
} */

/* void list_sort(list_t *list)
{
   list->head = list_msort(list->head);

    list_node_t *node = list->head;
    while (node->next != nullptr)
        node = node->next;
    list->tail = node;
} */
