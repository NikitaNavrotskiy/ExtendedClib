/**
 * @file hashset.h Implementation of Hashset
 * (unordered_set in STL) data structure.
 */

#ifndef _EXTENDED_C_LIB_LIB_HASHSET_H
#define _EXTENDED_C_LIB_LIB_HASHSET_H

#include <stdbool.h> // bool
#include <stdlib.h>  //malloc, free

#include "array.h"
#include "forward_list.h"
#include "hash.h"
#include "types.h"

#define HASHSET_STARTING_NUMBER_OF_BUCKETS 5
#define HASHSET_INCREASE_BUCKETS_FACTOR 2

/**
 * @struct hashset.
 * @brief Implementation of Hashset data structure.
 */
typedef struct hashset
{
  /**
   * @brief Counting current number of elements.
   */
  size_t size;

  /**
   * @brief Array that contains
   * instances of forward_list.
   */
  array *buckets;

  /**
   * @brief Compare function for elemnts.
   * Return true if val1 == val2.
   * Return false if val1 != val2.
   */
  bool (*cmp) (constdptr, constdptr);

  /**
   * @brief Function to get to know size
   * of the elem. Needs for hash alg.
   */
  size_t (*size_func) (constdptr);

  /**
   * @brief Destructor for elements.
   * Null if shouldnot be freed.
   */
  void (*destr) (dptr);
} hashset;

/**
 * @brief Public API functions of the hashset.
 *
 */

/**
 * @brief Function to create new hashset. Allocates the memory. Should be
 * destroyed at the end.
 * @param pair_vals_cmp Function to compare vals
 * Return true if val1 == val2.
 * Return false if val1 != val2.
 * @param size_func Function to compute
 * size of the Val.
 * @param destr Destructor for elements.
 * Null if should not be freed.
 * @return Pointer to new hashset.
 */
hashset *
hashset_create (bool (*pair_vals_cmp) (constdptr val1, constdptr val2),
                size_t (*size_func) (constdptr val), void (*destr) (dptr val));

/**
 * @brief Function to get number of bucket for
 * <val> element.
 *
 * @param hs Pointer to the instance of hashset.
 * @param val Element for searching.
 * @return size_t Index of bucket where <val> val is.
 */
size_t hashset_bucket (const hashset *hs, constdptr val);

/**
 * @brief Function to get number of buckets in hashset.
 *
 * @param hm Pointer to the instance of hashset.
 * @return size_t Number of buckets in hashset.
 */
size_t hashset_bucket_count (const hashset *hs);

/**
 * @brief Function to get number of elements
 * in <nbucket> bucket.
 *
 * @param hs Pointer to the instance of hashset.
 * @param nbucket
 * @return size_t Number of elements in <nbucket>
 * bucket.
 */
size_t hashset_bucket_size (const hashset *hs, size_t nbucket);

/**
 * @brief Function to clear hashset.
 * Do not destroy instance of hashset.
 *
 * @param hs Pointer to the instance of hashset.
 */
void hashset_clear (hashset *hs);

/**
 * @brief Function to check if element is in
 * the hashset.
 *
 * @param hs Pointer to the instance of hashmap.
 * @param val Element to check on existense.
 * @return true If element is in hashset,
 *  false If element is not in hashset.
 */
bool hashset_contains (const hashset *hs, constdptr val);

/**
 * @brief Function to check if hashset is empty.
 *
 * @param hs Pointer to the instance of hashset.
 * @return true If hashset is empty.
 * @return false If hashset is not empty.
 */
bool hashset_empty (const hashset *hs);

/**
 * @brief Function to erase element
 *  from the hashset.
 *
 * @param hs Pointer to the instance of hashset.
 * @param val element to erase.
 */
void hashset_erase (hashset *hs, constdptr val);

/**
 * @brief Function to insert new val into
 * the hashset or not if val already exist.
 *
 * @param hs Pointer to the instance of hashset.
 * @param val Valto insert.
 */
void hashset_insert (hashset *hs, constdptr val);

/**
 * @brief Function to get load of hashset.
 *
 * @param hs Pointer to the instance of hashset.
 * @return float Size / Number of backets.
 */
float hashset_load_factor (const hashset *hs);

/**
 * @brief Function to rehash hashset.
 *
 * @param hs Pointer to the instance of hashset.
 */
void hashset_rehash (hashset *hs);

/**
 * @brief Function to get number of elements
 * if hashset.
 *
 * @param hs Pointer to the instance of hashset.
 * @return size_t Number of elements in hashset.
 */
size_t hashset_size (const hashset *hs);

/**
 * @brief Destructor for hashset.
 *
 * @param hs Pointer to the instance of hashset.
 */
void hashset_destroy (hashset *hs);

#endif