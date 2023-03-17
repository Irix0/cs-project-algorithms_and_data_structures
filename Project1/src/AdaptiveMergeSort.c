/* ========================================================================= *
 * \file AdaptiveMergeSort.c
 * \brief Implementation of the Adaptive Merge Sort algorithm.
 * \author Louan Robert
 * \author Luca Heudt
 * ========================================================================= */

#include "Array.h"
#include "Sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MIN_SIZE 4

int findRun(int *array, size_t start, size_t end, size_t minSize);

static int findSubArray(int *array, size_t start, size_t end, size_t minSize);

static void merge(int tab[], int lo, int mid, int hi, int aux[]);

static void reverse(int *array, size_t start, size_t end);

static void insertionSort(int *array, size_t start, size_t end);

// Find a subarray of minimum size minSize that is sorted in ascending or
// descending order (if descending inverse it)
int findRun(int *array, size_t start, size_t end, size_t minSize) {
   assert(minSize > 0);
   int sub = findSubArray(array, start, end, minSize);
   if (sub == -1) {
      // If no subarray is found, sort from start to start + minSize - 1
      if(end - start < minSize)
         insertionSort(array, start, end);
      else
         insertionSort(array, start, start + minSize-1);
      return start + minSize - 1;
   } else
      return sub;
}

void sort(int *array, size_t length) {
   int *stack = malloc((length/MIN_SIZE + 2) * sizeof(int)), stackSize = 1;
   stack[0] = -1;
   int *aux = malloc(length * sizeof(int));

   int i = 0, j = 0;
   while(i < length) {
      j = findRun(array, i, length, MIN_SIZE);
      stack[stackSize++] = j;
      i = j + 1;
      int A, B, C;
      printf("\nStack : \n");
   // Print stack
   for (int i = 0; i < stackSize; i++) {
      printf("%d ", stack[i]);
   }
      if(stackSize > 3) { // Merge if A <= B + C
         C = stack[stackSize-1] - stack[stackSize - 2];
         B = stack[stackSize - 2] - stack[stackSize - 3];
         A = stack[stackSize - 3] - stack[stackSize - 4];
         if(A <= B + C) {
            if(A <= C) { // Merge A and B
               printf("1. size = %d, A = %d, B = %d, C = %d        ", stackSize, A, B, C);
               merge(array, stack[stackSize -4], stack[stackSize-3], stack[stackSize-2], aux);
               stack[stackSize - 3] = stack[stackSize - 2];
               stack[stackSize - 2] = stack[stackSize - 1];
               stackSize--;
            } else { // A > C : merge B and C
               printf("2. size = %d, A = %d, B = %d, C = %d        ", stackSize, A, B, C);
               merge(array, stack[stackSize - 3]+1, stack[stackSize - 2], stack[stackSize - 1], aux);
               stack[stackSize - 2] = stack[stackSize - 1];
               stackSize--;
            }
         }
      } 
      if (stackSize == 3) { // Merge if B <= C
         C = stack[stackSize-1] - stack[stackSize - 2];
         B = stack[stackSize - 2] - stack[stackSize - 3];
         printf("3. size = %d, B = %d, C = %d        ", stackSize, B, C);

         if(B <= C) { // merge B and C
            merge(array, stack[stackSize - 3]+1, stack[stackSize - 2], stack[stackSize - 1], aux);
            stack[stackSize - 2] = stack[stackSize - 1];
            stackSize--;
         }
      }
   }

   while (stackSize > 2) { // Merge all remaining subarrays
      merge(array, stack[stackSize - 3]+1, stack[stackSize - 2], stack[stackSize - 1], aux);
      stack[stackSize - 2] = stack[stackSize - 1];
      stackSize--;
   }

   free(stack);
   array = aux;
   return;
}

int main() {
   int SIZE = 100;
   int a[SIZE], j = 0;
   // Print array
   for (int i = 0; i < SIZE; i++) {
      a[i] = rand() % 22;
      printf("%d ", a[i]);
   }
   printf("\n");
   sort(a, SIZE);
   printf("\n Sorted array : \n");
   for (int i = 0; i < SIZE; i++) {
      printf("%d ", a[i]);
   }
}

// Returns the index of the last element of the sorted subarray, -1 if not found
static int findSubArray(int *array, size_t start, size_t end, size_t minSize){
    int i = start;
    
   // Find sub array that is sorted ascending
   while (i < end - 1 && intCmp(array[i], array[i + 1]) <= 0)
      i++;
   // Check if subarray is big enough
   if (i - start >= minSize)
      return i;
   // Subarray is too small, look for sub array that is sorted descending
   int j = start;
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
   for (int i = start + 1; i <= end; i++) {
      int j = i;
      while (j > start && intCmp(array[j], array[j - 1]) < 0) {
         int temp = array[j];
         array[j] = array[j - 1];
         array[j - 1] = temp;
         j--;
      }
   }
}
