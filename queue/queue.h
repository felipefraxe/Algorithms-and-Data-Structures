#ifndef QUEUE_H
#define QUEUE_H

#include "../list/list.h"

typedef list_t queue_t;

void queue_init(queue_t *queue);
void queue_free(queue_t *queue);
bool queue_empty(queue_t *queue);
void queue_dequeue(queue_t *queue);
void queue_enqueue(queue_t *queue, int data);
int queue_front(queue_t *queue);

#endif
