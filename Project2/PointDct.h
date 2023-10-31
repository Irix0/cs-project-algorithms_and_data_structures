/* ========================================================================= *
 * PointDct interface
 * ========================================================================= */

#ifndef __POINTDCT___
#define __POINTDCT___

#include "List.h"
#include "Point.h"

typedef struct PointDct_t PointDct;

/* ------------------------------------------------------------------------- *
 * Creates a PointDict object (dictionary of points). Points and values
 * are expected to be stored by pointers in the structure. They will not
 * be freed by pdctFree.
 *
 * PARAMETERS
 * lpoints          A list of Point objects (Point pointers)
 * lvalues          A list of values (void * pointers)
 *
 * RETURN
 * pd               A PointDict object
 * ------------------------------------------------------------------------- */

PointDct *pdctCreate(List *lpoints, List *Lvalues);

/* ------------------------------------------------------------------------- *
 * Frees a PointDct object. The Point objects and values are not freed.
 *
 * PARAMETERS
 * pd            A valid pointer to a PointDct object
 *
 * ------------------------------------------------------------------------- */

void pdctFree(PointDct *pd);

/* ------------------------------------------------------------------------- *
 * Returns the number of points stored in the PointDct object.
 *
 * PARAMETERS
 * pd           A valid pointer to a PointDct object
 *
 * RETURN
 * nb           The number of positions in pd
 * ------------------------------------------------------------------------- */

size_t pdctSize(PointDct *pd);

/* ------------------------------------------------------------------------- *
 * Returns the value associated to a point, if it belongs to the PointDct.
 * If several duplicate copies of that point belongs to pd, any one of the
 * values associated to that key is returned.
 *
 * PARAMETERS
 * pd           A valid pointer to a PointDct object
 * p            The point to look for
 *
 * RETURN
 * res          One of the value corresponding to that point. Or NULL if
 *              the point is not present in the BST
 * ------------------------------------------------------------------------- */

void *pdctExactSearch(PointDct *pd, Point *p);

/* ------------------------------------------------------------------------- *
 * Finds the set of positions (x,y) in the Point dictionary that are included
 * in a ball of radius r and centered at the position q given as argument.
 * The function returns a list of the values associated to these positions
 * (in no particular order).
 *
 * PARAMETERS
 * pd           A valid pointer to a PointDct object
 * q            The center of the ball
 * r            The radius of the ball
 *
 * RETURN
 * l            A list containing the values in the given ball, or NULL
 *              in case of allocation error.
 *
 * NOTES
 * The list must be freed but not its content. If no elements are in the ball,
 * the function returns an empty list.
 * ------------------------------------------------------------------------- */

List *pdctBallSearch(PointDct *pd, Point *p, double r);

#endif // __POINTDCT___
