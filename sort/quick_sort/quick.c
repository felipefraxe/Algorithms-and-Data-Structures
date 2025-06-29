#include <stdlib.h>
#include "quick.h"

static inline void swap(int *num1, int *num2)
{
    int tmp = *num1;
    *num1 = *num2;
    *num2 = tmp;
}

static int median_of_three(int arr[], long lo, long hi)
{
	long mid = lo + ((hi - lo) / 2);
	if (arr[lo] > arr[mid])
		swap(&arr[lo], &arr[mid]);
	if (arr[lo] > arr[hi])
		swap(&arr[lo], &arr[hi]);
	if (arr[mid] > arr[hi])
		swap(&arr[mid], &arr[hi]);
	
	return arr[mid];
}

static long partition(int arr[], long lo, long hi)
{
	int pivot = median_of_three(arr, lo, hi);
	while (lo <= hi)
	{
		while (arr[lo] < pivot)
			lo++;
		while (arr[hi] > pivot)
			hi--;
		if (lo <= hi)
		{
			swap(&arr[lo], &arr[hi]);
			lo++;
			hi--;
		}
	}
	return lo;
}

static void _qsort(int arr[], long lo, long hi)
{
	while (lo < hi)
	{
		long pi = partition(arr, lo, hi);
		if (pi - lo < hi - pi)
		{
			_qsort(arr, lo, pi - 1);
			lo = pi;
		}
		else
		{
			_qsort(arr, pi, hi);
			hi = pi - 1;
		}
	}
}

void quick_sort(int arr[], size_t length)
{
  	_qsort(arr, 0, length - 1);
}