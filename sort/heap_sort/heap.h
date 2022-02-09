#ifndef HEAP_H
#define HEAP_H

// Heap Sort prototypes
void heap_sort(int *array, int size);
void build_heap(int *array, int size);
void max_heapify(int *array, int parent, int size);
void adjust_aux(int *array, int size);
int get_largest(int *array, int num1, int num2, int num3);

#endif