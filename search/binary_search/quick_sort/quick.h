#ifndef QUICK_H
#define QUICK_H

// Quick Sort prototypes
void quick_sort(int *array, int left, int right);
int partition(int *array, int left, int right, int pivot);
void swap(int *elem1, int *elem2);

#endif