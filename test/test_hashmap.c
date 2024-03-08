#include "test.h"

static void
destr (dptr pair)
{
  free (pair);
  return;
}

static void
pair_destr (struct pair *pair)
{
  pair = pair;
}

static size_t
size_func (constdptr key)
{
  return sizeof (*(int *)key);
}

static bool
cmp_int (constdptr f, constdptr s)
{
  return (*(int *)((struct pair *)f)->key == *(int *)((struct pair *)s)->key);
}

START_TEST (hashmap_test_1)
{
  hashmap *hm = hashmap_create (cmp_int, size_func, NULL);
  int arr[16]
      = { 1, 8, 6, 4, 5, 3453, 235, 3, 564, 34, 53, 4, 53, 4545, 35, 3535 };
  int buckets_test[20] = { 0 };
  int i;
  ck_assert (hashmap_empty (hm));
  for (i = 0; i < 16; i++)
    {
      hashmap_insert (hm, arr + i, &i);
      ck_assert (!hashmap_empty (hm));
    }
  for (i = 0; i < 16; i++)
    {
      ck_assert_uint_eq (hashmap_bucket (hm, arr + i),
                         (size_t)hash (arr + i, sizeof (int))
                             % hashmap_bucket_count (hm));
      ck_assert (hashmap_contains (hm, arr + i));
      ck_assert (hashmap_at (hm, arr + i) == &i);
      ck_assert (!hashmap_empty (hm));
    }

  for (int i = 0; i < 16; i++)
    {
      if (i != 3 && i != 10)
        buckets_test[hash (arr + i, sizeof (int))
                     % hashmap_bucket_count (hm)]++;
    }
  for (int i = 0; i < 20; i++)
    {
      ck_assert_uint_eq (hashmap_bucket_size (hm, i), (size_t)buckets_test[i]);
    }

  ck_assert_uint_eq (hashmap_size (hm), 14);
  ck_assert_uint_eq (hashmap_bucket_count (hm), 20);
  ck_assert_float_eq_tol (hashmap_load_factor (hm), 14 / (float)20, 1e-07);
  for (i = 0; i < 16; i++)
    {
      hashmap_erase (hm, arr + i);
      ck_assert (hashmap_at (hm, arr + i) == NULL);
      ck_assert (!hashmap_contains (hm, arr + i));
    }

  hashmap_destroy (hm);
}

START_TEST (hashmap_test_2)
{
  int a = 24321, b = 78938, c = 18346;
  int val1 = 1, val2 = 2, val3 = 3;
  hashmap *hm = hashmap_create (cmp_int, size_func, NULL);

  ck_assert (hm != NULL);
  ck_assert (hashmap_size (hm) == 0);
  ck_assert_uint_eq (hashmap_bucket_count (hm),
                     HASHMAP_STARTING_NUMBER_OF_BUCKETS);

  hashmap_insert (hm, &a, &val1);
  ck_assert_uint_eq (hashmap_size (hm), 1);
  ck_assert (hashmap_at (hm, &a) == &val1);

  hashmap_insert (hm, &b, &val2);
  ck_assert_uint_eq (hashmap_size (hm), 2);
  ck_assert (hashmap_at (hm, &b) == &val2);

  hashmap_insert (hm, &c, &val3);
  ck_assert_uint_eq (hashmap_size (hm), 3);
  ck_assert (hashmap_at (hm, &c) == &val3);

  hashmap_clear (hm);
  ck_assert (hashmap_size (hm) == 0);

  hashmap_destroy (hm);
}

START_TEST (hashmap_test_3)
{
  int a = 24321; //, b = 78938, c = 18346;
  int val1 = 1;  //, val2 = 2, val3 = 3;
  hashmap *hm = hashmap_create (cmp_int, size_func, destr);

  struct pair *pr = pair_create (&a, &val1);
  pair_destroy (pr, pair_destr);

  ck_assert (hm != NULL);
  ck_assert (hashmap_size (hm) == 0);
  ck_assert_uint_eq (hashmap_bucket_count (hm),
                     HASHMAP_STARTING_NUMBER_OF_BUCKETS);

  hashmap_insert (hm, &a, &val1);
  ck_assert_uint_eq (hashmap_size (hm), 1);
  ck_assert (hashmap_at (hm, &a) == &val1);

  hashmap_destroy (hm);
}

START_TEST (hashmap_test_4)
{
  int arr[1000000] = {0};
  int i;
  hashmap *hm = hashmap_create (cmp_int, size_func, NULL);
  for(i = 0; i < 100000; i++)
  {
    arr[i] = i;
    hashmap_insert(hm, &i, arr + i);
  }

  for(int i = 0; i < 100000; i++)
  {
    hashmap_erase(hm, arr + i);
  }

  hashmap_destroy (hm);
}

Suite *
suite_hashmap ()
{
  Suite *s;
  TCase *tc;

  s = suite_create ("Hashmap test");
  tc = tcase_create ("Hashmap test");

  tcase_add_test (tc, hashmap_test_1);
  tcase_add_test (tc, hashmap_test_2);
  tcase_add_test (tc, hashmap_test_3);
  tcase_add_test (tc, hashmap_test_4);

  suite_add_tcase (s, tc);

  return s;
}