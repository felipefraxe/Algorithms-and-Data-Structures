/*
  Code written by Felipe Fraxe Filho
  rightust for learning
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "quick.h"

// Define Array's size
#define SIZE 2000000

void swap(void *elem1, void *elem2, size_t size);
void generate_array(int *array, int size);
void print_array(int *array, int size);
int stringcmp(const void *string1, const void *string2);
int intcmp(const void *ptr1, const void *ptr2);

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

  return 0;
}

int intcmp(const void *num1, const void *num2)
{
  return *(int *)num1 - *(int *)num2;
}

void quick_sort(void *array, size_t size, int left, int right, int (*cmp)(const void *, const void *))
{
  if(left >= right)
    return;
  int i = left, j = right;
  partition(array, size, &i, &j, cmp);
  if(left < j)
    quick_sort(array, size, left, j, cmp);
  if(i < right)
    quick_sort(array, size, i, right, cmp);
}

void partition(void *array, size_t size, int *left, int *right, int (*cmp)(const void *, const void *))
{
  int mid = *left + ((*right - *left) / 2);
  void *pivot = array + (mid * size);

  if(cmp((array + (*left * size)), pivot) > 0)
    swap((array + (*left * size)), pivot, size);

  if(cmp((array + (*right * size)), pivot) < 0)
    swap((array + (*right * size)), pivot, size);

  if(cmp((array + (*left * size)), pivot) > 0)
    swap((array + (*left * size)), pivot, size);

  pivot = array + (*right * size);
  while(*left <= *right)
  {
    while(cmp((array + (*left * size)), pivot) < 0)
      (*left)++;
    while(cmp((array + (*right * size)), pivot) > 0)
      (*right)--;
    if(*left <= *right)
    {
      swap((array + (*left * size)), (array + (*right * size)), size);
      (*left)++;
      (*right)--;
    }
  }
}

void swap(void *elem1, void *elem2, size_t size)
{
  char *ptr1 = (char *) elem1, *ptr2 = (char *) elem2;
  while(size-- > 0)
  {
    char tmp = *ptr1;
    *ptr1++ = *ptr2;
    *ptr2++ = tmp;
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