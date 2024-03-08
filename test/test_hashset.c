#include "test.h"

static void
destr (dptr data)
{
  data = data;
  return;
}

static size_t
size_func (constdptr val)
{
  return sizeof (*(int *)val);
}

static bool
cmp_int (constdptr f, constdptr s)
{
  return (*(int *)f == *(int *)s);
}

START_TEST (hashset_test_1)
{
  hashset *hs = hashset_create (cmp_int, size_func, NULL);
  int arr[16]
      = { 1, 8, 6, 4, 5, 3453, 235, 3, 564, 34, 53, 4, 53, 4545, 35, 3535 };
  int buckets_test[20] = { 0 };
  int i;
  ck_assert (hashset_empty (hs));
  for (i = 0; i < 16; i++)
    {
      hashset_insert (hs, arr + i);
      ck_assert (!hashset_empty (hs));
    }
  for (i = 0; i < 16; i++)
    {
      ck_assert_uint_eq (hashset_bucket (hs, arr + i),
                         (size_t)hash (arr + i, sizeof (int))
                             % hashset_bucket_count (hs));
      ck_assert (hashset_contains (hs, arr + i));
      ck_assert (!hashset_empty (hs));
    }

  for (int i = 0; i < 16; i++)
    {
      if (i != 3 && i != 10)
        buckets_test[hash (arr + i, sizeof (int))
                     % hashset_bucket_count (hs)]++;
    }
  for (int i = 0; i < 20; i++)
    {
      ck_assert_uint_eq (hashset_bucket_size (hs, i), (size_t)buckets_test[i]);
    }

  ck_assert_uint_eq (hashset_size (hs), 14);
  ck_assert_uint_eq (hashset_bucket_count (hs), 20);
  ck_assert_float_eq_tol (hashset_load_factor (hs), 14 / (float)20, 1e-07);
  for (i = 0; i < 16; i++)
    {
      hashset_erase (hs, arr + i);
      ck_assert (!hashset_contains (hs, arr + i));
    }

  hashset_destroy (hs);
}

START_TEST (hashset_test_2)
{
  int a = 24321, b = 78938, c = 18346;
  hashset *hs = hashset_create (cmp_int, size_func, NULL);

  ck_assert (hs != NULL);
  ck_assert (hashset_size (hs) == 0);
  ck_assert_uint_eq (hashset_bucket_count (hs),
                     HASHSET_STARTING_NUMBER_OF_BUCKETS);

  hashset_insert (hs, &a);
  ck_assert_uint_eq (hashset_size (hs), 1);
  ck_assert (hashset_contains (hs, &a));

  hashset_insert (hs, &b);
  ck_assert_uint_eq (hashset_size (hs), 2);
  ck_assert (hashset_contains (hs, &b));

  hashset_insert (hs, &c);
  ck_assert_uint_eq (hashset_size (hs), 3);
  ck_assert (hashset_contains (hs, &c));

  hashset_clear (hs);
  ck_assert (hashset_size (hs) == 0);

  hashset_destroy (hs);
}

START_TEST (hashset_test_3)
{
  int a = 24321; //, b = 78938, c = 18346;

  hashset *hs = hashset_create (cmp_int, size_func, destr);

  ck_assert (hs != NULL);
  ck_assert (hashset_size (hs) == 0);
  ck_assert_uint_eq (hashset_bucket_count (hs),
                     HASHSET_STARTING_NUMBER_OF_BUCKETS);

  hashset_insert (hs, &a);
  ck_assert_uint_eq (hashset_size (hs), 1);
  ck_assert (hashset_contains (hs, &a));

  hashset_destroy (hs);
}

START_TEST (hashset_test_4)
{
  int arr[1000000] = { 0 };
  int i;
  hashset *hs = hashset_create (cmp_int, size_func, NULL);
  for (i = 0; i < 100000; i++)
    {
      arr[i] = i;
      hashset_insert (hs, arr + i);
    }

  for (int i = 0; i < 100000; i++)
    {
      hashset_erase (hs, arr + i);
    }

  hashset_destroy (hs);
}

Suite *
suite_hashset ()
{
  Suite *s;
  TCase *tc;

  s = suite_create ("Hashset test");
  tc = tcase_create ("Hashset test");

  tcase_add_test (tc, hashset_test_1);
  tcase_add_test (tc, hashset_test_2);
  tcase_add_test (tc, hashset_test_3);
  tcase_add_test (tc, hashset_test_4);

  suite_add_tcase (s, tc);

  return s;
}