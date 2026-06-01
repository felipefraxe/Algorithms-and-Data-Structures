/*
  Code written by Felipe Fraxe Filho
  Just for learning
*/

#include <stdlib.h>

#include "merge.h"

void merge_sort(int array[], int size)
{
    int *aux = malloc(sizeof(int) * size);
    msort(array, aux, 0, size - 1);
    free(aux);
}

void msort(int array[], int aux[], int lo, int hi)
{
    if (lo >= hi)
        return;

    int mid = lo + ((hi - lo) >> 1);
    msort(array, aux, lo, mid);
    msort(array, aux, mid + 1, hi);
    merge(array, aux, lo, mid, hi);
}

void merge(int array[], int aux[], int lo, int mid, int hi)
{
    for (int i = lo; i <= hi; i++)
        aux[i] = array[i];

    int i = lo;
    int j = mid + 1;
    int k = lo;
    while (i <= mid && j <= hi)
    {
        if (aux[i] <= aux[j])
            array[k++] = aux[i++];
        else
            array[k++] = aux[j++];
    }

    while (i <= mid)
        array[k++] = aux[i++];
}
