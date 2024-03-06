#include "test.h"

void
destr (dptr data)
{
  data = data;
  return;
}

bool
cmp (constdptr f, constdptr s)
{
  return (*(int *)f == *(int *)s);
}

bool
predicate1 (constdptr data)
{
  return (*(int *)data == 1 || *(int *)data == 2);
}

bool
predicate2 (constdptr data)
{
  return (*(int *)data == 1);
}

dptr
cpy (constdptr data)
{
  return (dptr)data;
}

START_TEST (array_test_1)
{
  int a = 1, b = 2, c = 3;

  size_t capacity = 2;
  array *arr = array_create (capacity);
  ck_assert (arr != NULL);
  ck_assert (array_empty (arr));
  ck_assert (arr->vec != NULL);
  ck_assert (arr->size == 0);
  ck_assert (arr->capacity == capacity);
  ck_assert_uint_eq (sizeof (arr->vec), sizeof (dptr));

  array_push_back (arr, &a);
  ck_assert (!array_empty (arr));
  ck_assert (arr != NULL);
  ck_assert (arr->vec != NULL);
  ck_assert (arr->size == 1);
  ck_assert (arr->capacity == capacity);
  ck_assert (sizeof (arr->vec) == sizeof (dptr));
  ck_assert (array_front (arr) == &a);
  ck_assert (*array_begin (arr) == &a);

  array_push_back (arr, &b);
  ck_assert (!array_empty (arr));
  ck_assert (arr != NULL);
  ck_assert (arr->vec != NULL);
  ck_assert (arr->size == 2);
  ck_assert (arr->capacity == capacity);
  ck_assert_uint_eq (sizeof (arr->vec), sizeof (dptr));
  ck_assert (array_front (arr) == &a);
  ck_assert (*array_begin (arr) == &a);
  ck_assert (array_back (arr) == &b);
  ck_assert (*array_rbegin (arr) == &b);

  array_push_back (arr, &c);
  ck_assert (!array_empty (arr));
  ck_assert (arr != NULL);
  ck_assert (arr->vec != NULL);
  ck_assert (arr->size == 3);
  ck_assert (arr->capacity == 4);
  ck_assert_uint_eq (sizeof (arr->vec), sizeof (dptr));
  ck_assert (array_front (arr) == &a);
  ck_assert (*array_begin (arr) == &a);
  ck_assert (array_back (arr) == &c);
  ck_assert (*array_rbegin (arr) == &c);
  ck_assert (array_at (arr, 0) == &a);
  ck_assert (array_at (arr, 1) == &b);
  ck_assert (array_at (arr, 2) == &c);

  array_pop_back (arr, destr);
  ck_assert (!array_empty (arr));
  ck_assert (arr->size == 2);
  ck_assert (arr->capacity == 4);
  ck_assert_uint_eq (sizeof (arr->vec), sizeof (dptr));
  ck_assert (array_front (arr) == &a);
  ck_assert (*array_begin (arr) == &a);
  ck_assert (array_back (arr) == &b);
  ck_assert (*array_rbegin (arr) == &b);

  array_pop_back (arr, destr);
  ck_assert (!array_empty (arr));
  ck_assert (arr->size == 1);
  ck_assert (arr->capacity == 4);
  ck_assert_uint_eq (sizeof (arr->vec), sizeof (dptr));
  ck_assert (array_front (arr) == &a);
  ck_assert (*array_begin (arr) == &a);
  ck_assert (array_back (arr) == &a);
  ck_assert (*array_rbegin (arr) == &a);
  ck_assert (array_at (arr, 2) == NULL);

  array_pop_back (arr, destr);
  ck_assert (array_empty (arr));
  ck_assert (arr->size == 0);
  ck_assert (arr->capacity == 4);

  array_front (arr);
  array_back (arr);
  array_begin (arr);
  array_rbegin (arr);
  ck_assert (array_at (arr, -1) == NULL);

  array_destroy (arr, destr);
}

START_TEST (array_test_2)
{
  int a = 1, b = 2, c = 3, d = 4, e = 5;

  size_t capacity = 2;
  array *arr = array_create (capacity);

  array_push_back (arr, &a);
  array_push_back (arr, &b);
  array_push_back (arr, &c);
  array_push_back (arr, &d);
  array_push_back (arr, &e);

  array *arr1 = array_copy (arr, cpy);

  dptr *raw = array_data (arr);
  ck_assert (arr->size == arr1->size);
  ck_assert (arr->capacity == arr1->capacity);
  for (int i = 0; i < 5; i++)
    {
      ck_assert (arr->vec[i] == arr1->vec[i]);
      ck_assert (raw[i] == arr->vec[i]);
    }
  ck_assert (array_capacity (arr) == 8);
  ck_assert (array_at (arr, 4) == &e);

  array_clear (arr, destr);
  ck_assert (array_size (arr) == 0);

  array_destroy (arr1, destr);
  array_destroy (arr, destr);
}

START_TEST (array_test_3)
{
  int pattern = 1;
  int a[] = { 1, 2, 3, 3, 2, 1, 1, 2 };

  size_t capacity = 2;
  array *arr = array_create (capacity);

  for (int i = 0; i < 8; i++)
    array_push_back (arr, a + i);

  ck_assert (array_count (arr, &pattern, cmp) == 3);
  ck_assert (array_count_if (arr, predicate1) == 6);

  dptr *raw = array_data (arr);
  array_data (NULL);

  ck_assert (*(int *)raw[5] == 1);

  array_destroy (arr, destr);
}

START_TEST (array_test_4)
{
  int a[] = { 1, 2, 3, 3, 2, 1, 1, 2 };

  size_t capacity = 2;
  array *arr = array_create (capacity);

  for (int i = 0; i < 8; i++)
    array_push_back (arr, a + i);

  ck_assert (array_erase (arr, arr->vec, destr) == arr->vec);

  ck_assert (arr->size == 7);
  for (size_t i = 0; i < 7; i++)
    ck_assert_uint_eq ((uint64_t)(a + i + 1), (uint64_t)(arr->vec[i]));

  ck_assert (array_erase (arr, arr->vec + 10, destr) == NULL);
  ck_assert (arr->size == 7);

  ck_assert (array_erase (arr, arr->vec + 6, destr) == NULL);
  ck_assert (arr->size == 6);
  for (size_t i = 0; i < 6; i++)
    ck_assert_uint_eq ((uint64_t)(a + i + 1), (uint64_t)(arr->vec[i]));

  ck_assert (array_erase (arr, arr->vec + 2, destr) == arr->vec + 2);
  ck_assert (arr->size == 5);

  for (size_t i = 0; i < 2; i++)
    ck_assert_uint_eq ((uint64_t)(a + i + 1), (uint64_t)(arr->vec[i]));
  for (size_t i = 2; i < 5; i++)
    ck_assert_uint_eq ((uint64_t)(a + i + 2), (uint64_t)(arr->vec[i]));

  array_destroy (arr, destr);

  ck_assert (array_end () == NULL);
  ck_assert (array_rend () == NULL);
}

START_TEST (array_test_5)
{
  int a[] = { 1, 2, 3, 3, 2, 1, 1, 2, 5 };
  int pattern = 1;
  size_t capacity = 2;
  array *arr = array_create (capacity);

  for (int i = 0; i < 9; i++)
    array_push_back (arr, a + i);

  ck_assert (array_capacity (arr) == 16);
  array_shrink_to_fit (arr);
  ck_assert (array_capacity (arr) == array_size (arr));

  ck_assert (arr->vec == array_find (arr, &pattern, cmp));
  array_erase (arr, arr->vec, destr);
  ck_assert (arr->vec + 4 == array_find (arr, &pattern, cmp));
  array_erase (arr, arr->vec + 4, destr);
  ck_assert (arr->vec + 4 == array_find (arr, &pattern, cmp));
  array_erase (arr, arr->vec + 4, destr);
  ck_assert (NULL == array_find (arr, &pattern, cmp));

  array_destroy (arr, destr);
}

START_TEST (array_test_6)
{
  int a[] = { 1, 2, 3, 3, 2, 1, 1, 2, 5 };
  size_t capacity = 2;
  array *arr = array_create (capacity);

  for (int i = 0; i < 9; i++)
    array_push_back (arr, a + i);

  ck_assert (array_capacity (arr) == 16);
  array_shrink_to_fit (arr);
  ck_assert (array_capacity (arr) == array_size (arr));

  ck_assert (arr->vec == array_find_if (arr, predicate2));
  array_erase (arr, arr->vec, destr);
  ck_assert (arr->vec + 4 == array_find_if (arr, predicate2));
  array_erase (arr, arr->vec + 4, destr);
  ck_assert (arr->vec + 4 == array_find_if (arr, predicate2));
  array_erase (arr, arr->vec + 4, destr);
  ck_assert (NULL == array_find_if (arr, predicate2));

  array_destroy (arr, destr);
}

START_TEST (array_test_7)
{
  int a[] = { 1, 2, 3, 3, 2, 1, 1, 2, 5 };
  int pattern = 1;
  size_t capacity = 2;
  array *arr = array_create (capacity);

  for (int i = 0; i < 9; i++)
    array_push_back (arr, a + i);

  ck_assert (array_capacity (arr) == 16);
  array_shrink_to_fit (arr);
  ck_assert (array_capacity (arr) == array_size (arr));

  ck_assert (arr->vec + 6 == array_rfind (arr, &pattern, cmp));
  array_erase (arr, arr->vec + 6, destr);
  ck_assert (arr->vec + 5 == array_rfind (arr, &pattern, cmp));
  array_erase (arr, arr->vec + 5, destr);
  ck_assert (arr->vec == array_rfind (arr, &pattern, cmp));
  array_erase (arr, arr->vec, destr);
  ck_assert (NULL == array_rfind (arr, &pattern, cmp));

  array_destroy (arr, destr);
}

START_TEST (array_test_8)
{
  int a[] = { 1, 2, 3, 3, 2, 1, 1, 2, 5 };
  size_t capacity = 2;
  array *arr = array_create (capacity);

  for (int i = 0; i < 9; i++)
    array_push_back (arr, a + i);

  ck_assert (array_capacity (arr) == 16);
  array_shrink_to_fit (arr);
  ck_assert (array_capacity (arr) == array_size (arr));

  ck_assert (arr->vec + 6 == array_rfind_if (arr, predicate2));
  array_erase (arr, arr->vec + 6, destr);
  ck_assert (arr->vec + 5 == array_rfind_if (arr, predicate2));
  array_erase (arr, arr->vec + 5, destr);
  ck_assert (arr->vec == array_rfind_if (arr, predicate2));
  array_erase (arr, arr->vec, destr);
  ck_assert (NULL == array_rfind_if (arr, predicate2));

  array_destroy (arr, destr);
}

START_TEST (array_test_9)
{
  int a = 1, b = 2, c = 3, d = 4, e = 5;

  size_t capacity = 2;
  array *arr = array_create (capacity);

  array_insert (arr, NULL, &a);
  ck_assert (array_size (arr) == 1);
  ck_assert (array_front (arr) == &a);
  ck_assert (*array_begin (arr) == &a);
  ck_assert (array_back (arr) == &a);
  ck_assert (*array_rbegin (arr) == &a);

  array_insert (arr, NULL, &b);
  ck_assert (array_size (arr) == 2);
  ck_assert (array_front (arr) == &a);
  ck_assert (*array_begin (arr) == &a);
  ck_assert (array_back (arr) == &b);
  ck_assert (*array_rbegin (arr) == &b);

  array_emplace (arr, arr->vec, &c);
  ck_assert (array_size (arr) == 3);
  ck_assert (array_front (arr) == &c);
  ck_assert (*array_begin (arr) == &c);
  ck_assert (arr->vec[1] == &a);
  ck_assert (array_back (arr) == &b);
  ck_assert (*array_rbegin (arr) == &b);

  array_emplace (arr, arr->vec + 2, &d);
  ck_assert (array_size (arr) == 4);
  ck_assert (array_front (arr) == &c);
  ck_assert (*array_begin (arr) == &c);
  ck_assert (arr->vec[1] == &a);
  ck_assert (arr->vec[2] == &d);
  ck_assert (array_back (arr) == &b);
  ck_assert (*array_rbegin (arr) == &b);

  array_reserve (arr, 13);
  ck_assert (array_size (arr) == 4);
  ck_assert (array_front (arr) == &c);
  ck_assert (*array_begin (arr) == &c);
  ck_assert (arr->vec[1] == &a);
  ck_assert (arr->vec[2] == &d);
  ck_assert (array_back (arr) == &b);
  ck_assert (*array_rbegin (arr) == &b);
  ck_assert (arr->capacity == 13);

  array_emplace_back (arr, &e);
  ck_assert (array_size (arr) == 5);
  ck_assert (array_front (arr) == &c);
  ck_assert (*array_begin (arr) == &c);
  ck_assert (arr->vec[1] == &a);
  ck_assert (arr->vec[2] == &d);
  ck_assert (arr->vec[3] == &b);
  ck_assert (array_back (arr) == &e);
  ck_assert (*array_rbegin (arr) == &e);

  array_destroy (arr, destr);
}

Suite *
suite_array ()
{
  Suite *s;
  TCase *tc;

  s = suite_create ("Array test");
  tc = tcase_create ("Array test");

  tcase_add_test (tc, array_test_1);
  tcase_add_test (tc, array_test_2);
  tcase_add_test (tc, array_test_3);
  tcase_add_test (tc, array_test_4);
  tcase_add_test (tc, array_test_5);
  tcase_add_test (tc, array_test_6);
  tcase_add_test (tc, array_test_7);
  tcase_add_test (tc, array_test_8);
  tcase_add_test (tc, array_test_9);

  suite_add_tcase (s, tc);

  return s;
}