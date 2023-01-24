#ifndef QUICK_H
#define QUICK_H

// Quick Sort prototypes
void quick_sort(void *array, size_t size, int left, int right, int (*cmp)(const void *, const void *));
int partition(void *array, size_t size, int left, int right, int (*cmp)(const void *, const void *));

#endif