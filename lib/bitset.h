/**
 * @file bitset.h Implementation of Bitset data structure
 */

#ifndef _EXTENDED_C_LIB_LIB_BITSET_H
#define _EXTENDED_C_LIB_LIB_BITSET_H

#include <stdarg.h>
#include <stdbool.h> // bool
#include <stddef.h>  // size_t
#include <stdlib.h>  // calloc, malloc, free.
#include <string.h>  // mem funcs.

#include "types.h"

/**
 * @struct bitset
 * @brief Implementation of bitset.
 *
 */
typedef struct bitset
{
  /**
   * @brief Array with bits.
   */
  unsigned char *bits;

  /**
   * @brief Number of bits.
   */
  size_t n;
} bitset;

/**
 * @brief Creates bitset with n
 * bits, all equals zero after
 * initialization.
 *
 * @param n Number of bits.
 * @return bitset* Created instance
 * of bitset.
 */
bitset *bitset_create (size_t n);

/**
 * @brief Creates bitset from
 * <data> with <size> size in bytes.
 * Saving all bits of data.
 *
 * @param data Data
 * @param size Size of data.
 * @return bitset* Created instance
 * of bitset.
 */
bitset *bitset_create_from_data (dptr data, size_t size);

/**
 * @brief Checking that all bits
 * are set.
 *
 * @param b Pointer to bitset instance.
 * @return true if all bits are set.
 * @return false  if one or more
 * bits aren't set.
 */
bool bitset_all (bitset *b);

/**
 * @brief Checking that one or
 * more bits are set.
 *
 * @param b Pointer to bitset instance.
 * @return true if one or more bits are
 * set.
 * @return false if zero bits are set.
 */
bool bitset_any (bitset *b);

/**
 * @brief Returns number of
 * set bits.
 *
 * @param b Pointer to bitset instance.
 * @return size_t Number of
 * bits in set state.
 */
size_t bitset_count (bitset *b);

/**
 * @brief Inversing bit on <pos>
 * position.
 *
 * @param b Pointer to bitset instance.
 * @param pos Position of bit.
 */
void bitset_flip (bitset *b, size_t pos);

/**
 * @brief Inversing all bits.
 *
 * @param b Pointer to bitset instance.
 */
void bitset_flip_all (bitset *b);

/**
 * @brief Reseting bit on <pos> position.
 *
 * @param b Pointer to bitset instance.
 * @param pos Position of bit.
 */
void bitset_reset (bitset *b, size_t pos);

/**
 * @brief Reseting all bits.
 *
 * @param b Pointer to bitset instance.
 */
void bitset_reset_all (bitset *b);

/**
 * @brief Setting bit on <pos> position.
 *
 * @param b Pointer to bitset instance.
 * @param pos Position of bit.
 */
void bitset_set (bitset *b, size_t pos);

/**
 * @brief Setting all bits.
 *
 * @param b Pointer to bitset instance.
 */
void bitset_set_all (bitset *b);

/**
 * @brief Returning number of bits
 * in bitset.
 *
 * @param b Pointer to bitset instance.
 * @return size_t Number of bits
 * in bitset.
 */
size_t bitset_size (bitset *b);

/**
 * @brief Checking bit on <pos> position.
 *
 * @param b Pointer to bitset instance.
 * @param pos Position of bit.
 * @return true If bit is set.
 * @return false If bit isn't set.
 */
bool bitset_test (bitset *b, size_t pos);

/**
 * @brief Converting bits to data representation.
 *
 * @param b Pointer to bitset instance.
 * @param data Data.
 * @param size Size of data.
 */
void bitset_to_data (bitset *b, dptr data, size_t size);

/**
 * @brief Destructor of bitset.
 * sizes should be equal.
 *
 * @param b Pointer to bitset instance.
 */
void bitset_destroy (bitset *b);

#endif