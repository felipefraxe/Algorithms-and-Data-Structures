/*
  Code written by Felipe Fraxe Filho
  Just for learning
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "list.h"

List list_init(void)
{
    return (List){
        .head = nullptr,
        .tail = nullptr,
        .length = 0,

        .clear = list_clear,
        .empty = list_empty,
        .get = list_get,
        .pop_back = list_pop_back,
        .pop_front = list_pop_front,
        .print = list_print,
        .push_back = list_push_back,
        .push_front = list_push_front,
        .remove = list_remove,
        .reverse = list_reverse,
        .sort = list_sort};
}

ListNode *list_create_node(int key)
{
    ListNode *node = malloc(sizeof(ListNode));
    if (node == nullptr)
    {
        fprintf(stderr, "Could not allocate memory for node. Something went wrong\n");
        return nullptr;
    }
    node->key = key;
    node->next = nullptr;
    node->prev = nullptr;
    return node;
}

void list_clear(List *self)
{
    while (self->head != nullptr)
        list_pop_front(self);

    self->tail = nullptr;
    self->length = 0;
}

bool list_empty(List *self)
{
    return self->length == 0;
}

ListNode *list_get(List *list, int key)
{
    ListNode *head = list->head;
    ListNode *tail = list->tail;
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
}

void list_pop_back(List *self)
{
    ListNode *tmp = self->tail;
    self->tail = tmp->prev;
    if (self->tail != nullptr)
        self->tail->next = nullptr;
    else
        self->head = nullptr;
    free(tmp);

    self->length--;
}

void list_pop_front(List *self)
{
    ListNode *tmp = self->head;
    self->head = tmp->next;
    if (self->head != nullptr)
        self->head->prev = nullptr;
    else
        self->tail = nullptr;
    free(tmp);

    self->length--;
}

void list_print(List *self)
{
    for (ListNode *node = self->head; node != nullptr; node = node->next)
        printf("%d ", node->key);
    printf("\n");
}

void list_push_back(List *self, ListNode *node)
{
    if (self->tail == nullptr)
        self->tail = self->head = node;
    else
    {
        node->prev = self->tail;
        self->tail->next = node;
        self->tail = node;
    }

    self->length++;
}

void list_push_front(List *self, ListNode *node)
{
    if (self->head == nullptr)
        self->head = self->tail = node;
    else
    {
        node->next = self->head;
        self->head->prev = node;
        self->head = node;
    }

    self->length++;
}

void _list_remove_node(ListNode *node)
{
    ListNode *prev = node->prev;
    ListNode *next = node->next;

    if (next != nullptr)
        next->prev = prev;
    if (prev != nullptr)
        prev->next = next;
    free(node);
}

void list_remove(List *self, int key)
{
    if (key == self->head->key)
        list_pop_front(self);
    else if (key == self->tail->key)
        list_pop_back(self);
    else
    {
        ListNode *node = self->get(self, key);
        if (node != nullptr)
        {
            _list_remove_node(node);
            self->length--;
        }
    }
}

void list_reverse(List *self)
{
    ListNode *curr = self->head;
    ListNode *tmp = nullptr;

    while (curr != nullptr)
    {
        tmp = curr->prev;
        curr->prev = curr->next;
        curr->next = tmp;
        curr = curr->prev;
    }

    tmp = self->head;
    self->head = self->tail;
    self->tail = tmp;
}

ListNode *_list_merge(ListNode *first, ListNode *second)
{
    ListNode dummy = {0, nullptr, nullptr};
    ListNode *curr = &dummy;

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
}

ListNode *_list_split(ListNode *head)
{
    if (head == nullptr || head->next == nullptr)
        return nullptr;

    ListNode *fast = head;
    ListNode *slow = head;
    while (fast->next != nullptr && fast->next->next != nullptr)
    {
        fast = fast->next->next;
        slow = slow->next;
    }

    ListNode *second = slow->next;
    slow->next = nullptr;
    if (second != nullptr)
        second->prev = nullptr;

    return second;
}

ListNode *_list_msort(ListNode *node)
{
    if (node == nullptr || node->next == nullptr)
        return node;

    ListNode *second = _list_split(node);

    ListNode *first = _list_msort(node);
    second = _list_msort(second);

    return _list_merge(first, second);
}

void list_sort(List *self)
{
   self->head = _list_msort(self->head);

    ListNode *node = self->head;
    while (node->next != nullptr)
        node = node->next;
    self->tail = node;
}
