/**
 * @file std_allocator.h Implementation of Standart
 * Allocator.
 */

#ifndef _EXTENDED_C_LIB_STD_ALLOCATOR_H
#define _EXTENDED_C_LIB_STD_ALLOCATOR_H

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif // _GNU_SOURCE

#include <stddef.h> // NULL
#include <stdint.h>
#include <sys/mman.h> // mmap, munmap, mremap

#include "types.h"

/**
 * @struct std_allocator
 * @brief Implemenation of std_allocator.
 * Just wrapper around malloc, free (mmap, munmap).
 */
typedef struct std_allocator
{
  /**
   * @brief Size of one chunk to allocate.
   * Size of type to allocate for.
   */
  size_t type_size;

  /**
   * @brief Number of chunks with sizeof(type)
   * bytes that allocator has allocated.
   * Will be + n when allocate n * sizeof(type) bytes
   * and - n when deallocate n * sizeof(type) bytes.
   * When it destroys itself, <n> should be
   * equal to 0.
   */
  size_t n;
} std_allocator;

////////////////////////////////////////////////////
/*   Public API functions of the std_allocator    */
////////////////////////////////////////////////////

/**
 * @brief Contructor for the std_allocator.
 *
 * @param type_size Number of bytes for one
 * chunk.
 * @param capacity Number of chunks.
 * In std_allocator just placeholder to satisfy
 * interface.
 * @param align Alignment for addresses.
 * In std_allocator just placeholder to satisfy
 * interface.
 * @return std_allocator* Pointer to
 * std_allocator instance.
 */
std_allocator *std_allocator_create (size_t type_size, size_t capacity,
                                     uint8_t align);

/**
 * @brief Function to allocate new block of memory
 * from allocator. Guaranted to allocate
 * count * chunk_size bytes, or Null if
 * operation failed.
 * @param al Pointer to std allocator.
 * @return dptr Pointer to allocated memory.
 */
dptr std_allocator_allocate (std_allocator *al, size_t count);

/**
 * @brief Function to allocate new chunk of memory
 * from allocator.
 *
 * @param al Pointer to std allocator.
 * @param ptr Pointer to the first chunk to deallocate.
 * @param count Number of chunks to deallocate.
 */
void std_allocator_deallocate (std_allocator *al, dptr ptr, size_t count);

/**
 * @brief Function to reallocate chunk of memory
 * from allocator with deifferent size.
 *
 * @param al Pointer to std allocator.
 * @param ptr Pointer to the first chunk to reallocate.
 * @param old_count Number of chunks before reallocation.
 * @param new_count Number of chunks should be after reallocation.
 */
dptr std_allocator_reallocate (std_allocator *al, dptr ptr, size_t old_count,
                               size_t new_count);

/**
 * @brief Destructor for std allocator.
 *
 * @param al Pointer to std allocator.
 */
void std_allocator_destroy (std_allocator *al);

#endif
