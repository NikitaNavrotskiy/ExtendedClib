#include "test.h"

START_TEST (pool_allocator_test_1)
{
  size_t block_size = 64, blocks_number = 4;
  pool_allocator *al = pool_allocator_create (block_size, blocks_number);
  ck_assert (al->block_size == block_size);
  ck_assert (al->blocks_number == blocks_number);
  ck_assert (forward_list_size (al->free_blocks) == 4);
  ck_assert ((size_t)(al->ptr_end - al->ptr_begin)
             == block_size * blocks_number);

  dptr one = pool_allocator_allocate (al);
  ck_assert (one == (al->ptr_begin + block_size * (blocks_number - 1)));
  ck_assert (forward_list_size (al->free_blocks) == 3);

  dptr two = pool_allocator_allocate (al);
  ck_assert (two == (al->ptr_begin + block_size * (blocks_number - 2)));
  ck_assert (forward_list_size (al->free_blocks) == 2);
  ck_assert ((size_t)(one - two) == block_size);

  dptr three = pool_allocator_allocate (al);
  ck_assert (three == (al->ptr_begin + block_size * (blocks_number - 3)));
  ck_assert (forward_list_size (al->free_blocks) == 1);
  ck_assert ((size_t)(two - three) == block_size);

  dptr four = pool_allocator_allocate (al);
  ck_assert (four == (al->ptr_begin + block_size * (blocks_number - 4)));
  ck_assert (forward_list_size (al->free_blocks) == 0);
  ck_assert ((size_t)(three - four) == block_size);

  dptr five = pool_allocator_allocate (al);
  ck_assert (five == NULL);

  pool_allocator_deallocate (al, four);
  ck_assert (forward_list_size (al->free_blocks) == 1);
  ck_assert (forward_list_front (al->free_blocks) == four);

  four = pool_allocator_allocate (al);
  ck_assert (four == (al->ptr_begin + block_size * (blocks_number - 4)));
  ck_assert (forward_list_size (al->free_blocks) == 0);
  ck_assert ((size_t)(three - four) == block_size);

  five = pool_allocator_allocate (al);
  ck_assert (five == NULL);

  pool_allocator_deallocate (al, one);
  ck_assert (forward_list_size (al->free_blocks) == 1);
  ck_assert (forward_list_front (al->free_blocks) == one);

  one = pool_allocator_allocate (al);
  ck_assert (one == (al->ptr_begin + block_size * (blocks_number - 1)));
  ck_assert (forward_list_size (al->free_blocks) == 0);
  ck_assert ((size_t)(one - two) == block_size);

  pool_allocator_deallocate (al, two);
  ck_assert (forward_list_size (al->free_blocks) == 1);
  ck_assert (forward_list_front (al->free_blocks) == two);

  two = pool_allocator_allocate (al);
  ck_assert (two == (al->ptr_begin + block_size * (blocks_number - 2)));
  ck_assert (forward_list_size (al->free_blocks) == 0);
  ck_assert ((size_t)(two - three) == block_size);

  pool_allocator_destroy (al);
}

START_TEST (pool_allocator_test_2)
{
  size_t block_size = 64, blocks_number = 4;
  pool_allocator *al = pool_allocator_create (block_size, blocks_number);
  ck_assert (al->block_size == block_size);
  ck_assert (al->blocks_number == blocks_number);
  ck_assert (forward_list_size (al->free_blocks) == 4);
  ck_assert ((size_t)(al->ptr_end - al->ptr_begin)
             == block_size * blocks_number);

  dptr one = pool_allocator_allocate (al);
  ck_assert (one == (al->ptr_begin + block_size * (blocks_number - 1)));
  ck_assert (forward_list_size (al->free_blocks) == 3);

  dptr two = pool_allocator_allocate (al);
  ck_assert (two == (al->ptr_begin + block_size * (blocks_number - 2)));
  ck_assert (forward_list_size (al->free_blocks) == 2);
  ck_assert ((size_t)(one - two) == block_size);

  dptr three = pool_allocator_allocate (al);
  ck_assert (three == (al->ptr_begin + block_size * (blocks_number - 3)));
  ck_assert (forward_list_size (al->free_blocks) == 1);
  ck_assert ((size_t)(two - three) == block_size);

  dptr four = pool_allocator_allocate (al);
  ck_assert (four == (al->ptr_begin + block_size * (blocks_number - 4)));
  ck_assert (forward_list_size (al->free_blocks) == 0);
  ck_assert ((size_t)(three - four) == block_size);

  dptr five = pool_allocator_allocate (al);
  ck_assert (five == NULL);

  pool_allocator_deallocate (al, four + 1);
  ck_assert (forward_list_size (al->free_blocks) == 0);

  pool_allocator_deallocate (al, four - 200);
  ck_assert (forward_list_size (al->free_blocks) == 0);

  pool_allocator_destroy (al);
}

START_TEST (pool_allocator_test_3)
{
  size_t block_size = 64, blocks_number = 4;
  pool_allocator *al = pool_allocator_create (block_size, blocks_number);
  ck_assert (al->block_size == block_size);
  ck_assert (al->blocks_number == blocks_number);
  ck_assert (forward_list_size (al->free_blocks) == 4);
  ck_assert ((size_t)(al->ptr_end - al->ptr_begin)
             == block_size * blocks_number);

  dptr one = pool_allocator_allocate (al);
  ck_assert (one == (al->ptr_begin + block_size * (blocks_number - 1)));
  ck_assert (forward_list_size (al->free_blocks) == 3);

  pool_allocator_deallocate (al, one);
  ck_assert (forward_list_size (al->free_blocks) == 4);

  pool_allocator_deallocate (al, one);
  ck_assert (forward_list_size (al->free_blocks) == 4);

  pool_allocator_destroy (al);
}

Suite *
suite_pool_allocator ()
{
  Suite *s;
  TCase *tc;

  s = suite_create ("Pool Allocator test");
  tc = tcase_create ("Pool Allocator test");

  tcase_add_test (tc, pool_allocator_test_1);
  tcase_add_test (tc, pool_allocator_test_2);
  tcase_add_test (tc, pool_allocator_test_3);

  suite_add_tcase (s, tc);

  return s;
}