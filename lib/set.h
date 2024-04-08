/**
 * @file set.h Implementation of set based
 * on Red-Black Tree.
 */

#ifndef _EXTENDED_C_LIB_LIB_SET_H
#define _EXTENDED_C_LIB_LIB_SET_H

#include <stdbool.h> // bool
#include <stdlib.h>  //malloc, free

#include "rbtree.h"

/**
 * @struct set.
 * @brief Implementation of Set data structure.
 * Set represents wrapper based on Red-Black, that
 * disallow duplicated.
 * Tree.
 */
typedef struct set
{
  /**
   * @brief Instance of Red-Black Tree.
   */
  rbtree *tree;
} set;

typedef rbtree_iterator set_iterator;
typedef const_rbtree_iterator const_set_iterator;

////////////////////////////////////////////////////
/*     Public API functions of the hashset        */
////////////////////////////////////////////////////

/**
 * @brief Function create new instanse of set.
 *
 * @param cmp Compare function.
 * 1. Return int < 0 if first > second.
 * 2. Return int = 0 if first = second.
 * 3. Return int > 0 if first > second.
 * @param destr Destructor function for nodes.
 * Null if should not be freed.
 */
set *set_create (int (*cmp) (constdptr first, constdptr second),
                 void (*destr) (dptr data));

/**
 * @brief Function to get iterator to the
 * first element.
 *
 * @param st Pointer to Set.
 * @return set_iterator Iterator to the
 * first element.
 */
set_iterator set_begin (const set *st);

/**
 * @brief Function to get iterator to the
 * first element in reverse order.
 *
 * @param st Pointer to Set.
 * @return set_iterator Iterator to the
 * first element in reverse order.
 */
set_iterator set_rbegin (const set *st);

/**
 * @brief Function to delete all nodes,
 * but does not deallocate memory of
 * set instanse.
 *
 * @param st Pointer to Set.
 */
void set_clear (set *st);

/**
 * @brief Function to check if Set contains
 * data.
 *
 * @param st Pointer to Set.
 * @param data Data to check.
 * @return bool true if data in tree,
 * false otherwise.
 */
bool set_contains (const set *st, constdptr data);

/**
 * @brief Function counts number of elements equals to
 * data using cmp().
 *
 * @param st Pointer to Set.
 * @param data Data to count.
 * @return size_t Number of elemeents equals to data.
 */
size_t set_count (const set *st, constdptr data);

/**
 * @brief Destructor Function for Set.
 * Using destr() to destroy nodes.
 *
 * @param st Pointer to Set.
 */
void set_destroy (set *st);

/**
 * @brief Function to insert new data to
 * the Set.
 *
 * @param st Pointer to the Set instanse.
 * @param data Data to insert.
 * @return set_iterator Iterator to the inserted node,
 * if element already exist, NULL iterator.
 */
set_iterator set_insert (set *st, constdptr data);

/**
 * @brief Function to get iterator to the
 * first after last element.
 *
 * @param st Pointer to Red-black Set.
 * @return set_iterator Iterator to the
 * first after the last element.
 */
set_iterator set_end ();

/**
 * @brief Function to get iterator to the
 * first after the last element in reverse
 * order.
 *
 * @param st Pointer to Set.
 * @return set_iterator Iterator to the
 * first after the last element in reverse
 * order.
 */
set_iterator set_rend ();

/**
 * @brief Function to erase element by
 * iterator.
 *
 * @param st Pointer to Set.
 * @param iter Iterator to element to erase.
 * @return set_iterator Iterator to the first
 * after erased element.
 */
set_iterator set_erase (set *st, set_iterator iter);

/**
 * @brief Function checks is set is empty.
 *
 * @param st Pointer to Set.
 * @return true if set is empty.
 * false otherwise.
 */
bool set_empty (set *st);

/**
 * @brief Function that finds element by data using
 * cmp() func and returns iterator to this element,
 * or returns Null iterator if element hasn't found.
 *
 * @param st Pointer to Set.
 * @return set_iterator Iterator to found element.
 */
set_iterator set_find (const set *st, constdptr data);

/**
 * @brief Function to remove element by
 * data.
 *
 * @param st Pointer to Set.
 * @param data - data ot the removing element.
 */
void set_remove (set *st, constdptr data);

/**
 * @brief Function to get number of nodes in
 * set.
 *
 * @param st Pointer to Set.
 * @return size_t Number of elements in set.
 */
size_t set_size (const set *st);

/**
 * @brief Function to get next iterator after
 * given.
 *
 * @param iter Given iterator.
 * @return set_iterator Next iterator
 * after given.
 */
set_iterator set_next (const_set_iterator iter);

/**
 * @brief Function to get previous iterator after
 * given.
 *
 * @param iter Given iterator.
 * @return set_iterator previous iterator
 * after given.
 */
set_iterator set_prev (const_set_iterator iter);

#endif
