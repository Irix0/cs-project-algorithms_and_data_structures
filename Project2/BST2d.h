/* ========================================================================= *
 * BST2d interface
 * ========================================================================= */

#ifndef _BST2D_H_
#define _BST2D_H_

#include "List.h"
#include "Point.h"
#include <stdbool.h>
#include <stddef.h>

/* Opaque Structure */
typedef struct BST2d_t BST2d;

/* ------------------------------------------------------------------------- *
 * Creates an empty BST2d
 *
 * The BST2d must later be deleted by calling freeBST2d().
 *
 * RETURN
 * bst2d                A pointer to the BST2d, or NULL in case of
 *                      error
 * ------------------------------------------------------------------------- */

BST2d *bst2dNew(void);

/* ------------------------------------------------------------------------- *
 * Frees the allocated memory of the given BST2d.
 *
 * PARAMETERS
 * bst2d          A valid pointer to a BST2d object
 * freeKey        Whether to free the keys.
 * freeValue      Whether to free the values.
 *
 * ------------------------------------------------------------------------- */

void bst2dFree(BST2d *bst2d, bool freeKey, bool freeValue);

/* ------------------------------------------------------------------------- *
 * Counts the number of elements/nodes stored in the given BST2d.
 *
 * PARAMETERS
 * bst2d          A valid pointer to a BST2d object
 *
 * RETURN
 * nb             The amount of elements stored in bst2d
 * ------------------------------------------------------------------------- */

size_t bst2dSize(BST2d *bst2d);

/* ------------------------------------------------------------------------- *
 * Inserts a new position-value pair in the provided BST2d. This
 * implementation of the BST allows duplicate keys.
 *
 * PARAMETERS
 * bst2d          A valid pointer to a BST object
 * point          The position of the new element (a Point object)
 * value          The value to store
 *
 * RETURN
 * res          A boolean equal to true if the new element was successfully
 *              inserted, false otherwise
 * ------------------------------------------------------------------------- */

bool bst2dInsert(BST2d *b2d, Point *point, void *value);

/* ------------------------------------------------------------------------- *
 * Returns the value associated to a position, if any. If several values are
 * associated to this position, any one of them is returned.
 *
 * PARAMETERS
 * bst          A valid pointer to a BST2d object
 * q            The position to look for
 *
 * RETURN
 * res          One of the value corresponding to that key. Or NULL if the key
 *              is not present in the BST2d
 * ------------------------------------------------------------------------- */

void *bst2dSearch(BST2d *b2d, Point *q);

/* ------------------------------------------------------------------------- *
 * Finds the set of positions (x,y) in the provided BST2d that are included
 * in a ball of radius r and centered at the position q given as argument.
 * The function returns a list of the values associated to these positions
 * (in no particular order).
 *
 * PARAMETERS
 * bst2d          A valid pointer to a BST2d object
 * q              The center of the ball
 * r              The radius of the ball
 *
 * RETURN
 * l              A List containing the values in the given ball, or
 *                NULL in case of allocation error.
 *
 * NOTES
 * The List must be freed but not its content. If no elements are in the
 * ball, the function returns an empty list
 * ------------------------------------------------------------------------- */

List *bst2dBallSearch(BST2d *bst2d, Point *q, double r);

/* ------------------------------------------------------------------------- *
 * Returns the average depth of the BST2d nodes. The depth of a node is the
 * number of edges that connect it to the root (the root's depth is thus 0).
 *
 * PARAMETERS
 * bst2d          A valid pointer to a BST2d object
 *
 * RETURN
 * double         The average depth of the BST2d nodes
 * ------------------------------------------------------------------------- */

double bst2dAverageNodeDepth(BST2d *bst2d);

#endif // !_BST_H_
