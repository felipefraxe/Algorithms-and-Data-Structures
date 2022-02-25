/*
  Code written by Felipe Fraxe Filho
  Just for learning
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "quick_sort/quick.h"
#define SIZE 1000000

void generate_array(int *array, int size);
void print_array(int *array, int size);
int binary_search(int *array, int left, int right, int num);

int main(void)
{
  srand(time(0));
  int array[SIZE];
  generate_array(array, SIZE);
  quick_sort(array, 0, SIZE - 1);
  int num = rand() / (RAND_MAX / SIZE + 1);
  clock_t t = clock();
  int found = binary_search(array, 0, SIZE-1, num);
  t = clock() - t;
  found != -1 ? printf("Found %d in position %d\n", num, found + 1) : printf("Couldn't find %d\n", num);
  printf("Took %lf seconds to find it\n", (double) t / CLOCKS_PER_SEC);
  return EXIT_SUCCESS;
}

int binary_search(int *array, int left, int right, int num)
{
  while(left <= right)
  {
    int mid = (left + right) / 2;
    if(array[mid] == num)
      return mid;
    if(array[mid] < num)
      left = mid + 1;
    else
      right = mid - 1;
  }
  return -1;
  

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