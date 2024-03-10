/**
 * @file pool_allocator.h Implementation of Pool
 * Allocator.
 */

#ifndef _EXTENDED_C_LIB_POOL_ALLOCATOR_H
#define _EXTENDED_C_LIB_POOL_ALLOCATOR_H

#include <stdlib.h>   // malloc, free
#include <sys/mman.h> // mmap, munmap

#include "forward_list.h"
#include "types.h"

/**
 * @struct pool_allocator
 * @brief Implemenation of pool_allocator.
 */
typedef struct pool_allocator
{
  /**
   * @brief Pointer to memory to manage by allocator.
   */
  dptr ptr_begin;

  /**
   * @brief Pointer to the next after last
   * byte that allocator manages.
   */

  dptr ptr_end;
  /**
   * @brief Size of one block (in bytes).
   */
  size_t block_size;

  /**
   * @brief Number of blocks.
   */
  size_t blocks_number;

  /**
   * @brief Forward list to manage free blocks.
   */
  forward_list *free_blocks;
} pool_allocator;


////////////////////////////////////////////////////
/*  Public API functions of the pool_allocator    */
////////////////////////////////////////////////////

/**
 * @brief Contructor for the pool allocator.
 *
 * @param block_size Number of bytes for one
 * block.
 * @param blocks_number Number of blocks.
 * @return pool_allocator* Pointer to
 * pool_allocator instance.
 */
pool_allocator *pool_allocator_create (size_t block_size,
                                       size_t blocks_number);

/**
 * @brief Function to allocate new block of memory
 * from allocator.
 *
 * @param al Pointer to pool allocator.
 * @return dptr Pointer to allocated memory.
 */
dptr pool_allocator_allocate (pool_allocator *al);

/**
 * @brief Function to allocate new block of memory
 * from allocator.
 *
 * @param al Pointer to pool allocator.
 * @param ptr Pointer to block to deallocate. Allocator
 * will add to forward_list of free blocks.
 */
void pool_allocator_deallocate (pool_allocator *al, dptr ptr);

/**
 * @brief Destructor for pool allocator.
 *
 * @param al Pointer to pool allocator.
 */
void pool_allocator_destroy (pool_allocator *al);

#endif
