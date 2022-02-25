/*
  Code written by Felipe Fraxe Filho
  Just for learning
*/

#include <stdio.h>
#include <stdlib.h>

#include "quick.h"
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