/* ========================================================================= *
 * \file AdaptiveMergeSort.c
 * \brief Implementation of the Adaptive Merge Sort algorithm.
 * \author Louan Robert
 * \author Luca Heudt
 * ========================================================================= */

#include "Array.h"
#include "Sort.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define MIN_SIZE 32

int findRun(int *array, size_t start, size_t end, size_t minSize);

static int findSubArray(int *array, size_t start, size_t end, size_t minSize);

static void merge(int tab[], int lo, int mid, int hi, int aux[]);

static void reverse(int *array, size_t start, size_t end);

static void insertionSort(int *array, size_t start, size_t end);

// Find a subarray of minimum size minSize that is sorted in ascending or
// descending order (if descending inverse it)
int findRun(int *array, size_t start, size_t end, size_t minSize) {
   assert(minSize > 0);
   if(!array)
      return -2;

   int sub = findSubArray(array, start, end, minSize);
   if (sub == -1) {
      // If no subarray is found, sort from start to start + minSize - 1
      if (end - start < minSize) {
         insertionSort(array, start, end);
         return end;
      } else {
         insertionSort(array, start, start + minSize - 1);
         return start + minSize - 1;
      }
   } else
      return sub;
}

void sort(int *array, size_t length) {
   if(!array)
      return;


   int *stack = malloc((length / MIN_SIZE + 2) * sizeof(int)), stackSize = 1;
   stack[0] = 0;
   int *aux = malloc(length * sizeof(int));

   size_t i = 0;
   while (i < length) {
      i = findRun(array, i, length, MIN_SIZE) + 1;
      stack[stackSize++] = i;

      if (stackSize > 3) {
         int a = stack[stackSize - 1] - stack[stackSize - 2];
         int b = stack[stackSize - 2] - stack[stackSize - 3];
         int c = stack[stackSize - 3] - stack[stackSize - 4];
         if (a <= b + c) {
            if (a >= c) { // merge a with b
               merge(array, stack[stackSize - 4] - 1, stack[stackSize - 3],
                     stack[stackSize - 2] - 1, aux);
               stack[stackSize - 2] = stack[stackSize - 1];
               stackSize--;
            }
         } else { // merge b with c
            merge(array, stack[stackSize - 3] - 1, stack[stackSize - 2],
                  stack[stackSize - 1] - 1, aux);
            stack[stackSize - 3] = stack[stackSize - 2];
            stack[stackSize - 2] = stack[stackSize - 1];
            stackSize--;
         }
      } else if (stackSize == 3) {
         int b = stack[stackSize - 1] - stack[stackSize - 2];
         int c = stack[stackSize - 2] - stack[stackSize - 3];
         if (b <= c) { // merge b with c
            merge(array, stack[stackSize - 3] - 1, stack[stackSize - 2],
                  stack[stackSize - 1] - 1, aux);
            stack[stackSize - 2] = stack[stackSize - 1];
            stackSize--;
         }
      }
   }

   // Merge remaining subarrays
   while (stackSize > 2) {
      merge(array, stack[stackSize - 1] - 1, stack[stackSize - 2],
            stack[stackSize - 3] - 1, aux);
      stackSize--;
   }
   free(aux);
   free(stack);

   return;
}


// Returns the index of the last element of the sorted subarray, -1 if not found
static int findSubArray(int *array, size_t start, size_t end, size_t minSize) {
   size_t i = start;

   // Find sub array that is sorted ascending
   while (i < end - 1 && intCmp(array[i], array[i + 1]) <= 0)
      i++;
   // Check if subarray is big enough
   if (i - start >= minSize) return i;
   // Subarray is too small, look for sub array that is sorted descending
   size_t j = start;
   while (j < end - 1 && intCmp(array[j], array[j + 1]) > 0)
      j++;
   // Check if subarray is big enough
   if (j - start >= minSize) {
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
   if (lo == -1) lo = 0;
   if (mid == -1) // :(
      mid = 0;
   if (hi == -1) hi = 0;
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

static void insertionSort(int *array, size_t start, size_t end) {
   if(!array)
      return;

   for (size_t i = start + 1; i <= end; i++) {
      size_t j = i;
      while (j > start && intCmp(array[j], array[j - 1]) < 0) {
         int temp = array[j];
         array[j] = array[j - 1];
         array[j - 1] = temp;
         j--;
      }
   }
}
