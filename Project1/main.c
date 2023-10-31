#include "Array.h"
#include "Sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static const size_t ARRAY_LENGTH = 10000;
static const size_t NBREP = 1;
static const float SWAPPROP = 0.01;

/* Prototypes */

/* ------------------------------------------------------------------------- *
 * Compute the CPU time (in seconds) used by the Sort function.
 *
 * PARAMETERS
 * array        Array to sort
 * length       Number of elements in the array
 *
 * RETURN
 * seconds      The number of seconds used by Sort
 * ------------------------------------------------------------------------- */
static double cpuTimeUsedToSort(int *array, size_t length) {
   clock_t start = clock();
   sort(array, length);
   clock_t end = clock();

   // Check that the array is sorted
   size_t i = 0;
   while (i < length - 1 && array[i] <= array[i + 1])
      i++;
   if (i < length - 1)
      printf("Error: the array is not correctly sorted %zu\n", i);
   return ((double)(end - start)) / CLOCKS_PER_SEC;
}

/* ------------------------------------------------------------------------- *
 * Main
 * ------------------------------------------------------------------------- */
int main(int argc, char **argv) {
   size_t length = ARRAY_LENGTH;
   size_t nbRepetitions = NBREP;
   float swapProp = SWAPPROP;

   srand(time(NULL)); // Use an integer seed to get a fix sequence

   if (argc > 1) length = atoi(argv[1]);
   if (argc > 2) nbRepetitions = atoi(argv[2]);

   printf("Sorting times for arrays of size %zu (%zu repetitions)\n", length,
          nbRepetitions);
   printf("---------------------------------------------\n");
   printf("Array type |    time [s]    |     nb comp.\n");
   printf("---------------------------------------------\n");

   // ---------------------------- Sorted array ---------------------------- //
   double sec = 0.0;
   double nbComp = 0.0;
   for (size_t i = 0; i < nbRepetitions; i++) {

      int *sorted = createSortedArray(length);
      if (!sorted) {
         fprintf(stderr, "Could not create sorted array. Aborting...\n");
         return EXIT_FAILURE;
      }

      resetCounter();
      sec += cpuTimeUsedToSort(sorted, length) / nbRepetitions;
      nbComp += (double)getCounter() / (double)nbRepetitions;
      free(sorted);
   }
   printf("Sorted     | %12.6f   | %12.1f\n", sec, nbComp);

   // -------------------------- Decreasing array -------------------------- //
   sec = 0.0;
   nbComp = 0.0;
   for (size_t i = 0; i < nbRepetitions; i++) {
      int *decreasing = createDecreasingArray(length);
      if (!decreasing) {
         fprintf(stderr, "Could not create decreasing array. Aborting...\n");
         return EXIT_FAILURE;
      }

      resetCounter();
      sec += cpuTimeUsedToSort(decreasing, length) / nbRepetitions;
      nbComp += (double)getCounter() / (double)nbRepetitions;
      free(decreasing);
   }
   printf("Decreasing | %12.6f   | %12.1f\n", sec, nbComp);

   // ---------------------------- Random array ---------------------------- //
   sec = 0.0;
   nbComp = 0.0;
   for (size_t i = 0; i < nbRepetitions; i++) {
      int *random = createRandomArray(length);
      if (!random) {
         fprintf(stderr, "Could not create random array. Aborting...\n");
         return EXIT_FAILURE;
      }

      resetCounter();
      sec += cpuTimeUsedToSort(random, length) / nbRepetitions;
      nbComp += (double)getCounter() / (double)nbRepetitions;
      free(random);
   }
   printf("Random     | %12.6f   | %12.1f\n", sec, nbComp);

   // ------------------------ Almost sorted array ------------------------ //
   sec = 0.0;
   nbComp = 0.0;
   for (size_t i = 0; i < nbRepetitions; i++) {
      int *almostsorted = createAlmostSortedArray(length, swapProp);
      if (!almostsorted) {
         fprintf(stderr, "Could not create random array. Aborting...\n");
         return EXIT_FAILURE;
      }

      resetCounter();
      sec += cpuTimeUsedToSort(almostsorted, length) / nbRepetitions;
      nbComp += (double)getCounter() / (double)nbRepetitions;
      free(almostsorted);
   }
   printf("~Sorted    | %12.6f   | %12.1f\n", sec, nbComp);
   printf("---------------------------------------------\n");

   return EXIT_SUCCESS;
}
