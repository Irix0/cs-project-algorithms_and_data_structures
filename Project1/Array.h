/* ========================================================================= *
 * Array generator
 * ========================================================================= */

#ifndef _ARRAY_H_
#define _ARRAY_H_

#include <stddef.h>

/* ------------------------------------------------------------------------- *
 * Create a sorted array of integers.
 *
 * The array must later be deleted by calling free().
 *
 * PARAMETERS
 * length       Number of elements in the array (pre-condition: 0 < length)
 *
 * RETURN
 * array        A new array of integers, or NULL in case of error
 * ------------------------------------------------------------------------- */
int *createSortedArray(size_t length);

/* ------------------------------------------------------------------------- *
 * Create an almost sorted array of integers. Start from a sorted array
 * and then randomly swap prop*length random pairs of positions.
 *
 * The array must later be deleted by calling free().
 *
 * PARAMETERS
 * length       Number of elements in the array (pre-condition: 0 < length)
 * prop         The percentage of random swaps
 *
 * RETURN
 * array        A new array of integers, or NULL in case of error
 * ------------------------------------------------------------------------- */
int *createAlmostSortedArray(size_t length, float prop);

/* ------------------------------------------------------------------------- *
 * Create a decreasing array of integers.
 *
 * The array must later be deleted by calling free().
 *
 * PARAMETERS
 * length       Number of elements in the array (pre-condition: 0 < length)
 *
 * RETURN
 * array        A new array of integers, or NULL in case of error
 * ------------------------------------------------------------------------- */
int *createDecreasingArray(size_t length);

/* ------------------------------------------------------------------------- *
 * Create a random array of integers (from 0 to length-1).
 *
 * The array must later be deleted by calling free().
 *
 * PARAMETERS
 * length       Number of elements in the array (pre-condition: 0 < length)
 *
 * RETURN
 * array        A new array of integers, or NULL in case of error
 * ------------------------------------------------------------------------- */
int *createRandomArray(size_t length);

/* ------------------------------------------------------------------------- *
 * Compare two integer values and increment a global counter.
 *
 * PARAMETERS
 * i1, i2       The two integers to be compared
 *
 * RETURN
 * comp         i1-i2 (<0 if i1<i2, =0 if i1==i2, >0 if i1>i2)
 * ------------------------------------------------------------------------- */

int intCmp(int i1, int i2);

/* ------------------------------------------------------------------------- *
 * Get the value of the global counter
 *
 * RETURN
 * count        The number of calls to intCmp since the last call to
 *              resetCounter
 * ------------------------------------------------------------------------- */

size_t getCounter(void);

/* ------------------------------------------------------------------------- *
 * Reset the value of the global counter
 *
 * ------------------------------------------------------------------------- */

void resetCounter(void);

#endif // !_ARRAY_H_
