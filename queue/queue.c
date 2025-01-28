#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

Queue queue_init(void)
{
    return (Queue){
        .front = NULL,
        .back = NULL,
        .length = 0,

        .clear = queue_clear,
        .empty = queue_empty,
        .dequeue = queue_dequeue,
        .enqueue = queue_enqueue};
}

QueueNode *queue_create_node(int key)
{
    QueueNode *node = malloc(sizeof(QueueNode));
    if (node == nullptr)
    {
        fprintf(stderr, "Memory allocation error\n");
        return nullptr;
    }
    node->key = key;
    node->next = NULL;
    node->prev = NULL;
    return node;
}


void queue_clear(Queue *self)
{
    while (!self->empty(self))
        self->dequeue(self);
    self->length = 0;
}

bool queue_empty(Queue *self)
{
    return self->length == 0;
}

void queue_dequeue(Queue *self)
{
    QueueNode *tmp = self->front;
    self->front = tmp->next;
    if (self->front != nullptr)
        self->front->prev = nullptr;
    else
        self->back = nullptr;
    free(tmp);

    self->length--;
}


void queue_enqueue(Queue *self, QueueNode *node)
{
    if (self->back == nullptr)
        self->back = self->front = node;
    else
    {
        node->prev = self->back;
        self->back->next = node;
        self->back = node;
    }

    self->length++;
}

