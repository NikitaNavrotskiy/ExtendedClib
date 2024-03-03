/**
 * @file list.h Implementation of List data structure
 */

#ifndef _EXTENDED_C_LIB_LIB_FORWARD_LIST_H
#define _EXTENDED_C_LIB_LIB_FORWARD_LIST_H

#include <stdarg.h>  // va_list
#include <stdbool.h> // bool
#include <stddef.h>  // size_t
#include <stdlib.h>  // malloc, free
#include <string.h>  // mem* funcs

#include "types.h"

#define flnode do_node

/**
 * @brief Alias for do_node pointer
 */
typedef struct flnode *forward_list_iterator;

/**
 * @struct forward_list
 * @brief Implements Forward list data struct.
 */

typedef struct forward_list
{
  /**
   * @brief variable to store size of the forward list.
   */
  size_t size;

  /**
   * @brief Pointer to the front of forward list.
   */
  struct flnode *front;
} forward_list;

/**
 * @brief Public API functions of the forward list.
 *
 */

/**
 * @brief Function to create new forward list. Allocates the memory. Should be
 * destroyed at the end.
 * @return Pointer to new forward list.
 */
forward_list *forward_list_create ();

/**
 * @brief Function returns iterator to
 * first element.
 *
 * @param l Pointer to the forward list.
 * @return forward_list_iterator.
 */
forward_list_iterator forward_list_begin (const forward_list *l);

/**
 * @brief Function to clear forward list, but not
 * destroying instance of forward list.
 *
 * @param l Pointer to the forward list.
 * @param destr Pointer to function, to
 * free memory of datas correctly.
 */
void forward_list_clear (forward_list *l, void (*destr) (dptr data));

/**
 * @brief Function to copy list.
 * Don't make deep copy, if dptr is the
 * pointer to the another pointer,
 * another pointer will be shared.
 *
 * @param l Pointer to the forward list.
 * @param cpy Funtion that copying data.
 * @return Pointer to the new forward list.
 */
forward_list *forward_list_copy (const forward_list *l,
                                 dptr (*cpy) (const dptr data));

/**
 * @brief Function to count <data> occurences.
 *
 * @param l Pointer to the list.
 * @param data Element to count.
 * @param cmp Function that return
 * true if <data> = element
 * false otherwise.
 * @return size_t Number of occurences.
 */
size_t forward_list_count (const forward_list *l, constdptr data,
                           bool (*cmp) (constdptr first, constdptr second));

/**
 * @brief Function to count all occurences, that
 * is true for <predicate>.
 *
 * @param l Pointer to the forward list.
 * @param predicate Function that return
 * true if element should be counted and
 * false otherwise.
 * @return size_t Number of occurences.
 */
size_t forward_list_count_if (const forward_list *l,
                              bool (*predicate) (constdptr data));

/**
 * @brief Function to Destroy forward list.
 * Frees memory. Do not check if
 * l == nullptr.
 *
 * @param l Pointer to the forward list.
 * @param destr Pointer to function, to
 * free memory of datas correctly.
 */
void forward_list_destroy (forward_list *l, void (*destr) (dptr data));

/**
 * @brief Function returns Nullptr iterator.
 *
 * @return Null forward_list_iterator
 */
forward_list_iterator forward_list_end ();

/**
 * @brief Function insert element after WHERE position.
 *
 * @param l Pointer to the forward list.
 * @param where Position of the new element.
 * @param data New element.
 */
void forward_list_emplace_after (forward_list *l, forward_list_iterator where,
                                 constdptr data);

/**
 * @brief Function insert element to the position of
 * the first element.
 *
 * @param l Pointer to the forward list.
 * @param data New element.
 */
void forward_list_emplace_front (forward_list *l, constdptr data);

/**
 * @brief Function to check if forward list is empty.
 *
 * @param l Pointer to the forward list.
 * @return true If forward list is empty.
 * @return false If forward list isn't empty.
 */
bool forward_list_empty (const forward_list *l);

/**
 * @brief Function to erase element from
 * forward list after WHERE position.
 *
 * @param where Points to the element to erase
 * arter.
 * @param destr Pointer to function, to
 * free memory of datas correctly.
 */
void forward_list_erase (forward_list_iterator where,
                         void (*destr) (dptr data));

/**
 * @brief Function returns front element.
 *
 * @param l Pointer to the forward list.
 * @return dptr Element on the front position.
 */
dptr forward_list_front (const forward_list *l);

/**
 * @brief Function to find first occurence
 * of <data>.
 *
 * @param l Pointer to the forward list.
 * @param data Element to find.
 * @param cmp Function that return
 * true if <data> = element
 * false otherwise.
 * @return forward_list_iterator to the first occurence
 * or NULL if element hasn't found.
 */
forward_list_iterator forward_list_find (const forward_list *l, constdptr data,
                                         bool (*cmp) (constdptr first,
                                                      constdptr second));

/**
 * @brief Function to find first occurences, that
 * is true for <predicate>.
 *
 * @param l Pointer to the forward list.
 * @param predicate Function that return
 * true if element is equal and should be
 * found and false otherwise.
 * @return forward_list_iterator to the first occurence
 * or NULL if element hasn't found.
 */
forward_list_iterator list_find_if (const forward_list *l,
                                    bool (*predicate) (constdptr data));

/**
 * @brief Function to insert New element after
 * WHERE position.
 *
 * @param l Pointer to the forward list.
 * @param where Position of the new element.
 * if where == NULL, placing element to the end.
 * @param data New element.
 * @return forward_list_iterator Iterator to the new
 * element.
 */
forward_list_iterator forward_list_insert_after (forward_list *l,
                                                 forward_list_iterator where,
                                                 constdptr data);

/**
 * @brief Function to insert many new elements with
 * <data> values to the WHERE position.
 *
 * @param l Pointer to the forward list.
 * @param where Position of the first of the new elements.
 * @param count Number of elements in ... .
 * @param data Value of new elements.
 * @return forward_list_iterator Iterator to the first
 * of the new elements.
 */
forward_list_iterator
forward_list_insert_after_many (forward_list *l, forward_list_iterator where,
                                size_t count, ...);

/**
 * @brief Function to remove first element of
 * the forward list.
 *
 * @param l Pointer to the forward list.
 * @param destr Pointer to function, to
 * free memory of datas correctly.
 */
void forward_list_pop_front (forward_list *l, void (*destr) (dptr data));

/**
 * @brief Function to append new element
 * to the forward list.
 *
 * @param l Pointer to the list.
 * @param data New element.
 */
void forward_list_push_front (forward_list *l, constdptr data);

/**
 * @brief Function to remove all occurences of
 * <data>
 *
 * @param l Pointer to the forward list.
 * @param data Element to remove.
 * @param cmp Function that return
 * true if <data> = element
 * false otherwise.
 * @param destr Pointer to function, to
 * free memory of datas correctly.
 */
void forward_list_remove (forward_list *l, dptr data,
                          bool (*cmp) (constdptr first, constdptr second),
                          void (*destr) (dptr data));

/**
 * @brief Function to remove all occurences, that
 * is true for <predicate>.
 *
 * @param l Pointer to the forward list.
 * @param destr Pointer to function, to
 * free memory of datas correctly.
 * @param predicate Function that return
 * true if element should be removed and
 * false otherwise.
 */
void forward_list_remove_if (forward_list *l,
                             bool (*predicate) (constdptr data),
                             void (*destr) (dptr data));

/**
 * @brief Function to reverce elements in
 * the forward list.
 *
 * @param l Pointer to the forward list.
 */
void forward_list_reverse (forward_list *l);

/**
 * @brief Function returns size of the
 * forward list.
 *
 * @param l Pointer to the forward list.
 * @return size_t Size of the forward list.
 */
size_t forward_list_size (const forward_list *l);

/**
 * @brief Function to sort the forward list.
 *
 * @param l Pointer to the forward list.
 * @param cmp Function of comparing
 * two elements for sorting.
 * return int < 0 if first < second
 * return int > 0 if first > second
 * return int = 0 if first = second.
 */
void forward_list_sort (forward_list *l,
                        int (*cmp) (constdptr first, constdptr second));

/**
 * @brief Function to unique forward list,
 * by removing extra elements.
 *
 * @param l Pointer to the forward list.
 * @param predicate Function of
 * comparing for unique.
 * return true if first = second.
 * return fasle if first != second.
 */
void forward_list_unique (forward_list *l,
                          bool (*predicate) (constdptr first,
                                             constdptr second));

#endif