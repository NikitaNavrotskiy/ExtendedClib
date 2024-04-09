#include "test.h"

static int
cmp (constdptr first, constdptr second)
{
  return *(int *)first - *(int *)second;
}

static void
destr (dptr data)
{
  data = data;
}

START_TEST (set_test_1)
{
  set *s = set_create (cmp, NULL);
  int arr[100];

  for (int j = 0; j < 20; j++)
    {
      for (int i = 0; i < 100; i++)
        {
          int randint = rand ();
          arr[i] = randint;
        }

      for (int i = 0; i < 100; i++)
        {
          set_insert (s, arr + i);
          ck_assert (set_contains (s, arr + i));
          ck_assert (set_size (s) == (size_t)i + 1);
        }
      set_iterator prev = set_begin (s);
      for (set_iterator beg = set_begin (s); beg != set_end ();
           beg = set_next (beg))
        {
          ck_assert (s->tree->cmp (prev->data, beg->data) <= 0);
          prev = beg;
        }

      prev = set_rbegin (s);
      for (set_iterator beg = set_rbegin (s); beg != set_rend ();
           beg = set_prev (beg))
        {
          ck_assert (s->tree->cmp (prev->data, beg->data) >= 0);
          prev = beg;
        }

      size_t count = set_size (s);
      while (s->tree->root)
        {
          int index = rand () % 100;
          set_iterator tmp = set_find (s, arr + index);

          if (tmp)
            {
              set_remove (s, arr + index);
              ck_assert (s->tree->size == count - 1);
              count = s->tree->size;
            }
        }
    }

  set_destroy (s);
}

START_TEST (set_test_2)
{
  set *s = set_create (cmp, destr);
  int arr[100];

  for (int j = 0; j < 20; j++)
    {
      for (int i = 0; i < 100; i++)
        {
          int randint = rand () % 100;
          arr[i] = randint;
        }

      for (int i = 0; i < 100; i++)
        {
          set_insert (s, arr + i);
          ck_assert (set_contains (s, arr + i));
          ck_assert (set_size (s) <= (size_t)i + 1);
        }
      set_iterator prev = set_begin (s);
      for (set_iterator beg = set_begin (s); beg != set_end ();
           beg = set_next (beg))
        {
          ck_assert (s->tree->cmp (prev->data, beg->data) <= 0);
          prev = beg;
        }

      prev = set_rbegin (s);
      for (set_iterator beg = set_rbegin (s); beg != set_rend ();
           beg = set_prev (beg))
        {
          ck_assert (s->tree->cmp (prev->data, beg->data) >= 0);
          prev = beg;
        }

      size_t count = set_size (s);
      while (s->tree->root)
        {
          int index = rand () % 100;
          set_iterator tmp = set_find (s, arr + index);

          if (tmp)
            {
              set_remove (s, arr + index);
              ck_assert (s->tree->size == count - 1);
              count = s->tree->size;
            }
        }
    }

  set_destroy (s);
}

START_TEST (set_test_3)
{
  int d = 235;
  set *s = set_create (cmp, destr);

  int arr[10] = { 2, 1, 3, 4, 5, 6, 7, 8, 9, 9 };

  for (int i = 8; i >= 0; i--)
    {
      set_insert (s, arr + i);
    }

  set_erase (s, set_find (s, arr));

  ck_assert (set_count (s, &d) == 0);
  for (int i = 1; i < 8; i++)
    ck_assert (set_count (s, arr + i) == 1);
  ck_assert (set_count (s, arr + 9) == 1);
  set_clear (s);
  ck_assert (s->tree->size == 0);
  ck_assert (set_empty (s));

  set_destroy (s);
}

Suite *
suite_set ()
{
  Suite *s;
  TCase *tc;

  s = suite_create ("Set test");
  tc = tcase_create ("Set test");

  tcase_add_test (tc, set_test_1);
  tcase_add_test (tc, set_test_2);
  tcase_add_test (tc, set_test_3);

  suite_add_tcase (s, tc);

  return s;
}
