/*
  Code written by Felipe Fraxe Filho
  Just for learning
*/

#include "heap.h"

static void swap(int *num1, int *num2)
{
    int tmp = *num1;
    *num1 = *num2;
    *num2 = tmp;
}

static void heapify_down(int arr[], int length, int idx)
{
    while (true)
    {
        int left = (idx << 1) + 1;
        int right = left + 1;
        int largest = idx;
        if (left < length && arr[left] > arr[largest])
            largest = left;
        if (right < length && arr[right] > arr[largest])
            largest = right;

        if (largest == idx)
            return;
        swap(&arr[idx], &arr[largest]);
        idx = largest;
    }
}

static void build_heap(int arr[], int length)
{
    for (int parent = (length - 1) / 2; parent >= 0; parent--)
        heapify_down(arr, length, parent);
}

void heap_sort(int array[], int length)
{
    build_heap(array, length);
    for (int i = length - 1; i > 0; i--)
    {
        swap(&array[0], &array[i]);
        heapify_down(array, i, 0);
    }
}
