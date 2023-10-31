/* ========================================================================= *
 * List interface:
 * Note that the linked list structure is not opaque so that you can
 * manipulate it directly.
 * ========================================================================= */

#ifndef _LIST_H_
#define _LIST_H_

#include <stdbool.h>
#include <stddef.h>

typedef struct lnode_t {
   void *value;
   struct lnode_t *next;
} LNode;

typedef struct list_t {
   size_t size;
   LNode *head;
   LNode *last;
} List;

/* ------------------------------------------------------------------------- *
 * Creates an empty List
 *
 * The LinkeedList must later be deleted by calling freeList().
 *
 * RETURN
 * List    A pointer to the List, or NULL in case of error
 *
 * ------------------------------------------------------------------------- */

List *listNew(void);

/* ------------------------------------------------------------------------- *
 * Frees the allocated memory of the given List.
 *
 * PARAMETERS
 * l            A valid pointer to a List object
 * freeContent  Whether to free the content as well.
 *
 * ------------------------------------------------------------------------- */

void listFree(List *l, bool freeContent);

/* ------------------------------------------------------------------------- *
 * Counts the number of elements stored in the given List.
 *
 * PARAMETERS
 * ll           A valid pointer to a List object
 *
 * RETURN
 * nb           The amount of elements stored in linked list
 * ------------------------------------------------------------------------- */

size_t listSize(List *l);

/* ------------------------------------------------------------------------- *
 * Inserts a new element at the beginning of the list.
 *
 * PARAMETERS
 * l            A valid pointer to a List object
 * value        The value to store
 *
 * RETURN
 * res          A boolean equal to true if the new element was successfully
 *              inserted, false otherwise (error)
 * ------------------------------------------------------------------------- */

bool listInsertFirst(List *l, void *value);

/* ------------------------------------------------------------------------- *
 * Inserts a new element at the end of the list.
 *
 * PARAMETERS
 * l            A valid pointer to a List object
 * value        The value to store
 *
 * RETURN
 * res          A boolean equal to true if the new element was successfully
 *              inserted, false otherwise (error)
 * ------------------------------------------------------------------------- */

bool listInsertLast(List *l, void *value);

#endif // !_LIST_H_
