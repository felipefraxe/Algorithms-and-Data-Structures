#ifndef MERGE_H
#define MERGE_H

// Prototypes for Merge Sort
void merge_sort(int *array, int left, int right);
void merge(int *array, int left, int mid, int right);
void fill_array(int *main_array, int left, int *array, int index, int size);
void get_in_order(int *main_array, int main_index, int *array1, int index1, int size1, int *array2, int index2, int size2);

#endif