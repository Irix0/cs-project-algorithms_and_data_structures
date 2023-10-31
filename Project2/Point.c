/* ========================================================================= *
 * Point definition
 * ========================================================================= */

#include "Point.h"
#include <stdio.h>
#include <stdlib.h>

struct Point_t {
   double x;
   double y;
};

Point *ptNew(double x, double y) {
   Point *p = malloc(sizeof(Point));
   if (!p) {
      printf("ptNew: Allocation of point failed\n");
      return NULL;
   }
   p->x = x;
   p->y = y;
   return p;
}

void ptFree(Point *p) { free(p); }

double ptGetx(Point *p) { return p->x; }

double ptGety(Point *p) { return p->y; }

double ptSqrDistance(Point *p1, Point *p2) {
   double dx = p1->x - p2->x;
   double dy = p1->y - p2->y;

   return dx * dx + dy * dy;
}

int ptCompare(Point *p1, Point *p2) {
   if (p1->x < p2->x)
      return -1;
   else if (p1->x > p2->x)
      return +1;
   else if (p1->y < p2->y)
      return -1;
   else if (p1->y > p2->y)
      return +1;
   else
      return 0;
}

void ptPrint(Point *p) { printf("(%f,%f)\n", p->x, p->y); }
