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
#define SIZE 2000000

void swap(int *elem1, int *elem2);
void generate_array(int *array, int size);
void print_array(int *array, int size);

int main(void)
{
  srand(time(0));
  int array[SIZE];
  generate_array(array, SIZE);
  clock_t t = clock();
  quick_sort(array, 0, SIZE - 1);
  t = clock() - t;
  print_array(array, SIZE);
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
  while(left < right)
  {
    while(array[left] <= pivot && left < right)
      left++;
    while(array[right] > pivot && left < right)
      right--;
    if(left < right)
    {
      swap(&array[left], &array[right]);
      left++;
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