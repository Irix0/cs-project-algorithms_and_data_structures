/* ========================================================================= *
 * InsertionSort
 * Implementation of the InsertionSort algorithm.
 * ========================================================================= */

#include <stddef.h>
#include "Sort.h"
#include "Array.h"

void sort(int *array, size_t length)
{
    if (!array)
        return;

    int j;
    int tmp;
    // Invariant: array[0..i] is sorted
    for (size_t i = 0; i < length; i++)
    {
        tmp = array[i];
        j = i;
        // Place tmp at the right position
        while (j > 0 && intCmp(array[j - 1], tmp) > 0)
        {
            array[j] = array[j - 1];
            j--;
        }
        array[j] = tmp;
    }
}
