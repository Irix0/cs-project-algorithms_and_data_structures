/* ========================================================================= *
 * Load and query from a file of taxi trips (in csv format)
 * ========================================================================= */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "List.h"
#include "Point.h"
#include "PointDct.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct Trip_t Trip;

struct Trip_t {
   char *tripID;
   char *taxiID;
   char *date;
   double longitude;
   double latitude;
};

// Prototypes
static Point *transformToXY(double longitude, double latitude);
static Point *transformToLL(double x, double y);
static List *parseCsv(const char *filename);
static void printTrip(Trip *trip);
static void freeTrip(Trip *trip);

/* ------------------------------------------------------------------------- *
 * Print information about a trip.
 *
 * PARAMETERS
 * trip       The trip to print
 * ------------------------------------------------------------------------- */

static void printTrip(Trip *trip) {
   printf("(%f, %f) %s %s %s\n", trip->longitude, trip->latitude, trip->tripID,
          trip->taxiID, trip->date);
}

/* ------------------------------------------------------------------------- *
 * Free a Trip object.
 *
 * PARAMETERS
 * trip       The trip to free
 * ------------------------------------------------------------------------- */

static void freeTrip(Trip *trip) {
   free(trip->tripID);
   free(trip->taxiID);
   free(trip->date);
   free(trip);
}

/* ------------------------------------------------------------------------- *
 * Parse a CSV file containing taxi trips.
 * This CSV must have four columns (no header):
 *   1) Trip ID: A unique identifier for the trip
 *   2) Taxi ID: A unique identifier for the taxi
 *   3) Date-time: A string giving the start time (date + time) of the trip
 *   4) Longitude: the longitude of the starting point of the trip (in degree)
 *   5) Latitude: the latitude of the starting point of the trip (in degree)
 *
 * PARAMETERS
 * filename     A null-terminated string containing the name of the CSV file
 *
 * RETURN
 * ltrips       A linked list containing the trips
 * ------------------------------------------------------------------------- */

// Max length of a single line in a .csv file
static const size_t LINE_SIZE = 1024;

static List *parseCsv(const char *filename) {
   printf("Loading file %s", filename);
   fflush(stdout);

   // Opens the file
   FILE *fileObj = fopen(filename, "r");
   if (fileObj == NULL) {
      fprintf(stderr, "Could not open file '%s'. Exiting...\n", filename);
      exit(EXIT_FAILURE);
   }
   List *ltrips = listNew();
   if (!ltrips) {
      fprintf(stderr, "Allocation error. Exiting...\n");
      exit(EXIT_FAILURE);
   }

   // Start reading the file, line by line (N.B.: fgets() reads until next \n or
   // EOF character)
   char line[LINE_SIZE];
   size_t nbLine = 0;
   char delim = ';';
   Trip *trip;

   while (fgets(line, sizeof(line), fileObj) != NULL) {
      if ((nbLine % 50000) == 0) {
         printf(".");
         fflush(stdout);
      }

      trip = malloc(sizeof(Trip));
      if (!trip) {
         fprintf(stderr, "Allocation error at line %zu. Exiting...\n", nbLine);
         exit(EXIT_FAILURE);
      }
      trip->latitude = 0.0;
      trip->longitude = 0.0;
      trip->tripID = NULL;
      trip->taxiID = NULL;
      trip->date = NULL;

      size_t currChar = 0;

      // ---- tripID
      while (line[currChar] != delim)
         currChar++;
      trip->tripID = malloc(sizeof(char) * (currChar + 1));
      if (!trip->tripID) {
         fprintf(stderr, "Allocation error: tripID at line %zu. Exiting...\n",
                 nbLine);
         exit(EXIT_FAILURE);
      }
      memcpy(trip->tripID, line, sizeof(char) * currChar);
      trip->tripID[currChar] = '\0';

      // ---- taxiID
      int start = ++currChar;
      while (line[currChar] != delim)
         currChar++;
      trip->taxiID = malloc(sizeof(char) * (currChar - start + 1));
      if (!trip->taxiID) {
         fprintf(stderr, "Allocation error: taxiID at line %zu. Exiting...\n",
                 nbLine);
         exit(EXIT_FAILURE);
      }
      memcpy(trip->taxiID, line + start, sizeof(char) * (currChar - start));
      trip->tripID[currChar - start] = '\0';

      // ---- Date
      start = ++currChar;
      while (line[currChar] != delim)
         currChar++;
      trip->date = malloc(sizeof(char) * (currChar - start + 1));
      if (!trip->date) {
         fprintf(stderr, "Allocation error: date at line %zu. Exiting...\n",
                 nbLine);
         exit(EXIT_FAILURE);
      }
      memcpy(trip->date, line + start, sizeof(char) * (currChar - start));
      trip->date[currChar - start] = '\0';

      // ---- Longitude and latitude
      start = ++currChar;
      trip->longitude = strtod(line + start, NULL);
      while (line[currChar] != delim)
         currChar++;
      start = ++currChar;
      trip->latitude = strtod(line + start, NULL);

      if (!listInsertLast(ltrips, trip)) {
         fprintf(stderr,
                 "Allocation error: listInsertLast at line %zu. Exiting...\n",
                 nbLine);
         exit(EXIT_FAILURE);
      }
      nbLine++;
   }
   fclose(fileObj);

   printf(" Done (read %zu trips)\n", listSize(ltrips));

   return ltrips;
}

#define REARTH 6371.0
#define PORTOLONG -8.6291
#define PORTOLAT 41.1579

/* ------------------------------------------------------------------------- *
 * Convert longitude and latitude into (x,y) coordinates that respect
 * (approximatively) distances and aeras. After conversion, the euclidean
 * distance between two points represent the distance in km between the
 * corresponding geographical coordinates.
 *
 * PARAMETERS
 * longitude    the longitude of the position (in degress, double)
 * latitude     the latitude of the position (in degress, double)
 * RETURN
 * p            A Point structure with the (x,y) coordinates.
 * ------------------------------------------------------------------------- */

static Point *transformToXY(double longitude, double latitude) {
   double x = REARTH * M_PI * longitude / 180 * cos(PORTOLAT / 180 * M_PI);
   double y = REARTH * M_PI * latitude / 180;

   Point *newp = ptNew(x, y);
   if (!newp) {
      fprintf(stderr, "Allocation error in transformToXY. Exiting...\n");
      exit(EXIT_FAILURE);
   }
   return newp;
}

/* ------------------------------------------------------------------------- *
 * Convert (x,y) obtained from transformToXY back into longitude and latitude
 * values.
 *
 * PARAMETERS
 * x           the x coordinate of the position.
 * y           the y coordinate of the position.
 * RETURN
 * p            A Point structure with the (longitude,latitude).
 * ------------------------------------------------------------------------- */

static Point *transformToLL(double x, double y) {
   double longitude = x / (REARTH * M_PI) * 180 / cos(PORTOLAT / 180 * M_PI);
   double latitude = y / (REARTH * M_PI) * 180;

   Point *newp = ptNew(longitude, latitude);
   if (!newp) {
      fprintf(stderr, "Allocation error in transformToXY. Exiting...\n");
      exit(EXIT_FAILURE);
   }
   return newp;
}

int main(int argc, char **argv) {

   if (argc != 4) {
      printf("Usage: ./testtaxi longitude latitude radius\n");
      printf("(longitude and latitude in degrees, radius in km.)\n");
      printf("Example: ./testtaxi -8.6291 41.1579 0.5\n");
      exit(EXIT_FAILURE);
   }

   double longitude = strtod(argv[1], NULL);
   double latitude = strtod(argv[2], NULL);
   double radius = strtod(argv[3], NULL);
   printf("Testing long=%f, lat=%f, radius=%f\n", longitude, latitude, radius);

   Point *query = transformToXY(longitude, latitude);

   char *filename = "taxitripsporto.csv";
   List *ltrips = parseCsv(filename);

   printf("Creating points...");
   List *lpoints = listNew();
   for (LNode *p = ltrips->head; p != NULL; p = p->next) {
      Point *newp = transformToXY(((Trip *)p->value)->longitude,
                                  ((Trip *)p->value)->latitude);
      listInsertLast(lpoints, newp);
   }
   printf("Done\n");

   printf("Creating dictionary...");
   clock_t start = clock();
   PointDct *pd = pdctCreate(lpoints, ltrips);
   clock_t end = clock();
   printf("Done in %fs\n", ((double)(end - start)) / CLOCKS_PER_SEC);

   printf("Searching...");
   start = clock();
   List *l = pdctBallSearch(pd, query, radius);
   end = clock();
   printf("Done in %fs\n", ((double)(end - start)) / CLOCKS_PER_SEC);
   printf("%zu trips found at the position\n", listSize(l));

   if (listSize(l) > 0) {
      if (listSize(l) > 10) printf("First 10 trips:\n");
      int i = 0;
      for (LNode *p = l->head; p != NULL && i < 10; p = p->next, i++) {
         printf("  ");
         printTrip(p->value);
      }
   }

   listFree(l, false);
   pdctFree(pd);
   listFree(lpoints, true);
   for (LNode *p = ltrips->head; p != NULL; p = p->next)
      freeTrip(p->value);
   listFree(ltrips, false);
}
