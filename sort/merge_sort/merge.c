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
#define SIZE 2000000

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
    printf("This method took %lf seconds to sort\n", (double) t / CLOCKS_PER_SEC);
    return EXIT_SUCCESS;
}

void merge_sort(int *array, int low, int high)
{
    if (low >= high)
        return;
    
    int mid = low + (high - low) / 2;
    merge_sort(array, low, mid);
    merge_sort(array, mid + 1, high);
    merge(array, low, mid, high);
}

void merge(int *array, int low, int mid, int high)
{
    int size1 = (mid + 1) - low;
    int size2 = high - mid;
    int array1[size1], array2[size2];

    for(int i = 0, k = low; i < size1; i++, k++)
        array1[i] = array[k];

    for(int j = 0, k = mid + 1; j < size2; j++, k++)
        array2[j] = array[k];

    int i = 0, j = 0, k = low;
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