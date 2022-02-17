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
#define SIZE 95000

void swap(int *elem1, int *elem2);
void generate_array(int *array, int index, int size);
void print_array(int *array, int index, int size);

int main(void)
{
  srand(time(0));
  int array[SIZE];
  generate_array(array, 0, SIZE);
  clock_t t = clock();
  merge_sort(array, 0, SIZE - 1);
  t = clock() - t;
  print_array(array, 0, SIZE);
  printf("This method toomain_index %lf seconds to sort\n", (double) t / CLOCKS_PER_SEC);
  return EXIT_SUCCESS;
}

void merge_sort(int *array, int left, int right)
{
  if (left < right)
  {
    int mid = (left + right) / 2;
    merge_sort(array, left, mid);
    merge_sort(array, mid + 1, right);
    merge(array, left, mid, right);
  }
}

void merge(int *array, int left, int mid, int right)
{
  int size1 = (mid + 1) - left;
  int size2 = right - mid;
  int array1[size1];
  int array2[size2];
  fill_array(array, left, array1, 0, size1);
  fill_array(array, mid + 1, array2, 0, size2);
  get_in_order(array, left, array1, 0, size1, array2, 0, size2);
}

void fill_array(int *main_array, int main_index, int *array, int index, int size)
{
  if(index < size)
  {
    array[index] = main_array[main_index];
    fill_array(main_array, main_index + 1, array, index + 1, size);
  }
}

void get_in_order(int *main_array, int main_index, int *array1, int index1, int size1, int *array2, int index2, int size2)
{
  if(index1 < size1 && index2 < size2)
  {
    if(array1[index1] < array2[index2])
    {
      main_array[main_index] = array1[index1];
      get_in_order(main_array, main_index + 1, array1, index1 + 1, size1, array2, index2, size2);
    }
    else
    {
      main_array[main_index] = array2[index2];
      get_in_order(main_array, main_index + 1, array1, index1, size1, array2, index2 + 1, size2);
    }
  }
  else if(index1 < size1)
  {
    main_array[main_index] = array1[index1];
    get_in_order(main_array, main_index + 1, array1, index1 + 1, size1, array2, index2, size2);
  }
  else if(index2 < size2)
  {
    main_array[main_index] = array2[index2];
    get_in_order(main_array, main_index + 1, array1, index1, size1, array2, index2 + 1, size2);
  }
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