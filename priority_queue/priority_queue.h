#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "../vector/vector.h"

typedef struct vector_t priority_queue_t;

void pq_build_heap(priority_queue_t *heap);
bool pq_empty(priority_queue_t *min_heap);
void pq_free(priority_queue_t *min_heap);
void pq_init(priority_queue_t *min_heap);
void pq_pop(priority_queue_t *min_heap);
void pq_push(priority_queue_t *min_heap, int data);
void pq_push_pop(priority_queue_t *min_heap, int data);
int pq_top(priority_queue_t *min_heap);

#endif