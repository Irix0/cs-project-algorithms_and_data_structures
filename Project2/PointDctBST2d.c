/* ========================================================================= *
 * PointDct definition (with BST2d)
 *
 * \file PointDctBST2d.c
 * \author Maé Klinkenberg s213722
 * \author Louan Robert s211732
 * \brief PointDct definition (with BST2d)
 * \date 23/04/2023
 *
 * ========================================================================= */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "BST2d.h"
#include "List.h"
#include "Point.h"
#include "PointDct.h"

// Structures

struct PointDct_t {
   BST2d *t;
};

// Functions definitions

PointDct *pdctCreate(List *lpoints, List *Lvalues) {
   assert(lpoints != NULL && Lvalues != NULL);
   assert(listSize(lpoints) == listSize(Lvalues));

   BST2d *t = bst2dNew();
   if (t == NULL) {
      return NULL;
   }

   PointDct *pd = malloc(sizeof(PointDct));
   if (pd == NULL) {
      bst2dFree(t, false, false);
      return NULL;
   }
   pd->t = t;

   LNode *pp = lpoints->head;
   LNode *pv = Lvalues->head;
   while (pp != NULL) {
      if (!bst2dInsert(t, pp->value, pv->value)) {
         bst2dFree(t, false, false);
         return NULL;
      }
      pp = pp->next;
      pv = pv->next;
   }

   return pd;
}

void pdctFree(PointDct *pd) {
   bst2dFree(pd->t, false, false);
   free(pd);
}

size_t pdctSize(PointDct *pd) {
   assert(pd != NULL);
   return bst2dSize(pd->t);
}

void *pdctExactSearch(PointDct *pd, Point *p) {
   assert(pd != NULL);
   return bst2dSearch(pd->t, p);
}

List *pdctBallSearch(PointDct *pd, Point *p, double r) {
   assert(pd != NULL);
   return bst2dBallSearch(pd->t, p, r);
}
