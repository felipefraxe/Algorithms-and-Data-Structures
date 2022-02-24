/*
  Code written by Felipe Fraxe Filho
  Just for learning
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define SIZE 160000

#include "bubble.h"
void swap(int *elem1, int *elem2);
void generate_array(int *array, int index, int size);
void print_array(int *array, int index, int size);

int main(void)
{
  srand(time(0));
  int array[SIZE];
  generate_array(array, 0, SIZE);
  clock_t t = clock();
  bubble_sort(array, 0, SIZE);
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

void bubble_sort(int *array, int index, int size)
{
  if(index < size)
  {
    bubble(array, 0, size);
    bubble_sort(array, index, size - 1);
  }
}

void bubble(int *array, int index, int size)
{
  if(index + 1 < size)
  {
    if(array[index] > array[index+1])
      swap(&array[index], &array[index+1]);
    bubble(array, index + 1, size);
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
