/*
  Code written by Felipe Fraxe Filho
  Just for learning
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define SIZE 100000

#include "selection.h"
void swap(int *elem1, int *elem2);
void generate_array(int *array, int size);
void print_array(int *array, int size);

int main(void)
{
  srand(time(0));
  int array[SIZE];
  generate_array(array, SIZE);
  clock_t t = clock();
  selection_sort(array, SIZE);
  t = clock() - t;
  print_array(array, SIZE);
  printf("This method took %lf seconds to sort\n", (double) t / CLOCKS_PER_SEC);
  return EXIT_SUCCESS;
}

void swap(int *elem1, int *elem2)
{
  int tmp = *elem1;
  *elem1 = *elem2;
  *elem2 = tmp;
}

int search_minor(int *array, int start, int size, int minor)
{
  for(int i = start; i < size; i++)
  {
    if(array[i] < array[minor])
      minor = i;
  }
  return minor;
}

void selection_sort(int *array, int size)
{
  for(int i = 0; i < size; i++)
  {
    int minor = search_minor(array, i, size, i);
    if(minor != i)
      swap(&array[minor], &array[i]);
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
