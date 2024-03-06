/**
 * @file Implementation of pool allocator's API functions.
 */

#include "pool_allocator.h"

pool_allocator *
pool_allocator_create (size_t block_size, size_t blocks_number)
{
  pool_allocator *al = (pool_allocator *)malloc (sizeof (pool_allocator));

  // counting size.
  size_t size = block_size * blocks_number;
  al->block_size = block_size;
  al->blocks_number = blocks_number;

  // allocating memory for allocator.
  al->ptr_begin = mmap (NULL, size, PROT_READ | PROT_WRITE,
                        MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

  // computing ptr_end (pointer to the address after last byte
  // that allocator can manipulate. )
  al->ptr_end = al->ptr_begin + size;

  // creating forward_list for free blocks.
  al->free_blocks = forward_list_create ();

  for (size_t i = 0; i < al->blocks_number; i++)
    forward_list_push_front (al->free_blocks,
                             al->ptr_begin + al->block_size * i);

  return al;
}

dptr
pool_allocator_allocate (pool_allocator *al)
{
  dptr ptr = NULL;

  // Getting free block if there are free blocks,
  // otherwise ptr will be NULL.
  if (!forward_list_empty (al->free_blocks))
    {
      ptr = forward_list_front (al->free_blocks);

      // Removing this block from free_blocks.
      forward_list_pop_front (al->free_blocks, NULL);
    }

  return ptr;
}

void
pool_allocator_deallocate (pool_allocator *al, dptr ptr)
{
  // Checing that ptr is from allocator's memory
  // and that address is correct (points to starting
  // byte of some block ).
  if (al->ptr_begin > ptr || al->ptr_end <= ptr)
    return;

  if ((size_t)ptr % al->block_size != (size_t)al->ptr_begin % al->block_size)
    return;

  // Checking if all blocks are already freed.
  if (forward_list_size (al->free_blocks) == al->blocks_number)
    return;

  // If everything is OK, pushing ptr to free blocks.
  forward_list_push_front (al->free_blocks, ptr);
}

void
pool_allocator_destroy (pool_allocator *al)
{
  // freeing memory of forward_list by calling destructor.
  forward_list_destroy (al->free_blocks, NULL);

  // freeing ptr
  munmap (al->ptr_begin, al->block_size * al->blocks_number);

  // freeing allocator.
  free (al);
}