/* ========================================================================= *
 * PointDct definition (with BST)
 *
 * \file PointDctBST.c
 * \author Maé Klinkenberg s213722
 * \author Louan Robert s211732
 * \brief PointDct definition (with BST)
 * \date 23/04/2023
 *
 * ========================================================================= */

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "BST.h"
#include "List.h"
#include "Point.h"
#include "PointDct.h"

// Strucures

typedef struct Tuple_t Tuple;

struct Tuple_t {
   void *key;
   void *value;
};

struct PointDct_t {
   BST *t;
};

// Functions prototypes

static int pointCompare(void *p1, void *p2);

// Functions definitions

static int pointCompare(void *p1, void *p2) {
   Point *point1 = (Point *)p1;
   Point *point2 = (Point *)p2;
   return ptCompare(point1, point2);
}

PointDct *pdctCreate(List *lpoints, List *Lvalues) {
   assert(lpoints != NULL && Lvalues != NULL);
   assert(listSize(lpoints) == listSize(Lvalues));

   // Creating BST and PointDct
   BST *t = bstNew(&pointCompare);
   if (t == NULL) {
      return NULL;
   }

   PointDct *pd = malloc(sizeof(PointDct));
   if (pd == NULL) {
      bstFree(t, false, false);
      return NULL;
   }
   pd->t = t;

   // Inserting points and values in BST

   LNode *pp = lpoints->head;
   LNode *pv = Lvalues->head;

   while (pp != NULL) {
      Tuple *tuple = malloc(sizeof(Tuple));
      if (tuple == NULL) {
         bstFree(t, false, true);
         pdctFree(pd);
         return NULL;
      }

      tuple->key = pp->value;
      tuple->value = pv->value;
      if (!bstInsert(t, pp->value, tuple)) {
         bstFree(t, false, true);
         return NULL;
      }

      pp = pp->next;
      pv = pv->next;
   }

   return pd;
}

void pdctFree(PointDct *pd) {
   assert(pd != NULL);
   bstFree(pd->t, false, true);
   free(pd);
}

size_t pdctSize(PointDct *pd) {
   assert(pd != NULL);
   return bstSize(pd->t);
}

void *pdctExactSearch(PointDct *pd, Point *p) {
   assert(pd != NULL && p != NULL);

   Tuple *tuple = bstSearch(pd->t, p);

   if (tuple == NULL) {
      return NULL;
   }

   return tuple->value;
}

List *pdctBallSearch(PointDct *pd, Point *p, double r) {
   assert(pd != NULL && p != NULL && r >= 0);
   if (pd->t == NULL) {
      return NULL;
   }

   List *pre_result;

   Point *minPoint = ptNew(ptGetx(p) - r, ptGety(p) - r);
   if (minPoint == NULL) {
      return NULL;
   }

   Point *maxPoint = ptNew(ptGetx(p) + r, ptGety(p) + r);
   if (minPoint == NULL) {
      ptFree(minPoint);
      return NULL;
   }

   // First we get the list of points between p-r and p+r (using ptCompare)
   pre_result = bstRangeSearch(pd->t, minPoint, maxPoint);

   // Then we remove the points that are not in the circle
   List *result = listNew();
   if (result == NULL) {
      listFree(pre_result, false);
      ptFree(minPoint);
      ptFree(maxPoint);
      return NULL;
   }

   double r2 = r * r;
   LNode *current = pre_result->head;

   bool error = false;
   while (current != NULL) {
      Tuple *t = (Tuple *)current->value;
      Point *currentPoint = (Point *)t->key;

      if (ptSqrDistance(p, currentPoint) <= r2) {
         error = error || !listInsertLast(result, t->value);
      }
      current = current->next;
   }

   listFree(pre_result, false);

   ptFree(minPoint);
   ptFree(maxPoint);

   if (error) {
      listFree(result, false);
      return NULL;
   }

   return result;
}
