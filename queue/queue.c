#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

void queue_init(queue_t *queue)
{
    list_init(queue);
}

void queue_free(queue_t *queue)
{
    list_free(queue);
}

bool queue_empty(queue_t *queue)
{
    return queue->length == 0;
}

void queue_dequeue(queue_t *queue)
{
    list_pop_back(queue);
}


void queue_enqueue(queue_t *queue, int data)
{
    list_push_back(queue, data);
}

int queue_front(queue_t *queue)
{
    return list_front(queue);
}