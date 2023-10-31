/* ========================================================================= *
 * BST interface
 * ========================================================================= */

#ifndef _BST_H_
#define _BST_H_

#include "List.h"
#include <stdbool.h>
#include <stddef.h>

/* Opaque Structure */
typedef struct BST_t BST;

typedef struct tuple_t {
   void *key;
   void *value;
} tuple;

/* ------------------------------------------------------------------------- *
 * Creates an empty BST (or BST).
 *
 * The BST must later be deleted by calling freeBST().
 *
 * ARGUMENT
 * comparison_fn_t      A comparison function
 *
 * RETURN
 * bst                  A pointer to the BST, or NULL in case of
 *                      error
 *
 * COMPARISON FUNCTION
 * comparison_fn_t(a, b) < 0    <=> a < b
 * comparison_fn_t(a, b) = 0    <=> a == b
 * comparison_fn_t(a, b) > 0    <=> a > b
 *
 * USAGE (example for doubles:
 * http://www.gnu.org/software/libc/manual/html_node/Comparison-Functions.html)
 * int compare_doubles(void* a, void* b)
 * {
 *     double* a_ = (double*)a;
 *     double* b_ = (double*)b;
 *     return (*a_ > *b_) - (*a_ < *b_)
 * }
 * ...
 * BST bst = newBST(&compare_doubles);
 * ------------------------------------------------------------------------- */

BST *bstNew(int comparison_fn_t(void *, void *));

/* ------------------------------------------------------------------------- *
 * Frees the allocated memory of the given BST.
 *
 * PARAMETERS
 * bst          A valid pointer to a BST object
 * freeKey      Whether to free the keys.
 * freeValue    Whether to free the values.
 *
 * ------------------------------------------------------------------------- */

void bstFree(BST *bst, bool freeKey, bool freeValue);

/* ------------------------------------------------------------------------- *
 * Counts the number of elements/nodes stored in the given BST.
 *
 * PARAMETERS
 * bst          A valid pointer to a BST object
 *
 * RETURN
 * nb           The amount of elements stored in bst
 * ------------------------------------------------------------------------- */

size_t bstSize(BST *bst);

/* ------------------------------------------------------------------------- *
 * Inserts a new key-value pair in the provided BST. This
 * implementation of the BST allows duplicate keys.
 *
 * PARAMETERS
 * bst          A valid pointer to a BST object
 * key          The key of the new element
 * value        The value to store
 *
 * RETURN
 * res          A boolean equal to true if the new element was successfully
 *              inserted, false otherwise
 * ------------------------------------------------------------------------- */

bool bstInsert(BST *bst, void *key, void *value);

/* ------------------------------------------------------------------------- *
 * Returns the value associated to that key, if it belongs to the bst.
 * If duplicate copies of that key belongs to the bst, any one of the values
 * associated to that key is returned.
 *
 *
 * PARAMETERS
 * bst          A valid pointer to a BST object
 * key          The key to look for
 *
 * RETURN
 * res          One of the value corresponding to that key. Or NULL if the key
 *              is not present in the BST
 * ------------------------------------------------------------------------- */

void *bstSearch(BST *bst, void *key);

/* ------------------------------------------------------------------------- *
 * Returns the average depth of the BST nodes. The depth of a node is the
 * number of edges that connect it to the root (the root's depth is thus 0).
 *
 * PARAMETERS
 * bst          A valid pointer to a BST object
 *
 * RETURN
 * double       The average depth of the BST nodes
 * ------------------------------------------------------------------------- */

double bstAverageNodeDepth(BST *bst);

/* ------------------------------------------------------------------------- *
 * Finds a set of elements in the provided BST whose keys are included
 * in a range [keyMin, keyMax] and returns their values. The values
 * are sorted in the increasing order of the keys.
 *
 * PARAMETERS
 * bst          A valid pointer to a BST object
 * keyMin       Lower bound of the range (inclusive)
 * keyMax       Upper bound of the range (inclusive)
 *
 * RETURN
 * l            A List containing the element in the given range, or
 *              NULL in case of allocation error.
 *
 * NOTES
 * The List must be freed but not its content. If no elements are in the
 * range, the function returns an empty list
 * ------------------------------------------------------------------------- */

List *bstRangeSearch(BST *bst, void *keyMin, void *keyMax);

#endif // !_BST_H_
