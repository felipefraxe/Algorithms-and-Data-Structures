#ifndef MERGE_H
#define MERGE_H

// Prototypes for Merge Sort
void merge_sort(int array[], int size);
void msort(int array[], int aux[], int lo, int hi);
void merge(int array[], int aux[], int lo, int mid, int hi);

#endif