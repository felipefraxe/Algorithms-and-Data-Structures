/*
  Code written by Felipe Fraxe Filho
  Just for learning
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define SIZE 160000

#include "heap.h"
void swap(int *elem1, int *elem2);
void generate_array(int *array, int index, int size);
void print_array(int *array, int i, int size);

int main(void)
{
  srand(time(0));
  int array[SIZE];
  generate_array(array, 0, SIZE);
  clock_t t = clock();
  heap_sort(array, SIZE);
  t = clock() - t;
  print_array(array, 0, SIZE);
  printf("This method took %lf seconds to sort\n", (double) t / CLOCKS_PER_SEC);
  return EXIT_SUCCESS;
}

void heap_sort(int *array, int size)
{
  build_heap(array, size);
  adjust_aux(array, size);
}

void adjust_aux(int *array, int size)
{
  if(size > 0)
  {
    swap(&array[0], &array[size-1]);
    max_heapify(array, array[0], size-1);
    adjust_aux(array, size - 1);
  }
}

void build_heap(int *array, int size)
{
  int parent = (size - 1) / 2;
  if(parent > 0)
  {
    max_heapify(array, parent, size);
    build_heap(array, size - 1);
  }
}

void max_heapify(int *array, int parent, int size)
{
  int left = (parent * 2) + 1;
  int right = (parent * 2) + 2;
  int largest;
  if(left >= size)
    largest = parent;
  else if(right >= size)
    largest = array[parent] < array[left] ? left : parent;
  else
    largest = get_largest(array, parent, left, right);

  if(array[parent] < array[largest])
  {
    swap(&array[parent], &array[largest]);
    max_heapify(array, largest, size);
  }
  else
  {
    int grandparent = (parent - 1) / 2;
    if(parent > 0)
      max_heapify(array, grandparent, size);
  }
}

int get_largest(int *array, int num1, int num2, int num3)
{
  if(array[num1] >= array[num2] && array[num1] >= array[num3])
    return num1;
  if(array[num2] > array[num1] && array[num2] > array[num3])
    return num2;
  return num3;
}

void swap(int *elem1, int *elem2)
{
  int tmp = *elem1;
  *elem1 = *elem2;
  *elem2 = tmp;
}

void generate_array(int *array, int index, int size)
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