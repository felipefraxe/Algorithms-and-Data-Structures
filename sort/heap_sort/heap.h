#ifndef HEAP_H
#define HEAP_H

// Heap Sort prototypes
void heap_sort(int array[], int length);
static void heapify_down(int array[], int length, int idx);
static void build_heap(int array[], int length);

#endif