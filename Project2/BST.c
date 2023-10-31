/* ========================================================================= *
 * BST definition
 *
 * \file BSTC.c
 * \author Maé Klinkenberg s213722
 * \author Louan Robert s211732
 * \brief BST definition
 * \date 23/04/2023
 *
 * ========================================================================= */

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "BST.h"
#include "List.h"

// Opaque Structure

typedef struct BNode_t BNode;

struct BNode_t {
   BNode *parent;
   BNode *left;
   BNode *right;
   void *key;
   void *value;
};

struct BST_t {
   BNode *root;
   size_t size;
   int (*compfn)(void *, void *);
};

// Prototypes of static functions

static void bstFreeRec(BNode *n, bool freeKey, bool freeValue);

static BNode *bnNew(void *key, void *value);

/**
 * \brief Traverse the BST to sum the depths and the number of nodes
 * 
 * \param node Current node to traverse
 * \param depth Current node depth
 * \param total_depth Summed depth of all the nodes
 * \param num_keys Number of nodes
 */
static void bstTraverse(BNode *node, float depth, int *total_depth, int *num_keys);

/**
 * \brief Traverse the BST to do a range search
 * 
 * \param node Current node to traverse
 * \param result List of the values that are in the searched range
 * \param compfn Function used to compare the keys
 * \param keymin Minimal key of the range
 * \param keymax Maximal key of the range
 * \result true Success
 * \result false Failure (allocation error)
 */
static bool bstTraverseRangeSearch(BNode *node, List *result,
                            int (*compfn)(void *, void *), void *keymin,
                            void *keymax);

// Function definitions

static BNode *bnNew(void *key, void *value) {
   BNode *n = malloc(sizeof(BNode));
   if (n == NULL) {
      printf("bnNew: allocation error\n");
      return NULL;
   }
   n->left = NULL;
   n->right = NULL;
   n->key = key;
   n->value = value;
   return n;
}

BST *bstNew(int comparison_fn_t(void *, void *)) {
   assert(comparison_fn_t != NULL);
   BST *bst = malloc(sizeof(BST));
   if (bst == NULL) {
      printf("bestNew: allocation error");
      return NULL;
   }
   bst->root = NULL;
   bst->size = 0;
   bst->compfn = comparison_fn_t;
   return bst;
}

void bstFree(BST *bst, bool freeKey, bool freeValue) {
   bstFreeRec(bst->root, freeKey, freeValue);
   free(bst);
}

void bstFreeRec(BNode *n, bool freeKey, bool freeValue) {
   if (n == NULL) return;
   bstFreeRec(n->left, freeKey, freeValue);
   bstFreeRec(n->right, freeKey, freeValue);
   if (freeKey) free(n->key);
   if (freeValue) free(n->value);
   free(n);
}

size_t bstSize(BST *bst) { return bst->size; }

bool bstInsert(BST *bst, void *key, void *value) {
   assert(bst != NULL);
   if (bst->root == NULL) {
      bst->root = bnNew(key, value);
      if (bst->root == NULL) {
         return false;
      }
      bst->size++;
      return true;
   }
   BNode *prev = NULL;
   BNode *n = bst->root;
   while (n != NULL) {
      prev = n;
      int cmp = bst->compfn(key, n->key);
      if (cmp <= 0) {
         n = n->left;
      } else if (cmp > 0) {
         n = n->right;
      }
   }
   BNode *new = bnNew(key, value);
   if (new == NULL) {
      return false;
   }
   new->parent = prev;
   if (bst->compfn(key, prev->key) <= 0) {
      prev->left = new;
   } else {
      prev->right = new;
   }
   bst->size++;
   return true;
}

void *bstSearch(BST *bst, void *key) {
   assert(bst != NULL);
   BNode *n = bst->root;
   while (n != NULL) {
      int cmp = bst->compfn(key, n->key);
      if (cmp < 0) {
         n = n->left;
      } else if (cmp > 0) {
         n = n->right;
      } else {
         return n->value;
      }
   }
   return NULL;
}

static void bstTraverse(BNode *node, float depth, int *total_depth, int *num_keys) {
   if (node == NULL) {
      return;
   }

   *total_depth += depth;
   (*num_keys)++;

   bstTraverse(node->left, depth + 1.0, total_depth, num_keys);
   bstTraverse(node->right, depth + 1.0, total_depth, num_keys);
}

double bstAverageNodeDepth(BST *bst) {
   assert(bst != NULL);

   int total_depth = 0.0;
   int num_keys = 0;

   bstTraverse(bst->root, 0.0, &total_depth, &num_keys);

   return (double)total_depth / (double)num_keys;
}

static bool bstTraverseRangeSearch(BNode *n, List *result,
                            int (*compfn)(void *, void *), void *keymin,
                            void *keymax) {
   if (n == NULL) return true;

   bool error = false;

   if (compfn(n->key, keymin) < 0) { // key < keymin -- we go right
      bstTraverseRangeSearch(n->right, result, compfn, keymin, keymax);
   } else if (compfn(n->key, keymax) > 0) { // key > keymax -- we go left
      bstTraverseRangeSearch(n->left, result, compfn, keymin, keymax);
   } else {
      bstTraverseRangeSearch(n->left, result, compfn, keymin, keymax);
      error = error || !listInsertLast(result, n->value);
      bstTraverseRangeSearch(n->right, result, compfn, keymin, keymax);
   }

   if (error) {
      printf("bstTraverseRangeSearch: error durring allocation. Stopping ...\n");
      return false;
   }

   return true;
}

List *bstRangeSearch(BST *bst, void *keymin, void *keymax) {
   assert(bst != NULL && keymin != NULL && keymax != NULL);

   if (bst->compfn(keymin, keymax) > 0) return NULL;

   List *result = listNew();
   if (bst->root == NULL) {
      return result;
   }
   bool error = !bstTraverseRangeSearch(bst->root, result, bst->compfn, keymin, keymax);

   if (error) {
      printf("bstRangeSearch: error durring allocation. Stopping and freeing ...\n");
      listFree(result, false);
      return NULL;
   }
   return result;
}
