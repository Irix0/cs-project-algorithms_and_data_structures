/* ========================================================================= *
 * Compute CPU times on random points for a PointDct implementation
 * ========================================================================= */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "List.h"
#include "Point.h"
#include "PointDct.h"

#define N 1000
#define NSEARCH 1000
#define RADIUS 0.1

typedef struct Data_t Data;

struct Data_t {
   Point *point;
};

int main(int argc, char **argv) {

   size_t npoints = N;
   size_t nsearch = NSEARCH;
   double radius = RADIUS;
   clock_t start, end;

   srand(time(NULL));

   if (argc > 1) npoints = atoi(argv[1]);
   if (argc > 2) nsearch = atoi(argv[2]);
   if (argc > 3) radius = strtod(argv[3], NULL);

   size_t ntotal = npoints + nsearch;

   //****************************
   // create data

   printf("Preparation:\n");
   printf("   Generating %zu points...", ntotal);
   Point **lp = malloc(ntotal * sizeof(Point *));
   Data **lv = malloc(ntotal * sizeof(Data *));

   List *lpoints = listNew();
   List *lvalues = listNew();

   for (size_t i = 0; i < ntotal; i++) {
      lp[i] = ptNew((double)rand() / (double)(RAND_MAX),
                    (double)rand() / (double)(RAND_MAX));
      lv[i] = malloc(sizeof(Data));
      lv[i]->point = lp[i];

      if (i < npoints) {
         listInsertLast(lpoints, lp[i]);
         listInsertLast(lvalues, lv[i]);
      }
   }
   printf("Done\n");

   //****************************
   // Create dictionary

   printf("   Creation of the dictionary (%zu points)...", npoints);
   start = clock();
   PointDct *pd = pdctCreate(lpoints, lvalues);
   end = clock();
   printf("Done in %fs\n", ((double)(end - start)) / CLOCKS_PER_SEC);

   //****************************
   // Exact searches

   printf("\nTesting exact searches:\n");
   printf("   %zu positive searches...", nsearch);
   bool error = false;

   start = clock();
   for (size_t i = 0; i < nsearch; i++) {
      int rp = rand() % npoints;
      void *val = pdctExactSearch(pd, lp[rp]);
      if (val == NULL) {
         printf("  Error: one positive point was not found\n");
         error = true;
         break;
      } else if (val != lv[rp]) {
         printf("  Error: associated data is wrong\n");
         error = true;
         break;
      }
   }
   end = clock();
   printf("Done in %fs\n", ((double)(end - start)) / CLOCKS_PER_SEC);
   if (error) printf("   Warning: there were some errors\n");

   printf("   %zu negative searches...", nsearch);
   error = false;
   start = clock();
   for (size_t i = 0; i < nsearch; i++) {
      Point *p = ptNew(-1.0 + (double)rand() / (double)(RAND_MAX),
                       1.0 + (double)rand() / (double)(RAND_MAX));
      void *val = pdctExactSearch(pd, p);
      if (val != NULL) {
         printf("  Error: one negative point was found\n");
         error = true;
      }
      ptFree(p);
   }
   end = clock();
   printf("Done in %fs\n", ((double)(end - start)) / CLOCKS_PER_SEC);

   if (error) printf("   Warning: there were some errors\n");

   //****************************
   // Ball searches

   printf("\nTesting ball searches:\n");
   printf("   %zu ball searches of radius %f...", nsearch, radius);
   error = false;
   double avgsize = 0;

   start = clock();
   for (size_t i = npoints; i < ntotal; i++) {
      List *l = pdctBallSearch(pd, lp[i], radius);
      avgsize += (double)listSize(l) / (double)nsearch;
      listFree(l, false);
   }
   end = clock();
   printf("Done in %fs\n", ((double)(end - start)) / CLOCKS_PER_SEC);
   printf("   Average list size: %f\n", avgsize);

   //****************************
   // Average Node Depth

   /*printf("\nTesting average node depth:\n");

   error = false;
   start = clock();
   double avgdepth = 0;
   for (size_t i = npoints; i < ntotal; i++){
      double depth = ptDctAverageNodeDepth(pd);
      avgdepth += depth / (double)nsearch;
   }
   end = clock();
   printf("Done in %fs\n", ((double)(end - start)) / CLOCKS_PER_SEC);
   printf("   Average node depth: %f\n", avgdepth);*/

   //****************************
   // Free

   pdctFree(pd);
   listFree(lpoints, false);
   listFree(lvalues, false);
   for (size_t i = 0; i < ntotal; i++) {
      ptFree(lp[i]);
      free(lv[i]);
   }
   free(lv);
   free(lp);
}
