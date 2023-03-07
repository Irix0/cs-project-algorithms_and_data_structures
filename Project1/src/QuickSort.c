/* ========================================================================= *
 * \file QuickSort.c
 * \brief Implementation of the QuickSort algorithm.
 * \author Louan Robert
 * \author Luca Heudt
 * ========================================================================= */

#include "Sort.h"
#include "Array.h"

/**
 * \brief Sort an array of integers using the QuickSort algorithm.
 * 
 * \param array The array to sort
 * \param length The length of the array
 */
void sort(int *array, size_t length)
{
    quickSort(array, 0, length - 1);
}

/**
 * \brief Partition an array around a pivot.
 * 
 * \param a Array to partition
 * \param s start index
 * \param e end index
 * \result int 
 */
int partition(int *a, int s, int e) {
    int x = a[e]; // pivot
    int i = s - 1; 

    for(int j = s; j < e; j++) {
        if(intCmp(a[j], x) <= 0) {
            swap(a, ++i, j);
        }
    }
    swap(a, ++i, e);

    return i;
}

/**
 * \brief Sort an array of integers using the QuickSort algorithm.
 * 
 * \param a The array to sort
 * \param s start index
 * \param e end index
 */
void quickSort(int *a, int s, int e) {
    if(intCmp(s, e) < 0) {
        int q = partition(a, s, e);
        quickSort(a, s, q - 1);
        quickSort(a, q + 1, e);
    }
}

/**
 * \brief Swap two elements in an array. (a <- b_0 & b <- a_0)
 * 
 * \param array The array to swap elements in.
 * \param a Element a to swap.
 * \param b Element b to swap.
 */
void swap(int *array, int a, int b){
    int tmp = array[a];
    array[a] = array[b];
    array[b] = tmp;
}
