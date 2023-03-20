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
#define PRE_SIZE 21

int findRun(int *array, size_t start, size_t end, size_t minSize);

static int findSubArray(int *array, size_t start, size_t end, size_t minSize);

static void merge(int tab[], int lo, int mid, int hi, int aux[]);

static void reverse(int *array, size_t start, size_t end);

static void insertionSort(int *array, size_t start, size_t end);

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
   while (j < end - 1 && intCmp(array[j], array[j + 1]) > 0) //why >0 and not >=0 ? cause even in descending order,
      j++;                                                   // if 2 elements are equal it's still good I guess.
   // Check if subarray is big enough
   if (j - start >= minSize - 1) { // should be minSize -1 I think, as j is the INDEX of the last element, and
      reverse(array, start, j);    // minSize is the value of the minimum size (if j = 3, the subarray has a size
      return j;                    //of 4, which is good)
   }
   return -1;
}

// Find a subarray of minimum size minSize that is sorted in ascending or
// descending order (if descending, inverse it) and return the index of its last element
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
   stack[0] = 0; // changed value to 0 (was -1)
   int *aux = calloc(length,sizeof(int));

   int i = 0, j = 0, skip = 0;
   while(i < length) {
      j = findRun(array, i, length, MIN_SIZE);
      stack[stackSize++] = j; // put j in the stack and increment stacksize
      i = j + 1; //set the start of the next subarray to the element after the end of the previous one
      int A, B, C;
      if(stackSize > 3) { // Merge if A <= B + C
         C = stack[stackSize-1] - stack[stackSize - 2];
         B = stack[stackSize - 2] - stack[stackSize - 3];
         A = stack[stackSize - 3] - stack[stackSize - 4];
         if(A <= B + C) {
            if(A <= C) { // Merge A and B
               //printf("1. size = %d, A = %d, B = %d, C = %d        ", stackSize, A, B, C);
               if(stackSize > 4)
                  skip = 1;
               else
                  skip = 0;
               merge(array, stack[stackSize -4]+skip, stack[stackSize-3], stack[stackSize-2], aux); // maybe +1 here cause you have to skip
               stack[stackSize - 3] = stack[stackSize - 2];                                         // the subarrays before A (that's the "skip")
               stack[stackSize - 2] = stack[stackSize - 1];                                         //but what if there is more then one array to skip ???
               stackSize--;                                                                         //maybe skip = stackSize - 4 ?
            } else { // A > C : merge B and C
               // printf("2. size = %d, A = %d, B = %d, C = %d        ", stackSize, A, B, C);
               merge(array, stack[stackSize - 3]+1, stack[stackSize - 2], stack[stackSize - 1], aux); // +1 here cause you have to skip A
               stack[stackSize - 2] = stack[stackSize - 1];
               stackSize--;
            }
         }
      } 
      if (stackSize == 3) { // Merge if B <= C
         C = stack[stackSize-1] - stack[stackSize - 2];
         B = stack[stackSize - 2] - stack[stackSize - 3];
         // printf("3. size = %d, B = %d, C = %d        ", stackSize, B, C);

         if(B <= C) { // merge B and C
            merge(array, stack[stackSize - 3], stack[stackSize - 2], stack[stackSize - 1], aux);
            stack[stackSize - 2] = stack[stackSize - 1];
            stackSize--;
         }
      }
   }

   printf("\nArray before final merge :");
   for (int i = 0; i < length; i++) {
      printf("%d ", array[i]);
   }
   printf("\n");
   printf("----%d,%d,%d\n", stack[stackSize - 3], stack[stackSize - 2], stack[stackSize - 1]-1);

   while (stackSize > 2) { // Merge all remaining subarrays
      merge(array, stack[stackSize - 3], stack[stackSize - 2], stack[stackSize - 1], aux);
      stack[stackSize - 2] = stack[stackSize - 1];
      stackSize--;
   }

   free(stack);
   free(aux);
   return;
}

static void array_copy(int *base, int *copy, int size){
   for(int i = 0;i<size;i++)
      copy[i] = base[i];
}

int main() {
   int SIZE = PRE_SIZE;
   int a[SIZE], j = 0;
   int *copy = malloc(PRE_SIZE * sizeof(int));
   // Print array
   for (int i = 0; i < SIZE; i++) {
      a[i] = rand() % 100;
      //a[i] = i + rand() % 3;
      printf("%d ", a[i]);
   }
   printf("\n");
   array_copy(a,copy,PRE_SIZE);


   sort(a, SIZE);
   printf("\n Sorted array : \n");
   for (int i = 0; i < SIZE; i++) {
      printf("%d ", a[i]);
   }

   insertionSort(copy,0,PRE_SIZE-1);

   printf("\n InsertionSorted array : \n ");
   for (int i = 0; i < SIZE; i++) {
      printf("%d ", copy[i]);
   }
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

static void merge (int tab[], int lo, int mid, int hi, int aux[]) {
   int i = lo, j = mid + 1 ;

   for (int k = lo; k <= hi; k++){

      if (i == mid+1){
         aux[k] = tab[j++];
      }

      else if (j == hi + 1)
         aux[k] = tab[i++];

      else if (intCmp(tab[i], tab[j]) < 0){ // i < j
         aux[k] = tab[i++];
      }
      else{
         aux[k] = tab[j++];
      }
      
   }
   for (int k = lo; k <= hi; k++)
      tab[k] = aux[k];

}

// TO DO : POURQUOI çA FONCTIONNE PAS SI LE TABLEAU A UNE TAILLE DIFFERENTE DE K * MINSIZE ? probablement quand ça essaie de faire
//         le dernier subarray de taille minSize, ou lors de la fusion finale.

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
