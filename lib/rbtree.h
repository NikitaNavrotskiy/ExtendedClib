/**
 * @file rbtree.h
 * @brief Implementation of Red-black Tree
 */

#ifndef _EXTENDED_C_LIB_LIB_RBTREE_H
#define _EXTENDED_C_LIB_LIB_RBTREE_H

#include <stdbool.h> // bool
#include <stdlib.h>  //malloc, free

#include "types.h"

/**
 * @struct rbt_node.
 * @brief Implementation of Red-black Tree node.
 */
struct __rbt_node
{
  /**
   * @brief Pointer to the parent node.
   */
  struct __rbt_node *parent;

  /**
   * @brief Pointer to the right child node.
   */
  struct __rbt_node *right;

  /**
   * @brief Pointer to the left child node.
   */
  struct __rbt_node *left;

  /**
   * @brief Pointer to data of the node.
   */
  dptr data;

  /**
   * @brief Color of the node.
   *  true - red, false - black.
   */
  bool is_red;
};

/**
 * @brief iterator aliases.
 */
typedef struct __rbt_node *rbtree_iterator;
typedef const rbtree_iterator const_rbtree_iterator;

/**
 * @struct rbtree.
 * @brief Implementation of Red-black Tree data structure.
 */
typedef struct rbtree
{
  /**
   * @brief Pointer to the root of
   * the Red-black Tree.
   */
  struct __rbt_node *root;

  /**
   * @brief Size of the root.
   * Means number of nodes.
   */
  size_t size;

  /**
   * @brief Compare Function.
   * Should satisfy next requirements:
   * 1. Return int < 0 if first > second.
   * 2. Return int = 0 if first = second.
   * 3. Return int > 0 if first > second.
   */
  int (*cmp) (constdptr first, constdptr second);

  /**
   * @brief Destructor function for nodes.
   * Null if should not be freed.
   */
  void (*destr) (dptr data);

  /**
   * @brief Flag that allows of disallows the
   * same values (when cmp() func returns 0).
   * true - allows the same values,
   * false - disallows.
   */
  bool allow_same;
} rbtree;

// Debug function
#ifdef DEBUG
bool __rbtree_is_correct (rbtree *tree);
#endif // DEBUG

////////////////////////////////////////////////////
/*  Public API functions of the Red-black Tree    */
////////////////////////////////////////////////////

/**
 * @brief Function create new instanse of rbtree.
 *
 * @param cmp Compare function.
 * 1. Return int < 0 if first > second.
 * 2. Return int = 0 if first = second.
 * 3. Return int > 0 if first > second.
 * @param destr Destructor function for nodes.
 * Null if should not be freed.
 * @param allow_same flag that allows of disallows
 * the same values (when cmp() func returns 0).
 * true - allows the same values,
 * false - disallows.
 * @return rbtree * New instanse of Red-black Tree.
 */
rbtree *rbtree_create (int (*cmp) (constdptr first, constdptr second),
                       void (*destr) (dptr data), bool allow_same);

/**
 * @brief Function to get iterator to the
 * first element.
 *
 * @param tree Pointer to Red-black Tree.
 * @return rbtree_iterator Iterator to the
 * first element.
 */
rbtree_iterator rbtree_begin (const rbtree *tree);

/**
 * @brief Function to get iterator to the
 * first element in reverse order.
 *
 * @param tree Pointer to Red-black Tree.
 * @return rbtree_iterator Iterator to the
 * first element in reverse order.
 */
rbtree_iterator rbtree_rbegin (const rbtree *tree);

/**
 * @brief Function to delete all nodes,
 * but does not deallocate memory of
 * rbtree instanse.
 *
 * @param tree Pointer to Red-black Tree.
 */
void rbtree_clear (rbtree *tree);

/**
 * @brief Function to check if Red-black Tree contains
 * data.
 *
 * @param tree Pointer to Red-black Tree.
 * @param data Data to check.
 * @return bool true if data in tree,
 * false otherwise.
 */
bool rbtree_contains (const rbtree *tree, constdptr data);

/**
 * @brief Function counts number of elements equals to
 * data using cmp().
 *
 * @param tree Pointer to Red-black Tree.
 * @param data Data to count.
 * @return size_t Number of elemeents equals to data.
 */
size_t rbtree_count (const rbtree *tree, constdptr data);

/**
 * @brief Destructor Function for Red-black Tree.
 * Using destr() to destroy nodes.
 *
 * @param tree Pointer to Red-black Tree.
 */
void rbtree_destroy (rbtree *tree);

/**
 * @brief Function to insert new data to
 * the Red-black Tree.
 *
 * @param tree Pointer to the Red-black Tree instanse.
 * @param data Data to insert.
 * @return rbtree_iterator Iterator to the inserted node,
 * if element already exist (in allow_same = false case),
 * NULL iterator.
 */
rbtree_iterator rbtree_insert (rbtree *tree, constdptr data);

/**
 * @brief Function to get iterator to the
 * first after last element.
 *
 * @param tree Pointer to Red-black Tree.
 * @return rbtree_iterator Iterator to the
 * first after the last element.
 */
rbtree_iterator rbtree_end ();

/**
 * @brief Function to get iterator to the
 * first after the last element in reverse
 * order.
 *
 * @param tree Pointer to Red-black Tree.
 * @return rbtree_iterator Iterator to the
 * first after the last element in reverse
 * order.
 */
rbtree_iterator rbtree_rend ();

/**
 * @brief Function to erase element by
 * iterator.
 *
 * @param tree Pointer to Red-black Tree.
 * @param iter Iterator to element to erase.
 * @return rbtree_iterator Iterator to the first
 * after erased element.
 */
rbtree_iterator rbtree_erase (rbtree *tree, rbtree_iterator iter);

/**
 * @brief Function checks is rbtree is empty.
 *
 * @param tree Pointer to Red-black Tree.
 * @return true if Tree is empty.
 * false otherwise.
 */
bool rbtree_empty (rbtree *tree);

/**
 * @brief Function that finds element by data using
 * cmp() func and returns iterator to this element,
 * or returns Null iterator if element hasn't found.
 *
 * @param tree Pointer to Red-black Tree.
 * @param data Data to find.
 * @return rbtree_iterator Iterator to found element.
 */
rbtree_iterator rbtree_find (const rbtree *tree, constdptr data);

/**
 * @brief Function to remove element by
 * data. If allow_same if true, first element
 * that smaller in Red-black Tree order.
 *
 * @param tree Pointer to Red-black Tree.
 * @param data - data ot the removing element.
 */
void rbtree_remove (rbtree *tree, constdptr data);

/**
 * @brief Function to get number of nodes in
 * tree.
 *
 * @param tree Pointer to Red-black Tree.
 * @return size_t Number of elements in tree.
 */
size_t rbtree_size (const rbtree *tree);

/**
 * @brief Function to get next iterator after
 * given.
 *
 * @param iter Given iterator.
 * @return rbtree_iterator Next iterator
 * after given.
 */
rbtree_iterator rbtree_next (const_rbtree_iterator iter);

/**
 * @brief Function to get previous iterator after
 * given.
 *
 * @param iter Given iterator.
 * @return rbtree_iterator previous iterator
 * after given.
 */
rbtree_iterator rbtree_prev (const_rbtree_iterator iter);

#endif
