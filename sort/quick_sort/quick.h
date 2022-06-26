#ifndef QUICK_H
#define QUICK_H

// Quick Sort prototypes
void quick_sort(void *array, size_t size, int left, int right, int (*cmp)(void *, void *));
int partition(void *array, size_t size, int left, int right, int pivot, int (*cmp)(void *, void *));

#endif