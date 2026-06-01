#include <stdlib.h>
#include "quick.h"

static inline void swap(int *num1, int *num2)
{
    int tmp = *num1;
    *num1 = *num2;
    *num2 = tmp;
}

static int median_of_three(int arr[], int lo, int hi)
{
	int mid = lo + ((hi - lo) >> 1);

	if (arr[lo] < arr[mid])
	{
		if (arr[mid] < arr[hi])
			return arr[mid];

		if (arr[lo] < arr[hi])
			return arr[hi];

		return arr[lo];
	}

	if (arr[mid] < arr[hi])
		return arr[hi];

	if (arr[lo] < arr[hi])
		return arr[lo];
	
	return arr[mid];
}

static void _qsort(int arr[], int lo, int hi)
{
	while (lo < hi)
	{
		int pivot = median_of_three(arr, lo, hi);

		int i = lo, j = hi;
		while (i <= j)
		{
			while (arr[i] < pivot)
				i++;
			while (arr[j] > pivot)
				j--;

			if (i <= j)
				swap(&arr[i++], &arr[j--]);
		}

		if (hi - i > j - lo)
		{
			_qsort(arr, lo, j);
			lo = i;
		}
		else
		{
			_qsort(arr, i, hi);
			hi = j;
		}
	}
}

void quick_sort(int arr[], int length)
{
  	_qsort(arr, 0, length - 1);
}