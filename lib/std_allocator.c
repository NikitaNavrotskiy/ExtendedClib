#include "std_allocator.h"

////////////////////////////////////////////////////
/*  Public API functions of the pool_allocator    */
////////////////////////////////////////////////////

std_allocator *
std_allocator_create (size_t type_size,
                      __attribute__ ((unused)) size_t capacity,
                      __attribute__ ((unused)) uint8_t align)
{
  std_allocator *al = (std_allocator *)mmap (
      NULL, sizeof (std_allocator), PROT_READ | PROT_WRITE,
      MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

  al->type_size = type_size;
  al->n = 0;

  return al;
}

dptr
std_allocator_allocate (std_allocator *al, size_t count)
{
  dptr ptr = mmap (NULL, al->type_size * count, PROT_READ | PROT_WRITE,
                   MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  al->n += count;

  return ptr;
}

dptr
std_allocator_reallocate (std_allocator *al, dptr ptr, size_t old_count,
                          size_t new_count)
{
  dptr new_ptr = mremap (ptr, al->type_size * old_count,
                         al->type_size * new_count, MREMAP_MAYMOVE);

  al->n += new_count;
  al->n -= old_count;

  return new_ptr;
}

void
std_allocator_deallocate (std_allocator *al, dptr ptr, size_t count)
{
  munmap (ptr, count * al->type_size);
  al->n -= count;
}

void
std_allocator_destroy (std_allocator *al)
{
  munmap (al, sizeof (std_allocator));
}
