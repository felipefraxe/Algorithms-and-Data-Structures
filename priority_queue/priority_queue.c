#include <stdlib.h>
#include <limits.h>

#include "priority_queue.h"

static void heapify_up(priority_queue_t *min_heap, size_t idx)
{
    while (idx > 0)
    {
        size_t parent = (idx - 1) / 2;
        if (vector_at(min_heap, parent) <= vector_at(min_heap, idx))
            return;

        int tmp = vector_at(min_heap, parent);
        vector_set(min_heap, parent, vector_at(min_heap, idx));
        vector_set(min_heap, idx, tmp);

        idx = parent;
    }
}

static void heapify_down(priority_queue_t *min_heap, size_t idx)
{
    while (true)
    {
        size_t left = (2 * idx) + 1;
        size_t right = left + 1;
        size_t smallest = idx;

        if (left < min_heap->length && vector_at(min_heap, left) < vector_at(min_heap, smallest))
            smallest = left;

        if (right < min_heap->length && vector_at(min_heap, right) < vector_at(min_heap, smallest))
            smallest = right;

        if (smallest == idx)
            return;
        
        int tmp = vector_at(min_heap, idx);
        vector_set(min_heap, idx, vector_at(min_heap, smallest));
        vector_set(min_heap, smallest, tmp);
 
        idx = smallest;
    }
}

void pq_build_heap(priority_queue_t *vec)
{
    if (vec->length <= 1)
        return;

    for (size_t parent = (vec->length - 1) / 2; parent > 0; parent--)
        heapify_down(vec, parent);
    heapify_down(vec, 0);
}

void pq_init(priority_queue_t *min_heap)
{
    vector_init(min_heap);
}

void pq_free(priority_queue_t *min_heap)
{
    vector_free(min_heap);
}

void pq_push(priority_queue_t *min_heap, int data)
{
    vector_push_back(min_heap, data);
    heapify_up(min_heap, min_heap->length - 1);
}

void pq_pop(priority_queue_t *min_heap)
{
    if (pq_empty(min_heap))
        return;

    vector_set(min_heap, 0, vector_at(min_heap, min_heap->length - 1));
    min_heap->length--;

    heapify_down(min_heap, 0);
}

void pq_push_pop(priority_queue_t *min_heap, int data)
{
    if (pq_empty(min_heap))
        return;

    vector_set(min_heap, 0, data);
    heapify_down(min_heap, 0);
}

inline int pq_top(priority_queue_t *min_heap)
{
    return min_heap->length > 0 ? vector_at(min_heap, 0) : INT_MIN;
}

inline bool pq_empty(priority_queue_t *min_heap)
{
    return min_heap->length == 0;
}