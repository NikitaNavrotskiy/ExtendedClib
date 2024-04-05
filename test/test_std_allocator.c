#include "test.h"

typedef struct somestruct
{
  int i;
  char c;
  bool b;
  float f[4];
} somestruct;

START_TEST (std_allocator_test_1)
{
  std_allocator *al = std_allocator_create (sizeof (int), 0, 0);

  ck_assert (al->type_size == sizeof (int));
  ck_assert (al->n == 0);

  int *a = std_allocator_allocate (al, 1);

  ck_assert (a);
  ck_assert (al->n == 1);

  int *b = std_allocator_allocate (al, 1);

  ck_assert (b);
  ck_assert (al->n == 2);

  int *arr = std_allocator_allocate (al, 5);

  ck_assert (arr);
  ck_assert (al->n == 7);

  std_allocator_deallocate (al, b, 1);
  ck_assert (al->n == 6);

  std_allocator_reallocate (al, a, 1, 18);
  ck_assert (al->n == 23);

  std_allocator_deallocate (al, arr, 5);
  ck_assert (al->n == 18);

  std_allocator_deallocate (al, a, 18);

  ck_assert (al->n == 0);

  std_allocator_destroy (al);
}

START_TEST (std_allocator_test_2)
{
  std_allocator *al = std_allocator_create (sizeof (char), 0, 0);

  ck_assert (al->type_size == sizeof (char));
  ck_assert (al->n == 0);

  char *a = std_allocator_allocate (al, 1);

  ck_assert (a);
  ck_assert (al->n == 1);

  char *b = std_allocator_allocate (al, 1);

  ck_assert (b);
  ck_assert (al->n == 2);

  char *arr = std_allocator_allocate (al, 5);

  ck_assert (arr);
  ck_assert (al->n == 7);

  std_allocator_deallocate (al, b, 1);
  ck_assert (al->n == 6);

  std_allocator_reallocate (al, a, 1, 18);
  ck_assert (al->n == 23);

  std_allocator_deallocate (al, arr, 5);
  ck_assert (al->n == 18);

  std_allocator_deallocate (al, a, 18);

  ck_assert (al->n == 0);

  std_allocator_destroy (al);
}

START_TEST (std_allocator_test_3)
{
  std_allocator *al = std_allocator_create (sizeof (somestruct), 0, 0);

  ck_assert (al->type_size == sizeof (somestruct));
  ck_assert (al->n == 0);

  somestruct *a = std_allocator_allocate (al, 1);

  ck_assert (a);
  ck_assert (al->n == 1);

  somestruct *b = std_allocator_allocate (al, 1);

  ck_assert (b);
  ck_assert (al->n == 2);

  somestruct *arr = std_allocator_allocate (al, 5);

  ck_assert (arr);
  ck_assert (al->n == 7);

  std_allocator_deallocate (al, b, 1);
  ck_assert (al->n == 6);

  std_allocator_reallocate (al, a, 1, 18);
  ck_assert (al->n == 23);

  std_allocator_deallocate (al, arr, 5);
  ck_assert (al->n == 18);

  std_allocator_deallocate (al, a, 18);

  ck_assert (al->n == 0);

  std_allocator_destroy (al);
}

Suite *
suite_std_allocator ()
{
  Suite *s;
  TCase *tc;

  s = suite_create ("Standart Allocator test");
  tc = tcase_create ("Standart Allocator test");

  tcase_add_test (tc, std_allocator_test_1);
  tcase_add_test (tc, std_allocator_test_2);
  tcase_add_test (tc, std_allocator_test_3);

  suite_add_tcase (s, tc);

  return s;
}
