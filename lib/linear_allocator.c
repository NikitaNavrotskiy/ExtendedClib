#include "linear_allocator.h"


////////////////////////////////////////////////////
/* Public API functions of the linear_allocator   */
////////////////////////////////////////////////////

linear_allocator *
linear_allocator_create (size_t capacity, uint8_t align)
{
  // Allocating memory for allocator instance.
  linear_allocator *al
      = (linear_allocator *)malloc (sizeof (linear_allocator));

  // Set starting values for allocator.
  al->capacity = capacity;
  al->offset = 0;
  al->align = align;

  // Allocating memory to manage through syscall mmap
  al->ptr = mmap (NULL, al->capacity, PROT_READ | PROT_WRITE,
                  MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

  return al;
}

dptr
linear_allocator_allocate (linear_allocator *al, size_t count)
{
  // Calculating empty space (junk) for alignment.
  uint8_t junk
      = al->align == 0 ? 0 : (al->align - count % al->align) % al->align;

  // Checking enough space.
  if (al->offset + count + junk > al->capacity)
    return NULL;

  // Prepare ptr to give in use.
  dptr *ptr = (al->ptr + al->offset + junk);

  // Setting new offset.
  al->offset += count + junk;

  return ptr;
}

inline __attribute__ ((always_inline)) void
linear_allocator_free (linear_allocator *al)
{
  // Freeing memory by moving offset to zero.
  al->offset = 0;
}

inline void
linear_allocator_destroy (linear_allocator *al)
{
  // deallocate allocator's memory.
  munmap (al->ptr, al->capacity);

  // deallocate allocator instance.
  free (al);
}
