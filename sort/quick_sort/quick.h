#ifndef QUICK_H
#define QUICK_H

// Quick Sort prototypes
void quick_sort(int *array, size_t length, int low, int high, int (*cmp)(const void *, const void *));
int partition(void *array, size_t size, int low, int high, int (*cmp)(const void *, const void *));

#endif