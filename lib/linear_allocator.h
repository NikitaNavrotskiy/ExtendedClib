/**
 * @file linear_allocator.h Implementation of Linear
 * Allocator.
 */

#ifndef _EXTENDED_C_LIB_LINEAR_ALLOCATOR_H
#define _EXTENDED_C_LIB_LINEAR_ALLOCATOR_H

#include <stdint.h>   // uint8_t
#include <stdlib.h>   // malloc, free
#include <sys/mman.h> // mmap, munmap

#include "types.h"

/**
 * @struct linear_allocator
 * @brief Implemenation of linear_allocator.
 */
typedef struct linear_allocator
{
  /**
   * @brief Pointer to memory to manage by allocator.
   */
  dptr ptr;

  /**
   * @brief Current offset from <ptr>.
   * Points to the next place to allocate from
   * allocator.
   */
  size_t offset;

  /**
   * @brief Number of bytes that contain
   * allocator to manage.
   */
  size_t capacity;

  /**
   * @brief Allignment in allocator.
   */
  uint8_t align;
} linear_allocator;

////////////////////////////////////////////////////
/* Public API functions of the linear_allocator   */
////////////////////////////////////////////////////

/**
 * @brief Contructor for the linear allocator.
 *
 * @param capacity Number of bytes for memory
 * managment.
 * @param align Align in allocator.
 * @return linear_allocator* Pointer to
 * linear_allocator instance.
 */
linear_allocator *linear_allocator_create (size_t capacity, uint8_t align);

/**
 * @brief Function to allocate new chunk of memory
 * from allocator.
 *
 * @param al Pointer to Linear allocator.
 * @param count Number of bytes to get from
 * Allocator.
 * @return dptr Pointer to allocated memory.
 */
dptr linear_allocator_allocate (linear_allocator *al, size_t count);

/**
 * @brief Function to free all chunks of memory.
 * Actualy just moving offset to 0 position.
 *
 * @param al Pointer to Linear allocator.
 */
void linear_allocator_free (linear_allocator *al);

/**
 * @brief Destructor for Linear allocator.
 *
 * @param al Pointer to Linear allocator.
 */
void linear_allocator_destroy (linear_allocator *al);

#endif