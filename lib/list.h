/**
 * @file list.h Implementation of List data structure
 */

#ifndef _EXTENDED_C_LIB_LIB_LIST_H
#define _EXTENDED_C_LIB_LIB_LIST_H

#include <stdarg.h>  // va_list
#include <stdbool.h> // bool
#include <stddef.h>  // size_t
#include <stdlib.h>  // malloc, free
#include <string.h>  // mem* funcs

#include "types.h"

#define lnode do_node

/**
 * @brief Alias for do_node pointer
 */
typedef struct lnode *list_iterator;

/**
 * @struct list
 * @brief Implements List data struct.
 */
typedef struct list
{
  /**
   * @brief variable to store size of the list.
   */
  size_t size;

  /**
   * @brief Pointer to the front of list.
   */
  struct lnode *front;

  /**
   * @brief Pointer to the back of list.
   */
  struct lnode *back;
} list;

/**
 * @brief Public API functions of the list.
 *
 */

/**
 * @brief Function to create new list. Allocates the memory. Should be
 * destroyed at the end.
 * @return Pointer to new list.
 */
list *list_create ();

/**
 * @brief Function returns last element of
 * the list.
 *
 * @param l Pointer to the list.
 * @return dptr Last element.
 */
dptr list_back (const list *l);

/**
 * @brief Function returns iterator to
 * first element.
 *
 * @param l Pointer to the list.
 * @return list_iterator.
 */
list_iterator list_begin (const list *l);

/**
 * @brief Function to clear list, but not
 * destroying instance of list.
 *
 * @param l Pointer to the list.
 * @param destr Pointer to function, to
 * free memory of datas correctly.
 */
void list_clear (list *l, void (*destr) (dptr data));

/**
 * @brief Function to copy list.
 * Don't make deep copy, if dptr is the
 * pointer to the another pointer,
 * another pointer will be shared.
 *
 * @param l Pointer to the list.
 * @param cpy Funtion that copying data.
 * @return Pointer to the new list.
 */
list *list_copy (const list *l, dptr (*cpy) (const dptr data));

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
size_t list_count (const list *l, constdptr data,
                   bool (*cmp) (constdptr first, constdptr second));

/**
 * @brief Function to count all occurences, that
 * is true for <predicate>.
 *
 * @param l Pointer to the list.
 * @param predicate Function that return
 * true if element should be counted and
 * false otherwise.
 * @return size_t Number of occurences.
 */
size_t list_count_if (const list *l, bool (*predicate) (constdptr data));

/**
 * @brief Function to Destroy list.
 * Frees memory. Do not check if
 * l == nullptr.
 *
 * @param l Pointer to the list.
 * @param destr Pointer to function, to
 * free memory of datas correctly.
 */
void list_destroy (list *l, void (*destr) (dptr data));

/**
 * @brief Function returns Nullptr iterator.
 *
 * @return Null list_iterator
 */
list_iterator list_end ();

/**
 * @brief Function insert element to the WHERE position.
 *
 * @param l Pointer to the list.
 * @param where Position of the new element.
 * @param data New element.
 */
void list_emplace (list *l, list_iterator where, constdptr data);

/**
 * @brief Function insert element to the position of
 * the first element.
 *
 * @param l Pointer to the list.
 * @param data New element.
 */
void list_emplace_front (list *l, constdptr data);

/**
 * @brief Function insert element to the position of
 * last element.
 *
 * @param l Pointer to the list.
 * @param data New element.
 */
void list_emplace_back (list *l, constdptr data);

/**
 * @brief Function to check if list is empty.
 *
 * @param l Pointer to the list.
 * @return true If list is empty.
 * @return false If list isn't empty.
 */
bool list_empty (const list *l);

/**
 * @brief Function to erase element from
 * list on WHERE position.
 * @param l Pointer to the list.
 * @param where Points to the element to erase.
 * @param destr Pointer to function, to
 * free memory of datas correctly.
 */
void list_erase (list *l, list_iterator where, void (*destr) (dptr data));

/**
 * @brief Function to erase elements from
 * FIRST to LAST position (All includes). Programmer is
 * responsible for correct <first> and
 * <last> iterators. <last> maybe NULL to erase
 * all from <first> to the <last> including.
 * @param l Pointer to the list.
 * @param first Points to the first element
 * in erasing range.
 * @param last Points to the last element
 * in erasing range.
 * @param destr Pointer to function, to
 * free memory of datas correctly.
 */
void list_erase_range (list *l, list_iterator first, list_iterator last,
                       void (*destr) (dptr data));

/**
 * @brief Function returns front element.
 * Not safety if l->front is NULL.
 *
 * @param l Pointer to the list.
 * @return dptr Element on the front position.
 */
dptr list_front (const list *l);

/**
 * @brief Function to find first occurence
 * of <data>.
 *
 * @param l Pointer to the list.
 * @param data Element to find.
 * @param cmp Function that return
 * true if <data> = element
 * false otherwise.
 * @return list_iterator to the first occurence
 * or NULL if element hasn't found.
 */
list_iterator list_find (const list *l, constdptr data,
                         bool (*cmp) (constdptr first, constdptr second));

/**
 * @brief Function to find first occurences, that
 * is true for <predicate>.
 *
 * @param l Pointer to the list.
 * @param predicate Function that return
 * true if element is equal and should be
 * found and false otherwise.
 * @return list_iterator to the first occurence
 * or NULL if element hasn't found.
 */
list_iterator list_find_if (const list *l, bool (*predicate) (constdptr data));

/**
 * @brief Function to find first occurence
 * of <data> in reverse order.
 *
 * @param l Pointer to the list.
 * @param data Element to find.
 * @param cmp Function that return
 * true if <data> = element
 * false otherwise.
 * @return list_iterator to the first occurence in
 * reverse order or NULL if element hasn't found.
 */
list_iterator list_rfind (const list *l, constdptr data,
                          bool (*cmp) (constdptr first, constdptr second));

/**
 * @brief Function to find first occurences,
 * in reverse oreder, that is true for <predicate>.
 *
 * @param l Pointer to the list.
 * @param predicate Function that return
 * true if element should be find and
 * false otherwise.
 * @return list_iterator to the first occurence in
 * reverse order or NULL if element hasn't found.
 */
list_iterator list_rfind_if (const list *l,
                             bool (*predicate) (constdptr data));

/**
 * @brief Function to insert New element to the
 * WHERE position.
 *
 * @param l Pointer to the list.
 * @param where Position of the new element.
 * if where == NULL, placing element to the end.
 * @param data New element.
 * @return list_iterator Iterator to the new
 * element.
 */
list_iterator list_insert (list *l, list_iterator where, constdptr data);

/**
 * @brief Function to insert many new elements with
 * <data> values to the WHERE position.
 *
 * @param l Pointer to the list.
 * @param where Position of the first of the new elements.
 * @param count Number of elements in ... .
 * @param data Value of new elements.
 * @return list_iterator Iterator to the first
 * of the new elements.
 */
list_iterator list_insert_many (list *l, list_iterator where, size_t count,
                                ...);

/**
 * @brief Function to remove last element of
 * the list.
 *
 * @param l Pointer to the list.
 * @param destr Pointer to function, to
 * free memory of datas correctly.
 */
void list_pop_back (list *l, void (*destr) (dptr data));

/**
 * @brief Function to remove first element of
 * the list.
 *
 * @param l Pointer to the list.
 * @param destr Pointer to function, to
 * free memory of datas correctly.
 */
void list_pop_front (list *l, void (*destr) (dptr data));

/**
 * @brief Function to add new element to
 * the front of the list.
 *
 * @param l Pointer to the list.
 * @param data New element.
 */
void list_push_back (list *l, constdptr data);

/**
 * @brief Function to append new element
 * to the list.
 *
 * @param l Pointer to the list.
 * @param data New element.
 */
void list_push_front (list *l, constdptr data);

/**
 * @brief Function to remove all occurences of
 * <data>
 *
 * @param l Pointer to the list.
 * @param data Element to remove.
 * @param cmp Function that return
 * true if <data> = element
 * false otherwise.
 * @param destr Pointer to function, to
 * free memory of datas correctly.
 */
void list_remove (list *l, dptr data,
                  bool (*cmp) (constdptr first, constdptr second),
                  void (*destr) (dptr data));

/**
 * @brief Function to remove all occurences, that
 * is true for <predicate>.
 *
 * @param l Pointer to the list.
 * @param destr Pointer to function, to
 * free memory of datas correctly.
 * @param predicate Function that return
 * true if element should be removed and
 * false otherwise.
 */
void list_remove_if (list *l, bool (*predicate) (constdptr data),
                     void (*destr) (dptr data));

/**
 * @brief Function to reverce elements in
 * the list.
 *
 * @param l Pointer to the list.
 */
void list_reverse (list *l);

/**
 * @brief Function returns size of the list.
 *
 * @param l Pointer to the list.
 * @return size_t Size of the list.
 */
size_t list_size (const list *l);

/**
 * @brief Function to sort the list.
 *
 * @param l Pointer to the list.
 * @param cmp Function of comparing
 * two elements for sorting.
 * return int < 0 if first < second
 * return int > 0 if first > second
 * return int = 0 if first = second.
 */
void list_sort (list *l, int (*cmp) (constdptr first, constdptr second));

/**
 * @brief Function to unique list,
 * by removing extra elements.
 *
 * @param l Pointer to the list.
 * @param predicate Function of
 * comparing for unique.
 * return true if first = second.
 * return fasle if first != second.
 */
void list_unique (list *l,
                  bool (*predicate) (constdptr first, constdptr second));

#endif