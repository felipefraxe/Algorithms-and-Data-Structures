#ifndef QUEUE_H
#define QUEUE_H

#import "../list/list.h"

typedef list_t queue_t

void queue_init(queue_t *queue);
void queue_free(queue_t *queue);
bool queue_empty(queue_t *queue);
void queue_dequeue(queue_t *queue);
void queue_enqueue(queue_t *queue, int data);

#endif
