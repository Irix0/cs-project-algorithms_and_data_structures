/* ========================================================================= *
 * \file HeapSort.c
 * \brief Implementation of the HeapSort algorithm.
 * \author Louan Robert
 * \author Luca Heudt
 * ========================================================================= */

#include "Sort.h"
#include <stdlib.h>

void max_heapify(int *A, int i, int length);
void build_max_heap(int *A, size_t length);
static void swap(int *array, int a, int b);

void sort(int *array, size_t length)
{
    build_max_heap(array, length);
    for(int i = length - 1;i>0; i--){
        swap(array,i,0);
        length--;
        max_heapify(array,0, length);
    }
    return;
}

void max_heapify(int *A, int i, int length){
    int l = 2*i;
    int r = 2*i + 1;
    int largest;
    if (l < length && A[l] > A[i])
        largest = l;
    else 
        largest = i;

    if (r<length && A[r] > A[largest])
        largest = r;

    if (largest != i){
        swap(A,i,largest);
        max_heapify(A,largest, length);
    }

}

void build_max_heap(int *A, size_t length){
    for(int i = length/2 - 1;i>=0;i--)
        max_heapify(A,i,length);
}

static void swap(int *array, int a, int b){
   int tmp = array[a];
   array[a] = array[b];
   array[b] = tmp;
}
