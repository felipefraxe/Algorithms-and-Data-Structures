/*
  Code written by Felipe Fraxe Filho
  Just for learning
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "quick.h"

// Define Array's size
#define SIZE 160000

void swap(int *elem1, int *elem2);
void generate_array(unsigned int *array, int index, int size);
void print_array(int *array, int i, int size);

int main(void)
{
  srand(time(0));
  int array[SIZE];
  generate_array(array, 0, SIZE);
  clock_t t = clock();
  quick_sort(array, 0, SIZE - 1);
  t = clock() - t;
  print_array(array, 0, SIZE);
  printf("This method took %lf seconds to sort\n", (double) t / CLOCKS_PER_SEC);
  return EXIT_SUCCESS;
}

void quick_sort(int *array, int left, int right)
{
  if(left < right)
  {
    int pivot = (array[left] + array[(left + right) / 2] + array[right]) / 3;
    int frontier = partition(array, left, right, pivot);
    quick_sort(array, left, frontier - 1);
    quick_sort(array, frontier, right);
  }
}

int partition(int *array, int left, int right, int pivot)
{
  if(left < right)
  {
    if(array[left] <= pivot)
      return partition(array, left + 1, right, pivot);
    if(array[right] > pivot)
      return partition(array, left, right - 1, pivot);
    if(left < right)
    {
      swap(&array[left], &array[right]);
      return partition(array, left + 1, right, pivot);
    }
  }
  return left;
}

void swap(int *elem1, int *elem2)
{
  int tmp = *elem1;
  *elem1 = *elem2;
  *elem2 = tmp;
}

void generate_array(unsigned int *array, int index, int size)
{
  if(index < size)
  {
    array[index] = rand() / (RAND_MAX / SIZE + 1);
    generate_array(array, index + 1, size);
  }
}

void print_array(int *array, int i, int size)
{
  if(i < size)
  {
    printf("%d ", array[i]);
    print_array(array, i + 1, size);
  }
  else
    printf("\n");
}