/*
  Code written by Felipe Fraxe Filho
  Just for learning
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "merge.h"

// Define Array's size
#define SIZE 1000000

void swap(int *elem1, int *elem2);
void generate_array(int *array, int size);
void print_array(int *array, int size);

int main(void)
{
  srand(time(0));
  int array[SIZE];
  generate_array(array, SIZE);
  clock_t t = clock();
  merge_sort(array, 0, SIZE - 1);
  t = clock() - t;
  print_array(array, SIZE);
  printf("This method toomain_index %lf seconds to sort\n", (double) t / CLOCKS_PER_SEC);
  return EXIT_SUCCESS;
}

void merge_sort(int *array, int left, int right)
{
  if (left < right)
  {
    int mid = left + (right - left) / 2;
    merge_sort(array, left, mid);
    merge_sort(array, mid + 1, right);
    merge(array, left, mid, right);
  }
}

void merge(int *array, int left, int mid, int right)
{
  int size1 = (mid + 1) - left;
  int size2 = right - mid;
  int array1[size1], array2[size2];

  for(int i = 0, k = left; i < size1; i++, k++)
    array1[i] = array[k];

  for(int j = 0, k = mid + 1; j < size2; j++, k++)
    array2[j] = array[k];

  int i = 0, j = 0, k = left;
  while(i < size1 && j < size2)
  {
    if(array1[i] < array2[j])
      array[k++] = array1[i++];
    else
      array[k++] = array2[j++];
  }

  while(i < size1)
    array[k++] = array1[i++];
  while(j < size2)
    array[k++] = array2[j++];
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