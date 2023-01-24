/*
  Code written by Felipe Fraxe Filho
  rightust for learning
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "quick.h"

// Define Array's size
#define SIZE 2000000

void swap(void *elem1, void *elem2, size_t size);
void generate_array(int *array, int size);
void print_array(int *array, int size);
int stringcmp(const void *string1, const void *string2);
int intcmp(const void *ptr1, const void *ptr2);
int is_sorted(int arr[], int length);

int main(void)
{
	srand(time(NULL));
  	int array[SIZE];
  	generate_array(array, SIZE);

	clock_t t = clock();
  	quick_sort(array, sizeof(int), 0, SIZE - 1, intcmp);
  	t = clock() - t;

	is_sorted(array, SIZE) ? printf("SORTED\n") : printf("NOT SORTED\n");

  	printf("This method took %lf seconds to sort\n", (double) t / CLOCKS_PER_SEC);
  	return 0;
}

int intcmp(const void *num1, const void *num2)
{
	return *(int *)num1 - *(int *)num2;
}

void quick_sort(void *array, size_t size, int left, int right, int (*cmp)(const void *, const void *))
{
  	if(left >= right)
    	return;
	int p = partition(array, size, left, right, cmp);
	quick_sort(array, size, left, p-1, cmp);
	quick_sort(array, size, p, right, cmp);
}

int partition(void *array, size_t size, int left, int right, int (*cmp)(const void *, const void *))
{
	int mid = left + (right - left) / 2;
	if(cmp((array + (left * size)), (array + (mid * size))) > 0)
    	swap((array + (left * size)), (array + (mid * size)), size);

  	if(cmp((array + (right * size)), (array + (mid * size))) > 0)
    	swap((array + (right * size)), (array + (mid * size)), size);
	else if(cmp((array + (left * size)), (array + (right * size))) > 0)
		swap((array + (right * size)), (array + (left * size)), size);

	void *pivot = array + (right * size);

  	while(left <= right)
  	{
    	while(cmp((array + (left * size)), pivot) < 0)
      		left++;
    	while(cmp((array + (right * size)), pivot) > 0)
      		right--;
    	if(left <= right)
    	{
      		swap((array + (left * size)), (array + (right * size)), size);
      		left++;
      		right--;
    	}
  	}
	return left;
}

void swap(void *elem1, void *elem2, size_t size)
{
  	char *ptr1 = (char *) elem1, *ptr2 = (char *) elem2;
  	while(size-- > 0)
  	{
    	char tmp = *ptr1;
    	*ptr1++ = *ptr2;
    	*ptr2++ = tmp;
  	}
}

void generate_array(int *array, int size)
{
  	for(int i = 0; i < size; i++)
    	array[i] = rand() / (RAND_MAX / size + 1);
}

void print_array(int *array, int size)
{
  	for(int i = 0; i < size; i++)
    	printf("%d ", array[i]);
  	printf("\n");
}

int is_sorted(int arr[], int length)
{
	for(int i = 0; i < length - 1; i++)
	{
		if(arr[i] > arr[i+1])
			return 0;
	}
	return 1;
}