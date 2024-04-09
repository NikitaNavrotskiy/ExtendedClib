/**
 * @file map.h
 * @brief Implementation of map based
 * on Red-Black Tree.
 */

#ifndef _EXTENDED_C_LIB_LIB_MAP_H
#define _EXTENDED_C_LIB_LIB_MAP_H

#include <stdbool.h> // bool
#include <stdlib.h>  //malloc, free

#include "rbtree.h"

/**
 * @struct map.
 * @brief Implementation of map data structure.
 * map represents wrapper based on Red-Black, that
 * disallow duplicated.
 */
typedef struct map
{
  /**
   * @brief Instance of Red-Black Tree.
   */
  rbtree *tree;
} map;

typedef rbtree_iterator map_iterator;
typedef const_rbtree_iterator const_map_iterator;

////////////////////////////////////////////////////
/*     Public API functions of the hashmap        */
////////////////////////////////////////////////////

/**
 * @brief Function create new instanse of map.
 *
 * @param cmp Compare function.
 * Should compare two pairs.
 * 1. Return int < 0 if first > second.
 * 2. Return int = 0 if first = second.
 * 3. Return int > 0 if first > second.
 * @param destr Destructor function for pair.
 * Null if should not be freed.
 * @return map * New instanse of map.
 */
map *map_create (int (*cmp) (constdptr first, constdptr second),
                 void (*destr) (dptr pair));

/**
 * @brief Function to get value by key from the
 * hmap.
 *
 * @param hm Pointer to the instance of map.
 * @param key Key for searching.
 * @return dptr Value that associated the given key.
 */
dptr map_at (const map *mp, constdptr key);

/**
 * @brief Function to get iterator to the
 * first element.
 *
 * @param mp Pointer to map.
 * @return map_iterator Iterator to the
 * first element.
 */
map_iterator map_begin (const map *mp);

/**
 * @brief Function to get iterator to the
 * first element in reverse order.
 *
 * @param mp Pointer to map.
 * @return map_iterator Iterator to the
 * first element in reverse order.
 */
map_iterator map_rbegin (const map *mp);

/**
 * @brief Function to delete all nodes,
 * but does not deallocate memory of
 * map instanse.
 *
 * @param mp Pointer to map.
 */
void map_clear (map *mp);

/**
 * @brief Function to check if map contains
 * data.
 *
 * @param mp Pointer to map.
 * @param key Key to check.
 * @return bool true if data in tree,
 * false otherwise.
 */
bool map_contains (const map *mp, constdptr key);

/**
 * @brief Function counts number of elements equals to
 * data using cmp().
 *
 * @param mp Pointer to map.
 * @param key Key to count.
 * @return size_t Number of elemeents equals to data.
 */
size_t map_count (const map *mp, constdptr key);

/**
 * @brief Destructor Function for map.
 * Using destr() to destroy nodes.
 *
 * @param mp Pointer to map.
 */
void map_destroy (map *mp);

/**
 * @brief Function to insert new data to
 * the map.
 *
 * @param mp Pointer to the map instanse.
 * @param key Key to insert.
 * @param value Value to insert.
 * @return map_iterator Iterator to the inserted node,
 * if element already exist, NULL iterator.
 */
map_iterator map_insert (map *mp, constdptr key, constdptr value);

/**
 * @brief Function to get iterator to the
 * first after last element.
 *
 * @param mp Pointer to Red-black map.
 * @return map_iterator Iterator to the
 * first after the last element.
 */
map_iterator map_end ();

/**
 * @brief Function to get iterator to the
 * first after the last element in reverse
 * order.
 *
 * @param mp Pointer to map.
 * @return map_iterator Iterator to the
 * first after the last element in reverse
 * order.
 */
map_iterator map_rend ();

/**
 * @brief Function to erase element by
 * iterator.
 *
 * @param st Pointer to map.
 * @param iter Iterator to element to erase.
 * @return map_iterator Iterator to the first
 * after erased element.
 */
map_iterator map_erase (map *mp, map_iterator iter);

/**
 * @brief Function checks is map is empty.
 *
 * @param st Pointer to map.
 * @return true if map is empty.
 * false otherwise.
 */
bool map_empty (map *mp);

/**
 * @brief Function that finds element by data using
 * cmp() func and returns iterator to this element,
 * or returns Null iterator if element hasn't found.
 *
 * @param mp Pointer to map.
 * @param key Key to find.
 * @return map_iterator Iterator to found element.
 */
map_iterator map_find (const map *mp, constdptr key);

/**
 * @brief Function to remove element by
 * data.
 *
 * @param mp Pointer to map.
 * @param key - key of the removing element.
 */
void map_remove (map *mp, constdptr key);

/**
 * @brief Function to get number of nodes in
 * map.
 *
 * @param mp Pointer to map.
 * @return size_t Number of elements in map.
 */
size_t map_size (const map *mp);

/**
 * @brief Function to get next iterator after
 * given.
 *
 * @param iter Given iterator.
 * @return map_iterator Next iterator
 * after given.
 */
map_iterator map_next (const_map_iterator iter);

/**
 * @brief Function to get previous iterator after
 * given.
 *
 * @param iter Given iterator.
 * @return map_iterator previous iterator
 * after given.
 */
map_iterator map_prev (const_map_iterator iter);

#endif
