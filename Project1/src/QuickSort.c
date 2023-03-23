/* ========================================================================= *
 * \file QuickSort.c
 * \brief Implementation of the QuickSort algorithm.
 * \author Louan Robert
 * \author Luca Heudt
 * ========================================================================= */

#include "Array.h"
#include "Sort.h"
#include <stdlib.h>

void quickSort(int *a, int s, int e);

static int partition(int *a, int s, int e);

static int randomized_partition(int *a, int s, int e);

static void swap(int *array, int a, int b);

/**
 * \brief Sort an array of integers using the QuickSort algorithm.
 *
 * \param a The array to sort
 * \param s start index
 * \param e end index
 */
void quickSort(int *a, int s, int e) {
   if (s < e) {
      int q = randomized_partition(a, s, e);
      quickSort(a, s, q - 1);
      quickSort(a, q + 1, e);
   }
}

/**
 * \brief Sort an array of integers using the QuickSort algorithm.
 *
 * \param array The array to sort
 * \param length The length of the array
 */
void sort(int *array, size_t length) {
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
static int partition(int *a, int s, int e) {
   int x = a[e]; // pivot
   int i = s - 1;

   for (int j = s; j < e; j++) {
      if (intCmp(a[j], x) <= 0) {
         swap(a, ++i, j);
      }
   }
   swap(a, ++i, e);

   return i;
}

static int randomized_partition(int *a, int s, int e) {
   int i = rand() % (e - s + 1) +
           s; // https://www.geeksforgeeks.org/generating-random-number-range-c/
   swap(a, i, e);
   return partition(a, s, e);
}

/**
 * \brief Swap two elements in an array. (a <- b_0 & b <- a_0)
 *
 * \param array The array to swap elements in.
 * \param a Element a to swap.
 * \param b Element b to swap.
 */
static void swap(int *array, int a, int b) {
   int tmp = array[a];
   array[a] = array[b];
   array[b] = tmp;
}

/************************
 * RANDOMIZED_PARTITION *
 ************************

Sorting times for arrays of size 10000 (1 repetitions)
---------------------------------------------
Array type |    time [s]    |     nb comp.
---------------------------------------------
Sorted     |     0.002680   |     170315.0
Decreasing |     0.001138   |     174038.0
Random     |     0.001029   |     170169.0
~Sorted    |     0.000731   |     164371.0
---------------------------------------------

 ********************
 * NORMAL_PARTITION *
 ********************

Sorting times for arrays of size 10000 (1 repetitions)
---------------------------------------------
Array type |    time [s]    |     nb comp.
---------------------------------------------
Sorted     |     0.235326   |   50014999.0
Decreasing |     0.151092   |   50014999.0
Random     |     0.001006   |     174485.0
~Sorted    |     0.006969   |    1844557.0
---------------------------------------------
 */
