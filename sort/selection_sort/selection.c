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
void generate_array(int *array, int index, int size);
void print_array(int *array, int index, int size);

int main(void)
{
  srand(time(0));
  int array[SIZE];
  generate_array(array, 0, SIZE);
  clock_t t = clock();
  selection_sort(array, 0, SIZE);
  t = clock() - t;
  print_array(array, 0, SIZE);
  printf("This method took %lf seconds to sort\n", (double) t / CLOCKS_PER_SEC);
  return EXIT_SUCCESS;
}

void swap(int *elem1, int *elem2)
{
  int tmp = *elem1;
  *elem1 = *elem2;
  *elem2 = tmp;
}

int search_minor(int array[], int index, int size, int minor)
{
  if(index == size)
    return minor;
  if(array[index] < array[minor])
    return search_minor(array, index + 1, size, index);
  return search_minor(array, index + 1, size, minor);
}

void selection_sort(int array[], int index, int size)
{
  if(index < size)
  {
    int minor = search_minor(array, index, size, index);
    if(minor != index)
      swap(&array[minor], &array[index]);
    selection_sort(array, index + 1, size);
  }
}

void generate_array(int *array, int index, int size)
{
  if(index < size)
  {
    array[index] = rand() / (RAND_MAX / SIZE + 1);
    generate_array(array, index + 1, size);
  }
}

void print_array(int *array, int index, int size)
{
  if(index < size)
  {
    printf("%d ", array[index]);
    print_array(array, index + 1, size);
  }
  else
    printf("\n");
}