/*
  Code written by Felipe Fraxe Filho
  Just for learning
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "quick.h"

// Define Array's size
#define SIZE 200000

void swap(void *elem1, void *elem2, size_t size);
void generate_array(int *array, int size);
void print_array(int *array, int size);
int intcmp(void *ptr1, void *ptr2); 

int main(void)
{
  srand(time(NULL));
  int array[SIZE];
  generate_array(array, SIZE);

  clock_t t = clock();
  quick_sort(array, sizeof(int), 0, SIZE - 1, intcmp);
  t = clock() - t;

  print_array(array, SIZE);
  printf("This method took %lf seconds to sort\n", (double) t / CLOCKS_PER_SEC);
  return EXIT_SUCCESS;
}

int intcmp(void *ptr1, void *ptr2)
{
  int *num1 = ptr1;
  int *num2 = ptr2;
  return *num1 - *num2;
}

void quick_sort(void *array, size_t size, int left, int right, int (*cmp)(void *, void *))
{
  if(left < right)
  {
    int random_i = left + (rand() / (RAND_MAX / (right - left)));
    int pivot = (*((int *)(array + (left * size))) + *((int *)(array + (((left + right) / 2) * size))) + *((int *)(array + (right * size)))) / 3;
    int frontier = partition(array, size, left, right, pivot, cmp);
    quick_sort(array, size, left, frontier - 1, cmp);
    quick_sort(array, size, frontier, right, cmp);
  }
}

int partition(void *array, size_t size, int left, int right, int pivot, int (*cmp)(void *, void *))
{
  while(left < right)
  {
    while(cmp(array + (left * size), &pivot) <= 0 && left < right)
      left++;
    while(cmp(array + (right * size), &pivot) > 0 && left < right)
      right--;
    if(left < right)
      swap(array + (left * size), array + (right * size), size);
  }
  return left;
}

void swap(void *elem1, void *elem2, size_t size)
{
  void *(buffer[size]);
  memcpy(buffer, elem1, size);
  memcpy(elem1, elem2, size);
  memcpy(elem2, buffer, size);
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