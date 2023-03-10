/* ========================================================================= *
 * \file AdaptiveMergeSort.c
 * \brief Implementation of the Adaptive Merge Sort algorithm.
 * \author Louan Robert
 * \author Luca Heudt
 * ========================================================================= */

#include "Array.h"
#include "Sort.h"
#include <stdio.h>

int findRun(int *array, size_t start, size_t end, size_t minSize);

static int findSubArray(int *array, size_t start, size_t end, size_t minSize);

static void merge(int tab[], int lo, int mid, int hi, int aux[]);

static void reverse(int *array, size_t start, size_t end);

static void insertionSort(int *array, size_t end);

// Find a subarray of minimum size minSize that is sorted in ascending or
// descending order (if descending inverse it)
int findRun(int *array, size_t start, size_t end, size_t minSize) {
   int sub = findSubArray(array, start, end, minSize);
   if (sub > -1) {
      return sub;
   } else if (sub == -1) {
      // If no subarray is found, sort from start to start + minSize - 1
      insertionSort(array, minSize);
      return minSize - 1;
   } else {
      return -1; // Error, should be unreachable
   }
      
}

void sort(int *array, size_t length) {

   // to be completed
   return;
}

int main() {
   int a[] = {4, 1, 7, 2, 5, 3};
   printf("desc : %d \n", findRun(a, 0, 5, 3));
   // Print array
   for (int i = 0; i < 9; i++) {
      printf("%d ", a[i]);
   }
}

// Returns the index of the last element of the sorted subarray, -1 if not found
static int findSubArray(int *array, size_t start, size_t end, size_t minSize){
    int i = start;
   // Find sub array that is sorted ascending
   while (i < end && intCmp(array[i], array[i + 1]) <= 0)
      i++;

   // Check if subarray is big enough
   if (i - start + 1 >= minSize) 
      return i;

   // Subarray is too small, look for sub array that is sorted descending

   int j = start;
   while (j < end && intCmp(array[j], array[j + 1]) > 0)
      j++;

   // Check if subarray is big enough
   if (j - start + 1 >= minSize) {
      reverse(array, start, j);
      return j;
   }
   return -1;
}

static void reverse(int *array, size_t start, size_t end) {
   int temp;
   while (start < end) {
      temp = array[start];
      array[start] = array[end];
      array[end] = temp;
      start++;
      end--;
   }
}

static void merge(int tab[], int lo, int mid, int hi, int aux[]) {
   int i = lo, j = mid;

   for (int k = lo; k <= hi; k++)
      if (i == mid)
         aux[k] = tab[j++];
      else if (j == hi + 1)
         aux[k] = tab[i++];
      else if (intCmp(tab[i], tab[j]) < 0)
         aux[k] = tab[i++];
      else
         aux[k] = tab[j++];

   for (int k = lo; k <= hi; k++)
      tab[k] = aux[k];
}

static void insertionSort(int *array, size_t end) {
   for (int i = 1; i <= end; i++) {
      int j = i;
      while (j > 0 && intCmp(array[j], array[j - 1]) < 0) {
         int temp = array[j];
         array[j] = array[j - 1];
         array[j - 1] = temp;
         j--;
      }
   }
}
