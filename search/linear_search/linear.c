/*
  Code written by Felipe Fraxe Filho
  Just for learning
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define SIZE 1000000

void generate_array(int *array, int size);
void print_array(int *array, int size);
int linear_search(int *array, int size, int num);

int main(void)
{
  srand(time(0));
  int array[SIZE];
  generate_array(array, SIZE);
  int num = rand() / (RAND_MAX / SIZE + 1);
  clock_t t = clock();
  int found = linear_search(array, SIZE, num);
  t = clock() - t;
  found != -1 ? printf("Found %d in position %d\n", num, found + 1) : printf("Couldn't find %d\n", num);
  printf("Took %lf seconds to find it\n", (float) t / CLOCKS_PER_SEC);
  return EXIT_SUCCESS;
}

int linear_search(int *array, int size, int num)
{
  for(int i = 0; i < size; i++)
  {
    if(array[i] == num)
      return i;
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