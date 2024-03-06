#include "test.h"

START_TEST (linear_allocator_test_1)
{
  uint8_t align = 8;
  size_t capacity = 256;

  linear_allocator *al = linear_allocator_create (capacity, align);

  dptr one = linear_allocator_allocate (al, 16);
  ck_assert_uint_eq (((uint64_t)one - (uint64_t)al->ptr), 0);
  ck_assert (al->capacity == 256);
  ck_assert (al->offset == 16);

  dptr two = linear_allocator_allocate (al, 1);
  ck_assert_uint_eq (((uint64_t)two - (uint64_t)al->ptr), 23);
  ck_assert (al->capacity == 256);
  ck_assert (al->offset == 24);

  dptr three = linear_allocator_allocate (al, 300);
  ck_assert (three == NULL);
  ck_assert (al->offset == 24);

  linear_allocator_free (al);
  ck_assert (al->capacity == 256);
  ck_assert (al->offset == 0);

  linear_allocator_destroy (al);
}

START_TEST (linear_allocator_test_2)
{
  uint8_t align = 5;
  size_t capacity = 256;

  linear_allocator *al = linear_allocator_create (capacity, align);

  dptr one = linear_allocator_allocate (al, 16);
  ck_assert_uint_eq (((uint64_t)one - (uint64_t)al->ptr), 4);
  ck_assert (al->capacity == 256);
  ck_assert (al->offset == 20);

  dptr two = linear_allocator_allocate (al, 3);
  ck_assert_uint_eq (((uint64_t)two - (uint64_t)al->ptr), 22);
  ck_assert (al->capacity == 256);
  ck_assert (al->offset == 25);

  dptr three = linear_allocator_allocate (al, 300);
  ck_assert (three == NULL);
  ck_assert (al->offset == 25);

  linear_allocator_free (al);
  ck_assert (al->capacity == 256);
  ck_assert (al->offset == 0);

  linear_allocator_destroy (al);
}

START_TEST (linear_allocator_test_3)
{
  uint8_t align = 0;
  size_t capacity = 256;

  linear_allocator *al = linear_allocator_create (capacity, align);

  dptr one = linear_allocator_allocate (al, 32);
  ck_assert_uint_eq (((uint64_t)one - (uint64_t)al->ptr), 0);
  ck_assert (al->capacity == 256);
  ck_assert (al->offset == 32);

  dptr two = linear_allocator_allocate (al, 3);
  ck_assert_uint_eq (((uint64_t)two - (uint64_t)al->ptr), 32);
  ck_assert (al->capacity == 256);
  ck_assert (al->offset == 35);

  dptr three = linear_allocator_allocate (al, 300);
  ck_assert (three == NULL);
  ck_assert (al->offset == 35);

  linear_allocator_free (al);
  ck_assert (al->capacity == 256);
  ck_assert (al->offset == 0);

  linear_allocator_destroy (al);
}

Suite *
suite_linear_allocator ()
{
  Suite *s;
  TCase *tc;

  s = suite_create ("Linear Allocator test");
  tc = tcase_create ("Linear Allocator test");

  tcase_add_test (tc, linear_allocator_test_1);
  tcase_add_test (tc, linear_allocator_test_2);
  tcase_add_test (tc, linear_allocator_test_3);

  suite_add_tcase (s, tc);

  return s;
}