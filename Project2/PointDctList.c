/* ========================================================================= *
 * PointDct definition (with List)
 * ========================================================================= */

#include "List.h"
#include "Point.h"
#include "PointDct.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct PointDct_t {
   List *lpoints;
   List *lvalues;
};

PointDct *pdctCreate(List *lpoints, List *lvalues) {
   PointDct *pd = malloc(sizeof(PointDct));
   if (pd == NULL) {
      printf("pdctCreate: allocation error\n");
      return NULL;
   }
   pd->lpoints = lpoints;
   pd->lvalues = lvalues;
   return pd;
}

void pdctFree(PointDct *pd) { free(pd); }

size_t pdctSize(PointDct *pd) { return listSize(pd->lpoints); }

void *pdctExactSearch(PointDct *pd, Point *p) {
   for (LNode *pp = pd->lpoints->head, *pv = pd->lvalues->head; pp != NULL;
        pp = pp->next, pv = pv->next) {
      if (ptCompare(pp->value, p) == 0) {
         return pv->value;
      }
   }
   return NULL;
}

List *pdctBallSearch(PointDct *pd, Point *p, double radius) {
   List *l = listNew();
   if (l == NULL) return NULL;

   radius = radius * radius;
   bool error = false;
   for (LNode *pp = pd->lpoints->head, *pv = pd->lvalues->head; pp != NULL;
        pp = pp->next, pv = pv->next) {
      if (ptSqrDistance(pp->value, p) <= radius) {
         error = error || !listInsertLast(l, pv->value);
      }
   }
   if (error) {
      listFree(l, false);
      return NULL;
   }
   return l;
}
