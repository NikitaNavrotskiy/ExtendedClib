/**
 * @file hash.h Implementation of hash algorithm
 * for Hashset and Hashmap.
 */

#ifndef _EXTENDED_C_LIB_LIB_HASH_H
#define _EXTENDED_C_LIB_LIB_HASH_H

#include <stddef.h>
#include <stdint.h>

#include "types.h"

/**
 * @brief Alias for unsigned int 32 bits.
 */
typedef uint32_t hash32;

/**
 * @brief Implementation of Jenkins's
 * hash function. Produce 32bit hash.
 * This algorithm pretty easy and fast, but gives
 * excellent results in all indicators of the hash
 * functions.
 *
 * @param key Pointer to value to hash.
 * @param len Length (size) of key.
 * @return hash32 Resulting hash.
 */
hash32 hash (constdptr key, size_t len);

#endif