/*
  Code written by Felipe Fraxe Filho
  Just for learning
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "list.h"

list_t *list_init(void)
{
    list_t *list = malloc(sizeof(list_t));
    if (list == nullptr)
        return nullptr

    list->sentinel = malloc(sizeof(list_node_t));
    if (list->sentinel == nullptr)
        return nullptr;

    list->sentinel->next = list->sentinel;
    list->sentinel->prev = list->sentinel;
    list->length = 0;

    return list;
}

void list_destroy(list_t *list)
{
    if (list == nullptr)
        return;

    list_node_t *node = list->sentinel->next;
    while (node != list->sentinel)
    {
        list_node_t *next = node->next;
        free(node);
        node = next;
    }

    free(list->sentinel);
    free(list);
}

static list_node_t *list_create_node(int key)
{
    list_node_t *node = malloc(sizeof(list_node_t));
    node->key = key;

    return node;
}

/* void list_clear(list_t *list)
{
    while (list->head != nullptr)
        list_pop_front(list);

    list->tail = nullptr;
    list->length = 0;
} */

bool list_empty(list_t *list)
{
    return list->length == 0;
}

/* list_node_t *list_get(list_t *list, int key)
{
    list_node_t *head = list->head;
    list_node_t *tail = list->tail;
    while (head != tail)
    {
        if (key == head->key)
            return head;
        if (key == tail->key)
            return tail;
        head = head->next;
        tail = tail->prev;
    }

    if (key == head->key)
        return head;
    return nullptr;
} */

/* void list_pop_back(List *list)
{
    list_node_t *tmp = list->tail;
    list->tail = tmp->prev;
    if (list->tail != nullptr)
        list->tail->next = nullptr;
    else
        list->head = nullptr;
    free(tmp);

    list->length--;
} */

/* void list_pop_front(List *list)
{
    list_node_t *tmp = list->head;
    list->head = tmp->next;
    if (list->head != nullptr)
        list->head->prev = nullptr;
    else
        list->tail = nullptr;
    free(tmp);

    list->length--;
} */

void list_print(list_t *list)
{
    for (list_node_t *node = list->sentinel->next; node != list->sentinel; node = node->next)
        printf("%d ", node->key);
    printf("\n");
}

void list_push_back(list_t *list, int key)
{
    list_node_t *node = list_create_node(key);

    node->prev = list->sentinel->prev;
    node->next = list->sentinel;
    list->sentinel->prev->next = node;
    list->sentinel->prev = node;

    list->length++;
}

void list_push_front(list_t *list, int key)
{
    list_node_t *node = list_create_node(key);

    node->next = list->sentinel->next;
    node->prev = list->sentinel;
    list->sentinel->next->prev = node;
    list->sentinel->next = node;

    list->length++;
}

/* static void list_remove_node(list_node_t *node)
{
    list_node_t *prev = node->prev;
    list_node_t *next = node->next;

    if (next != nullptr)
        next->prev = prev;
    if (prev != nullptr)
        prev->next = next;
    free(node);
} */

/* void list_remove(List *list, int key)
{
    if (key == list->head->key)
        list_pop_front(list);
    else if (key == list->tail->key)
        list_pop_back(list);
    else
    {
        list_node_t *node = list->get(list, key);
        if (node != nullptr)
        {
            list_remove_node(node);
            list->length--;
        }
    }
} */

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
