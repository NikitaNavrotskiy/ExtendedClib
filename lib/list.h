/**
 * @file list.h Implementation of List data structure
 */

#ifndef _DATA_STRUCTS_LIB_LIST_H
#define _DATA_STRUCTS_LIB_LIST_H

#include <stdbool.h> // bool
#include <stddef.h>  // size_t
#include <stdlib.h>  // malloc, free

#include "types.h"


#define lnode do_node

/**
 * @brief Alias for lnode pointer
 */
typedef struct lnode * list_iterator;

/**
 * @struct list
 * @brief Implements Queue data struct.
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
} queue;


/**
 * @brief Public API functions of the list.
 *
 */

/**
 * @brief Function to create new list. Allocates the memory. Should be
 * destroyed at the end.
 * @return Pointer to new list.
 */
list *list_create();

/**
 * @brief Function returns last element of 
 * the list.
 * 
 * @param l Pointer to the list.
 * @return dataptr Last element.
 */
dataptr list_back(list *l);

/**
 * @brief Function returns iterator to
 * first element.
 * 
 * @param l Pointer to the list.
 * @return list_iterator.
 */
list_iterator list_begin(const list *l);

/**
 * @brief Function to clear list, but not 
 * destroying instance of list.
 * 
 * @param l Pointer to the list.
 */
void list_clear(list *l);

/**
 * @brief Function to copy list.
 * Don't make deep copy, if dataptr is the
 * pointer to the another pointer,
 * another pointer will be shared. 
 * 
 * @param l Pointer to the list.
 * @return Pointer to the new list.
 */
list *list_copy(const list *l);

/**
 * @brief Function to Destroy list.
 * Frees memory. Do not check if
 * l == nullptr.
 * 
 * @param l Pointer to the list.
 */
void list_destroy(list *l);

/**
 * @brief Function returns Nullptr iterator.
 * 
 * @param l Pointer to the list.
 * @return Null list_iterator 
 */
list_iterator list_end(const list *l);

/**
 * @brief Function insert element to the WHERE position.
 * 
 * @param l Pointer to the list.
 * @param where Position of the new element.
 * @param data New element.
 */
void list_emplace(list *l, list_iterator where, dataptr data);

/**
 * @brief Function insert element to the position of
 * the first element.
 * 
 * @param l Pointer to the list.
 * @param data New element.
 */
void list_emplace_front(list *l, dataptr data);

/**
 * @brief Function insert element to the position of
 * last element.
 * 
 * @param l Pointer to the list.
 * @param data New element.
 */
void list_emplace_back(list *l, dataptr data);

/**
 * @brief Function to check if list is empty.
 * 
 * @param l Pointer to the list.
 * @return true If list is empty.
 * @return false If list isn't empty.
 */
bool list_empty(const list *l);

/**
 * @brief Function to erase element from
 * list on WHERE position.
 * 
 * @param l Pointer to the list.
 * @param where Points to the element to erase.
 */
void list_erase(list *l, list_iterator where);

/**
 * @brief Function to erase elements from
 * FIRST to LAST position.
 * 
 * @param l Pointer to the list.
 * @param first Points to the first element
 * in erasing range.
 * @param last Points to the last element
 * in erasing range.
 */
void list_erase_range(list *l, list_iterator first, list_iterator last);

/**
 * @brief Function returns front element.
 * 
 * @param l Pointer to the list.
 * @return dataptr Element on the front position.
 */
dataptr list_front(const list *l);

/**
 * @brief Function to insert New element to the
 * WHERE position.
 * 
 * @param l Pointer to the list.
 * @param where Position of the new element.
 * @param data New element.
 * @return list_iterator Iterator to the new
 * element.
 */
list_iterator list_insert(list *l, list_iterator where, dataptr data);

/**
 * @brief Function to insert many new elements with
 * <data> values to the WHERE position.
 * 
 * @param l Pointer to the list.
 * @param where Position of the first of the new elements.
 * @param count Number of new elements with <data> value.
 * @param data Value of new elements.
 * @return list_iterator Iterator to the first
 * of the new elements.
 */
list_iterator list_insert_many(list *l, list_iterator where, size_t count, dataptr data);

/**
 * @brief Function to remove last element of
 * the list.
 * 
 * @param l Pointer to the list.
 */
void list_pop_back(list *l);

/**
 * @brief Function to remove first element of
 * the list.
 * 
 * @param l Pointer to the list. 
 */
void list_pop_front(list *l);

/**
 * @brief Function to add new element to
 * the front of the list.
 * 
 * @param l Pointer to the list. 
 * @param data New element.
 */
void list_push_back(list *l, dataptr data);

/**
 * @brief Function to append new element
 * to the list.
 * 
 * @param l Pointer to the list.
 * @param data New element.
 */
void list_push_front(list *l, dataptr data);

/**
 * @brief Function to remove all occurences of
 * <data>
 * 
 * @param l Pointer to the list.
 * @param data Element to remove.
 */
void list_remove(list *l, dataptr data);

/**
 * @brief Function to remove all occurences, that
 * is true for <predicate>.
 * 
 * @param l Pointer to the list.
 * @param predicate Function that return
 * true if element should be removed and 
 * false otherwise.
 */
void list_remove_if(list *l, bool (*predicate)(dataptr first, dataptr second));

/**
 * @brief Function to reverce elements in
 * the list.
 * 
 * @param l Pointer to the list.
 */
void list_reverse(list *l);

/**
 * @brief Function returns size of the list.
 * 
 * @param l Pointer to the list.
 * @return size_t Size of the list.
 */
size_t list_size(const list *l);

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
void list_sort(list *l, int (*cmp)(dataptr first, dataptr second));

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
void list_unique(list *l, bool (*predicate)(dataptr first, dataptr second));

#endif