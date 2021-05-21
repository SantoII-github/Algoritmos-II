#ifndef _LIST_H
#define _LIST_H

#include <stdbool.h>

/* list as a pointer to structs to guarantee encapsulation */
typedef struct list_node * list;
typedef int list_elem;

list list_empty();
/*
 * Creates a new empty list.
 */

list list_addl(list_elem e, list l);
/*
 * Adds the element e to the start of the list l.
 */

bool list_is_empty(list l);
/*
 * Returns true if the list l is empty.
 */

list_elem list_head(list l);
/*
 * Returns the first element of the list l.
 * PRE: not list_is_empty(l)
 */

list list_tail(list l);
/*
 * Deletes the first element of the list l.
 * PRE: not list_is_empty(l)
 */

list list_addr(list_elem e, list l);
/*
 * Adds the element e to the end of the list l.
 */

unsigned int list_length(list l);
/*
 * Returns the amount of elements in the list l.
 */

list list_concat(list l1, list l2);
/*
 * Adds each element of the list l2 to the end of the list l1, in order.
 */

list_elem list_index(list l, unsigned int n);
/*
 * Return the element that is in the n position of the list.
 * PRE: list_length(l) < n 
 */

list list_take(list l, unsigned int n);
/*
 * Returns a list that has only the first n elements of l.
 */

list list_drop(list l, unsigned int n);
/*
 * Returns a list without the first n elements of l.
 */

list copy_list(list l1);
/*
 * Makes a copy of l1 in a new list.
 */

list list_destroy(list l);
/*
 * Frees memory for l.
 */

#endif