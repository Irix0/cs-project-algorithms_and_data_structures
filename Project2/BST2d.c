/* ========================================================================= *
 * BST2d definition
 *
 * \file BSTC2d.c
 * \author Maé Klinkenberg s213722
 * \author Louan Robert s211732
 * \brief BST2d definition
 * \date 23/04/2023
 *
 * ========================================================================= */

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "BST2d.h"
#include "List.h"
#include "Point.h"

// Structures

typedef struct BNode2d_t BNode2d;

struct BNode2d_t {
   BNode2d *left;
   BNode2d *right;
   Point *key;
   void *value;
   int depth;
};

struct BST2d_t {
   BNode2d *root;
   size_t size;
};

// Prototypes of static functions

static BNode2d *bn2dNew(Point *key, void *value);

static void bst2dFreeRec(BNode2d *n, bool freeKey, bool freeValue);

/**
 * \brief Traverse the BST2d and does a ball search
 * 
 * \param node Current node to traverse
 * \param result List of the values that are in the searched range
 * \param q Point to range from
 * \param r Range of the ball search
 * \param depth Current depth of the node
 * \result true Success
 * \result false Failure (allocation error)
 */
static bool bst2dTraverseBallSearch(BNode2d *node, List *result, Point *q, double r,
                             int depth);
/**
 * \brief Traverse the BST2d to sum the depths and the number of nodes
 * 
 * \param node Current node to traverse
 * \param depth Current node depth
 * \param total_depth Summed depth of all the nodes
 * \param num_keys Number of nodes
 */
static void bst2dTraverse(BNode2d *node, int depth, int *total_depth, int *num_keys);

// Function definitions

static BNode2d *bn2dNew(Point *key, void *value) {
   BNode2d *n = malloc(sizeof(BNode2d));
   if (n == NULL) {
      printf("bn2dNew: allocation error\n");
      return NULL;
   }
   n->left = NULL;
   n->right = NULL;
   n->key = key;
   n->value = value;
   return n;
}

BST2d *bst2dNew(void) {
   BST2d *bst2d = malloc(sizeof(BST2d));
   if (bst2d == NULL) {
      printf("bst2dNew: allocation error");
      return NULL;
   }
   bst2d->root = NULL;
   bst2d->size = 0;
   return bst2d;
}

static void bst2dFreeRec(BNode2d *n, bool freeKey, bool freeValue) {
   if (n == NULL) return;
   bst2dFreeRec(n->left, freeKey, freeValue);
   bst2dFreeRec(n->right, freeKey, freeValue);
   if (freeKey) ptFree(n->key);
   if (freeValue) free(n->value);
   free(n);
}

void bst2dFree(BST2d *bst2d, bool freeKey, bool freeValue) {
   assert(bst2d != NULL);
   bst2dFreeRec(bst2d->root, freeKey, freeValue);
   free(bst2d);
}

size_t bst2dSize(BST2d *bst2d) {
   assert(bst2d != NULL);
   return bst2d->size;
}

bool bst2dInsert(BST2d *b2d, Point *point, void *value) {
   assert(b2d != NULL);
   if (b2d->root == NULL) {
      b2d->root = bn2dNew(point, value);
      b2d->size++;
      return true;
   }

   BNode2d *n = b2d->root;
   int depth = 0;
   Point *currpt;
   while (n != NULL) {
      currpt = n->key;
      if (!(depth % 2)) {                       // compare x
         if (ptGetx(point) >= ptGetx(currpt)) { // right
            if (n->right == NULL) {             // insert point right
               n->right = bn2dNew(point, value);
               b2d->size++;
               return true;
            } else { // continue search in right subtree
               n = n->right;
            }                      // end if
         } else {                  // left
            if (n->left == NULL) { // insert point left
               n->left = bn2dNew(point, value);
               b2d->size++;
               return true;
            } else { // continue search in left subtree
               n = n->left;
            }                                   // end if
         }                                      // end if
      } else {                                  // compare y
         if (ptGety(point) >= ptGety(currpt)) { // right
            if (n->right == NULL) {             // insert point right
               n->right = bn2dNew(point, value);
               b2d->size++;
               return true;
            } else { // continue search in right subtree
               n = n->right;
            }                      // end if
         } else {                  // left
            if (n->left == NULL) { // insert point left
               n->left = bn2dNew(point, value);
               b2d->size++;
               return true;
            } else { // continue search in left subtree
               n = n->left;
            } // end if
         }    // end if
      }       // end if
      depth++;
   }
   return false;
}

void *bst2dSearch(BST2d *b2d, Point *q) {
   assert(b2d != NULL);
   BNode2d *n = b2d->root;
   int depth = 0;
   Point *currpt;
   while (n != NULL) {
      currpt = n->key;
      if (!(depth % 2)) { // compare x
         if (ptGetx(q) == ptGetx(currpt)) {
            if (ptGety(q) == ptGety(currpt)) {
               return n->value;
            } else {
               if (ptGety(q) >= ptGety(currpt)) {
                  n = n->right;
               } else {
                  n = n->left;
               }
            }
         } else {
            if (ptGetx(q) >= ptGetx(currpt)) {
               n = n->right;
            } else {
               n = n->left;
            }
         }
      } else { // compare y
         if (ptGety(q) == ptGety(currpt)) {
            if (ptGetx(q) == ptGetx(currpt)) {
               return n->value;
            } else {
               if (ptGetx(q) >= ptGetx(currpt)) {
                  n = n->right;
               } else {
                  n = n->left;
               }
            }
         } else {
            if (ptGety(q) >= ptGety(currpt)) {
               n = n->right;
            } else {
               n = n->left;
            }
         }
      }
      depth++;
   }
   return NULL;
}

static bool bst2dTraverseBallSearch(BNode2d *node, List *result, Point *q, double r,
                             int depth) {
   if (node == NULL)
      return true;

   bool error = false;

   double r2 = r * r;
   if (ptSqrDistance(q, node->key) <= r2) {
      error = error || !listInsertLast(result, node->value);
   }

   if(error) {
      printf("bst2dTraverseBallSearch: allocation error while adding to the list. \n Stopping... \n");
      return false;
   }

   if (!(depth % 2)) { // compare x
      if (ptGetx(q) + r <= ptGetx(node->key)) {
         bst2dTraverseBallSearch(node->left, result, q, r, depth + 1);
      } else if (ptGetx(q) - r >= ptGetx(node->key)) {
         bst2dTraverseBallSearch(node->right, result, q, r, depth + 1);
      } else {
         bst2dTraverseBallSearch(node->left, result, q, r, depth + 1);
         bst2dTraverseBallSearch(node->right, result, q, r, depth + 1);
      }
   } else { // compare y
      if (ptGety(q) + r <= ptGety(node->key)) {
         bst2dTraverseBallSearch(node->left, result, q, r, depth + 1);
      } else if (ptGety(q) - r >= ptGety(node->key)) {
         bst2dTraverseBallSearch(node->right, result, q, r, depth + 1);
      } else {
         bst2dTraverseBallSearch(node->left, result, q, r, depth + 1);
         bst2dTraverseBallSearch(node->right, result, q, r, depth + 1);
      }
   }
   return true;
}

List *bst2dBallSearch(BST2d *bst2d, Point *q, double r) {
   assert(bst2d != NULL && q != NULL && r >= 0);
   List *result = listNew();
   if (bst2d->root == NULL) {
      return result;
   }
   bool error = !bst2dTraverseBallSearch(bst2d->root, result, q, r, 0);
   if(error) {
      printf("bst2dBallSearch: error detected. \n Freeing and stopping... \n");
      listFree(result, false);
      return NULL;
   }
   return result;
}

static void bst2dTraverse(BNode2d *node, int depth, int *total_depth,
                   int *num_keys) {
   if (node == NULL) {
      return;
   }

   *total_depth += depth;
   (*num_keys)++;

   bst2dTraverse(node->left, depth + 1, total_depth, num_keys);
   bst2dTraverse(node->right, depth + 1, total_depth, num_keys);
}

double bst2dAverageNodeDepth(BST2d *bst2d) {
   assert(bst2d != NULL);

   int total_depth = 0;
   int num_keys = 0;

   bst2dTraverse(bst2d->root, 0, &total_depth, &num_keys);

   return (double)total_depth / (double)num_keys;
}
