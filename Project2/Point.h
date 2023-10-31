/* ========================================================================= *
 * Point interface
 * ========================================================================= */

#ifndef _POINT_H_
#define _POINT_H_

typedef struct Point_t Point;

/* ------------------------------------------------------------------------- *
 * Creates a new point with (x,y) coordinates. The Point must later be deleted
 * by calling ptFree.
 *
 * PARAMETERS
 * x           The x coordinate of the point
 * y           The y coordinate of the point.
 *
 * RETURN
 * p           A pointer to a Point.
 * ------------------------------------------------------------------------- */

Point *ptNew(double x, double y);

/* ------------------------------------------------------------------------- *
 * Frees the allocated memory of the given Point.
 *
 * PARAMETERS
 * p           A valid pointer to a Point.
 * ------------------------------------------------------------------------- */

void ptFree(Point *p);

/* ------------------------------------------------------------------------- *
 * Returns the x coordinate of the point.
 *
 * PARAMETERS
 * p           A valid pointer to a Point.
 *
 * RETURN
 * x           The x coordinate of p (a double).
 * ------------------------------------------------------------------------- */

double ptGetx(Point *p);

/* ------------------------------------------------------------------------- *
 * Returns the y coordinate of the point.
 *
 * PARAMETERS
 * p           A valid pointer to a Point.
 *
 * RETURN
 * y           The y coordinate of p (a double).
 * ------------------------------------------------------------------------- */

double ptGety(Point *p);

/* ------------------------------------------------------------------------- *
 * Computes the square of the euclidean distance between two points.
 *
 * PARAMETERS
 * p1           A valid pointer to a Point.
 * p2           A valid pointer to a Point.
 *
 * RETURN
 * d            The square of the Euclidean distance between p1 and p2.
 * ------------------------------------------------------------------------- */

double ptSqrDistance(Point *p1, Point *p2);

/* ------------------------------------------------------------------------- *
 * Compare two points. p1<p2 if ptGetx(p1)<ptGetx(p2) or if
 * ptGetx(p1)=ptGetx(p2) and ptGety(p1)<ptGety(p2). p1=p2 if
 * ptGetx(p1)=ptGetx(p2) and ptGety(p1)=ptGety(p2).
 *
 * PARAMETERS
 * p1           A valid pointer to a Point.
 * p2           A valid pointer to a Point.
 *
 * RETURN
 * c            An integer equal to 0 if p1=p2, <0 if p1<p2 and >0 if p1>p2.
 * ------------------------------------------------------------------------- */

int ptCompare(Point *p1, Point *p2);

/* ------------------------------------------------------------------------- *
 * Prints the (x,y) coordinates of the point on the standard output.
 *
 * PARAMETERS
 * p           A valid pointer to a Point.
 * ------------------------------------------------------------------------- */

void ptPrint(Point *p);

#endif // !_POINT_H_
