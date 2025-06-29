#include <stdio.h>
#include <stdlib.h>

static inline void swap(int *num1, int *num2)
{
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

static void print_array(int array[], int length)
{
    for (int i = 0; i < length; i++)
        printf("%d ", array[i]);
    printf("\n");
}

void heap(int array[], int length)
{
    if (length == 1)
    {
        print_array(array, length);
        return;
    }
    
    for (int i = 0; i < length; i++)
    {
        heap(array, length - 1);
        if (length % 2 == 1)
            swap(&array[0], &array[length - 1]);
        else
            swap(&array[i], &array[length - 1]);
    }
}
