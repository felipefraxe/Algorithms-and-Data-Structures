/*
  Code written by Felipe Fraxe Filho
  Just for learning
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

#define SIZE 100000

#include "bubble.h"
void swap(int *elem1, int *elem2);
void generate_array(int *array, int size);
void print_array(int *array, int size);

int main(void)
{
  srand(time(0));
  int array[SIZE];
  generate_array(array, SIZE);
  clock_t t = clock();
  bubble_sort(array, SIZE);
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

void bubble_sort(int *array, int size)
{
  bool swapped = true;
  for(int i = 0; i < size - 1 && swapped; i++)
  {
    swapped = false;
    for(int j = 0; j < size - i - 1; j++)
    {
      if(array[j] > array[j+1])
      {
        swap(&array[j], &array[j+1]);
        swapped = true;
      }
    }
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
