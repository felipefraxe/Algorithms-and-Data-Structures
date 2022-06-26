#ifndef QUICK_H
#define QUICK_H

// Quick Sort prototypes
void quick_sort(int *array, int left, int right, int (*cmp)(void *, void *));
int partition(int *array, int left, int right, int pivot, int (*cmp)(void *, void *));

#endif