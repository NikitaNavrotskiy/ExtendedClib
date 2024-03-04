#include "test.h"

void
standart_destructor (dptr data)
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
predicate1 (constdptr d)
{
  return (*(int *)d) >= 2 && (*(int *)d) < 4;
}

bool
predicate2 (constdptr d)
{
  return (*(int *)d) < 2 || (*(int *)d) > 3;
}

bool
predicate3 (constdptr d)
{
  return (*(int *)d == 2 || (*(int *)d == 3));
}

bool
predicate4 (constdptr d)
{
  return (*(int *)d > 4);
}

dptr
copy_func (dptr val)
{
  return val;
}

START_TEST (list_test_1)
{
  int a = 1, b = 2;
  list *l = list_create ();
  ck_assert (l != NULL);
  ck_assert (list_empty (l));
  ck_assert (list_size (l) == 0);
  ck_assert (list_back (l) == NULL);
  ck_assert (list_front (l) == NULL);
  ck_assert (list_begin (l) == NULL);
  ck_assert (list_end () == NULL);

  list_push_back (l, &a);
  ck_assert (!list_empty (l));
  ck_assert (list_size (l) == 1);
  ck_assert (*(int *)list_back (l) == a);
  ck_assert (*(int *)list_front (l) == a);
  ck_assert (*(int *)list_begin (l)->data == a);
  ck_assert (list_end () == NULL);

  list_pop_back (l, standart_destructor);

  ck_assert (list_empty (l));
  ck_assert (list_size (l) == 0);
  ck_assert (list_back (l) == NULL);
  ck_assert (list_front (l) == NULL);
  ck_assert (list_begin (l) == NULL);
  ck_assert (list_end () == NULL);

  list_push_front (l, &a);
  ck_assert (!list_empty (l));
  ck_assert (list_size (l) == 1);
  ck_assert (*(int *)list_back (l) == a);
  ck_assert (*(int *)list_front (l) == a);
  ck_assert (*(int *)list_begin (l)->data == a);
  ck_assert (list_end () == NULL);

  list_pop_front (l, standart_destructor);
  ck_assert (list_empty (l));
  ck_assert (list_size (l) == 0);
  ck_assert (list_back (l) == NULL);
  ck_assert (list_front (l) == NULL);
  ck_assert (list_begin (l) == NULL);
  ck_assert (list_end () == NULL);

  list_push_back (l, &a);
  ck_assert (!list_empty (l));
  ck_assert (list_size (l) == 1);
  ck_assert (*(int *)list_back (l) == a);
  ck_assert (*(int *)list_front (l) == a);
  ck_assert (*(int *)list_begin (l)->data == a);
  ck_assert (list_end () == NULL);

  list_push_back (l, &b);
  ck_assert (!list_empty (l));
  ck_assert (list_size (l) == 2);
  ck_assert (*(int *)list_back (l) == b);
  ck_assert (*(int *)list_front (l) == a);
  ck_assert (*(int *)list_begin (l)->data == a);
  ck_assert (list_end () == NULL);

  list_pop_back (l, standart_destructor);
  ck_assert (!list_empty (l));
  ck_assert (list_size (l) == 1);
  ck_assert (*(int *)list_back (l) == a);
  ck_assert (*(int *)list_front (l) == a);
  ck_assert (*(int *)list_begin (l)->data == a);
  ck_assert (list_end () == NULL);

  list_push_front (l, &b);
  ck_assert (!list_empty (l));
  ck_assert (list_size (l) == 2);
  ck_assert (*(int *)list_back (l) == a);
  ck_assert (*(int *)list_front (l) == b);
  ck_assert (*(int *)list_begin (l)->data == b);
  ck_assert (list_end () == NULL);

  list_pop_front (l, standart_destructor);
  ck_assert (!list_empty (l));
  ck_assert (list_size (l) == 1);
  ck_assert (*(int *)list_back (l) == a);
  ck_assert (*(int *)list_front (l) == a);
  ck_assert (*(int *)list_begin (l)->data == a);
  ck_assert (list_end () == NULL);

  list_clear (l, standart_destructor);
  ck_assert (list_empty (l));
  ck_assert (list_size (l) == 0);
  ck_assert (list_size (l) == 0);
  ck_assert (list_back (l) == NULL);
  ck_assert (list_front (l) == NULL);
  ck_assert (list_begin (l) == NULL);
  ck_assert (list_end () == NULL);

  int i;
  int arr[1000] = { 0 };
  for (i = 0; i < 1000; i++)
    {
      arr[i] = i;
      list_push_back (l, arr + i);
      ck_assert (!list_empty (l));
      ck_assert (list_size (l) == (size_t)(arr[i] + 1));
      ck_assert_uint_eq (*(int *)list_back (l), arr[i]);
      ck_assert_uint_eq (*(int *)list_front (l), 0);
      ck_assert (list_begin (l)->data == (dptr)arr);
      ck_assert (list_end () == NULL);
    }

  for (i = 999; i > 0; i--)
    {
      ck_assert (!list_empty (l));
      list_pop_back (l, standart_destructor);
      ck_assert (list_size (l) == (size_t)arr[i]);
      ck_assert_uint_eq (*(int *)list_back (l), arr[i] - 1);
      ck_assert (*(int *)list_front (l) == 0);
      ck_assert (list_begin (l)->data == (dptr)arr);
      ck_assert (list_end () == NULL);
    }

  list_pop_back (l, standart_destructor);
  ck_assert (list_empty (l));
  ck_assert (list_size (l) == 0);
  ck_assert (list_back (l) == NULL);
  ck_assert (list_front (l) == NULL);
  ck_assert (list_begin (l) == NULL);
  ck_assert (list_end () == NULL);

  for (int i = 0; i < 1000; i++)
    arr[i] = 0;

  for (i = 0; i < 1000; i++)
    {
      arr[i] = i;
      list_push_front (l, arr + i);
      ck_assert (!list_empty (l));
      ck_assert (list_size (l) == (size_t)(arr[i] + 1));
      ck_assert_uint_eq (*(int *)list_back (l), 0);
      ck_assert_uint_eq (*(int *)list_front (l), i);
      ck_assert_ptr_eq (list_begin (l)->data, (dptr)(arr + i));
      ck_assert (list_end () == NULL);
    }

  for (i = 999; i > 0; i--)
    {
      list_pop_front (l, standart_destructor);
      ck_assert (!list_empty (l));
      ck_assert (list_size (l) == (size_t)arr[i]);
      ck_assert_uint_eq (*(int *)list_back (l), 0);
      ck_assert (*(int *)list_front (l) == arr[i] - 1);
      ck_assert (list_begin (l)->data == (dptr)(arr + i - 1));
      ck_assert (list_end () == NULL);
    }

  list_pop_back (l, standart_destructor);
  ck_assert (list_empty (l));
  ck_assert (list_size (l) == 0);
  ck_assert (list_back (l) == NULL);
  ck_assert (list_front (l) == NULL);
  ck_assert (list_begin (l) == NULL);
  ck_assert (list_end () == NULL);

  list_destroy (l, standart_destructor);
}

START_TEST (list_test_2)
{
  list *l = list_create ();
  ck_assert (l != NULL);
  ck_assert (list_empty (l));
  ck_assert (list_size (l) == 0);
  ck_assert (list_back (l) == NULL);
  ck_assert (list_front (l) == NULL);
  ck_assert (list_begin (l) == NULL);
  ck_assert (list_end () == NULL);

  int arr[1000] = { 0 };
  for (int i = 0; i < 1000; i++)
    {
      arr[i] = i;
      list_push_back (l, arr + i);
    }

  list *lcp = list_copy (l, copy_func);

  ck_assert_uint_eq (list_size (l), list_size (lcp));
  for (list_iterator li = list_begin (l), licp = list_begin (lcp);
       li != list_end () && licp != list_end ();
       li = li->next, licp = licp->next)
    ck_assert_int_eq (*(int *)li->data, *(int *)licp->data);

  list_destroy (l, standart_destructor);
  list_destroy (lcp, standart_destructor);
}

START_TEST (list_test_3)
{
  list *l = list_create ();
  int arr[10][50] = { 0 };

  for (int j = 0; j < 10; j++)
    {
      for (int i = 0; i < 5; i++)
        {
          arr[j][i] = i;
          list_push_back (l, &arr[j][i]);
        }
    }

  int i;
  for (i = 0; i < 5; i++)
    {
      ck_assert_uint_eq (list_count (l, &i, cmp), 10);
    }

  i = 6;
  ck_assert (list_count (l, &i, cmp) == 0);

  ck_assert (list_count_if (l, predicate1) == 20);
  ck_assert (list_count_if (l, predicate2) == 30);

  list_destroy (l, standart_destructor);
}

START_TEST (list_test_4)
{
  list *l = list_create ();
  int a = 1, b = 2, c = 3, d = 4;

  list_emplace (l, NULL, &b);
  ck_assert (!list_empty (l));
  ck_assert (list_size (l) == 1);
  ck_assert (*(int *)list_back (l) == b);
  ck_assert (*(int *)list_front (l) == b);
  ck_assert (*(int *)list_begin (l)->data == b);
  ck_assert (list_end () == NULL);

  list_emplace (l, NULL, &c);
  ck_assert (!list_empty (l));
  ck_assert (list_size (l) == 2);
  ck_assert (*(int *)list_back (l) == c);
  ck_assert (*(int *)list_front (l) == b);
  ck_assert (*(int *)list_begin (l)->data == b);
  ck_assert (list_end () == NULL);

  list_emplace (l, list_begin (l), &a);
  ck_assert (!list_empty (l));
  ck_assert (list_size (l) == 3);
  ck_assert (*(int *)list_back (l) == c);
  ck_assert (*(int *)list_front (l) == a);
  ck_assert (*(int *)list_begin (l)->data == a);
  ck_assert (list_end () == NULL);

  list_emplace (l, list_begin (l)->next->next, &d);
  ck_assert (*(int *)l->back->prev->data == d);
  ck_assert (*(int *)l->front->next->next->data == d);
  ck_assert (!list_empty (l));
  ck_assert (list_size (l) == 4);
  ck_assert (*(int *)list_back (l) == c);
  ck_assert (*(int *)list_front (l) == a);
  ck_assert (*(int *)list_begin (l)->data == a);
  ck_assert (list_end () == NULL);

  list_destroy (l, standart_destructor);
}

START_TEST (list_test_5)
{
  int a = 1, b = 2;
  list *l = list_create ();
  ck_assert (l != NULL);
  ck_assert (list_empty (l));
  ck_assert (list_size (l) == 0);
  ck_assert (list_back (l) == NULL);
  ck_assert (list_front (l) == NULL);
  ck_assert (list_begin (l) == NULL);
  ck_assert (list_end () == NULL);

  list_emplace_back (l, &a);
  ck_assert (!list_empty (l));
  ck_assert (list_size (l) == 1);
  ck_assert (*(int *)list_back (l) == a);
  ck_assert (*(int *)list_front (l) == a);
  ck_assert (*(int *)list_begin (l)->data == a);
  ck_assert (list_end () == NULL);

  list_pop_back (l, standart_destructor);

  ck_assert (list_empty (l));
  ck_assert (list_size (l) == 0);
  ck_assert (list_back (l) == NULL);
  ck_assert (list_front (l) == NULL);
  ck_assert (list_begin (l) == NULL);
  ck_assert (list_end () == NULL);

  list_emplace_front (l, &a);
  ck_assert (!list_empty (l));
  ck_assert (list_size (l) == 1);
  ck_assert (*(int *)list_back (l) == a);
  ck_assert (*(int *)list_front (l) == a);
  ck_assert (*(int *)list_begin (l)->data == a);
  ck_assert (list_end () == NULL);

  list_pop_front (l, standart_destructor);
  ck_assert (list_empty (l));
  ck_assert (list_size (l) == 0);
  ck_assert (list_back (l) == NULL);
  ck_assert (list_front (l) == NULL);
  ck_assert (list_begin (l) == NULL);
  ck_assert (list_end () == NULL);

  list_emplace_back (l, &a);
  ck_assert (!list_empty (l));
  ck_assert (list_size (l) == 1);
  ck_assert (*(int *)list_back (l) == a);
  ck_assert (*(int *)list_front (l) == a);
  ck_assert (*(int *)list_begin (l)->data == a);
  ck_assert (list_end () == NULL);

  list_emplace_back (l, &b);
  ck_assert (!list_empty (l));
  ck_assert (list_size (l) == 2);
  ck_assert (*(int *)list_back (l) == b);
  ck_assert (*(int *)list_front (l) == a);
  ck_assert (*(int *)list_begin (l)->data == a);
  ck_assert (list_end () == NULL);

  list_pop_back (l, standart_destructor);
  ck_assert (!list_empty (l));
  ck_assert (list_size (l) == 1);
  ck_assert (*(int *)list_back (l) == a);
  ck_assert (*(int *)list_front (l) == a);
  ck_assert (*(int *)list_begin (l)->data == a);
  ck_assert (list_end () == NULL);

  list_emplace_front (l, &b);
  ck_assert (!list_empty (l));
  ck_assert (list_size (l) == 2);
  ck_assert (*(int *)list_back (l) == a);
  ck_assert (*(int *)list_front (l) == b);
  ck_assert (*(int *)list_begin (l)->data == b);
  ck_assert (list_end () == NULL);

  list_pop_front (l, standart_destructor);
  ck_assert (!list_empty (l));
  ck_assert (list_size (l) == 1);
  ck_assert (*(int *)list_back (l) == a);
  ck_assert (*(int *)list_front (l) == a);
  ck_assert (*(int *)list_begin (l)->data == a);
  ck_assert (list_end () == NULL);

  list_clear (l, standart_destructor);
  ck_assert (list_empty (l));
  ck_assert (list_size (l) == 0);
  ck_assert (list_size (l) == 0);
  ck_assert (list_back (l) == NULL);
  ck_assert (list_front (l) == NULL);
  ck_assert (list_begin (l) == NULL);
  ck_assert (list_end () == NULL);

  int i;
  int arr[1000] = { 0 };
  for (i = 0; i < 1000; i++)
    {
      arr[i] = i;
      list_emplace_back (l, arr + i);
      ck_assert (!list_empty (l));
      ck_assert (list_size (l) == (size_t)(arr[i] + 1));
      ck_assert_uint_eq (*(int *)list_back (l), arr[i]);
      ck_assert_uint_eq (*(int *)list_front (l), 0);
      ck_assert (list_begin (l)->data == (dptr)arr);
      ck_assert (list_end () == NULL);
    }

  for (i = 999; i > 0; i--)
    {
      ck_assert (!list_empty (l));
      list_pop_back (l, standart_destructor);
      ck_assert (list_size (l) == (size_t)arr[i]);
      ck_assert_uint_eq (*(int *)list_back (l), arr[i] - 1);
      ck_assert (*(int *)list_front (l) == 0);
      ck_assert (list_begin (l)->data == (dptr)arr);
      ck_assert (list_end () == NULL);
    }

  list_pop_back (l, standart_destructor);
  ck_assert (list_empty (l));
  ck_assert (list_size (l) == 0);
  ck_assert (list_back (l) == NULL);
  ck_assert (list_front (l) == NULL);
  ck_assert (list_begin (l) == NULL);
  ck_assert (list_end () == NULL);

  for (int i = 0; i < 1000; i++)
    arr[i] = 0;

  for (i = 0; i < 1000; i++)
    {
      arr[i] = i;
      list_emplace_front (l, arr + i);
      ck_assert (!list_empty (l));
      ck_assert (list_size (l) == (size_t)(arr[i] + 1));
      ck_assert_uint_eq (*(int *)list_back (l), 0);
      ck_assert_uint_eq (*(int *)list_front (l), i);
      ck_assert_ptr_eq (list_begin (l)->data, (dptr)(arr + i));
      ck_assert (list_end () == NULL);
    }

  for (i = 999; i > 0; i--)
    {
      list_pop_front (l, standart_destructor);
      ck_assert (!list_empty (l));
      ck_assert (list_size (l) == (size_t)arr[i]);
      ck_assert_uint_eq (*(int *)list_back (l), 0);
      ck_assert (*(int *)list_front (l) == arr[i] - 1);
      ck_assert (list_begin (l)->data == (dptr)(arr + i - 1));
      ck_assert (list_end () == NULL);
    }

  list_pop_back (l, standart_destructor);
  ck_assert (list_empty (l));
  ck_assert (list_size (l) == 0);
  ck_assert (list_back (l) == NULL);
  ck_assert (list_front (l) == NULL);
  ck_assert (list_begin (l) == NULL);
  ck_assert (list_end () == NULL);

  list_destroy (l, standart_destructor);
}

START_TEST (list_test_6)
{
  int a = 1, b = 2, c = 3;
  list *l = list_create ();

  list_push_back (l, &a);
  list_erase (l, list_begin (l), standart_destructor);
  ck_assert (l->front == NULL);
  ck_assert (l->back == NULL);
  ck_assert (l->size == 0);

  list_push_back (l, &a);
  list_push_back (l, &b);
  list_erase (l, list_begin (l), standart_destructor);
  ck_assert (*(int *)list_front (l) == b);
  ck_assert (*(int *)list_back (l) == b);
  ck_assert (l->size == 1);

  list_push_front (l, &a);
  list_erase (l, l->back, standart_destructor);
  ck_assert (*(int *)list_front (l) == a);
  ck_assert (*(int *)list_back (l) == a);
  ck_assert (l->size == 1);

  list_push_back (l, &b);
  list_push_back (l, &c);
  list_erase (l, l->front->next, standart_destructor);
  ck_assert (*(int *)list_front (l) == a);
  ck_assert (*(int *)list_back (l) == c);
  ck_assert (l->size == 2);

  list_destroy (l, standart_destructor);
}

START_TEST (list_test_7)
{
  int a = 1, b = 2, c = 3;
  list *l = list_create ();

  list_insert_many (l, NULL, 3, &a, &b, &c);
  ck_assert (*(int *)list_front (l) == a);
  ck_assert (*(int *)l->front->next->data == b);
  ck_assert (*(int *)list_back (l) == c);
  ck_assert (list_size (l) == 3);
  list_clear (l, standart_destructor);

  list_push_back (l, &a);
  list_insert_many (l, NULL, 2, &b, &c);
  ck_assert (*(int *)list_front (l) == a);
  ck_assert (*(int *)l->front->next->data == b);
  ck_assert (*(int *)list_back (l) == c);
  ck_assert (list_size (l) == 3);
  list_clear (l, standart_destructor);

  list_push_back (l, &c);
  list_insert_many (l, l->front, 2, &a, &b);
  ck_assert (*(int *)list_front (l) == a);
  ck_assert (*(int *)l->front->next->data == b);
  ck_assert (*(int *)list_back (l) == c);
  ck_assert (list_size (l) == 3);
  list_clear (l, standart_destructor);

  int d = 4, e = 5;

  list_push_front (l, &a);
  list_push_back (l, &e);
  list_insert_many (l, l->front->next, 3, &b, &c, &d);
  ck_assert (*(int *)list_front (l) == a);
  ck_assert (*(int *)l->front->next->data == b);
  ck_assert (*(int *)l->front->next->next->data == c);
  ck_assert (*(int *)l->front->next->next->next->data == d);
  ck_assert (*(int *)list_back (l) == e);
  ck_assert (list_size (l) == 5);
  list_clear (l, standart_destructor);

  list_destroy (l, standart_destructor);
}

START_TEST (list_test_8)
{
  int a = 1, b = 2, c = 3, d = 4, e = 5;
  list *l = list_create ();

  list_push_front (l, &a);
  list_push_back (l, &e);
  list_insert_many (l, l->front->next, 3, &b, &c, &d);

  list_erase_range (l, list_begin (l), list_end (), standart_destructor);
  ck_assert (l->front == NULL);
  ck_assert (l->back == NULL);
  ck_assert (list_size (l) == 0);

  list_push_front (l, &a);
  list_push_back (l, &e);
  list_insert_many (l, l->front->next, 3, &b, &c, &d);

  list_erase_range (l, list_begin (l), l->back->prev, standart_destructor);
  ck_assert (*(int *)l->front->data == e);
  ck_assert (*(int *)l->back->data == e);
  ck_assert (list_size (l) == 1);
  list_clear (l, standart_destructor);

  list_push_front (l, &a);
  list_push_back (l, &e);
  list_insert_many (l, l->front->next, 3, &b, &c, &d);

  list_erase_range (l, list_begin (l)->next, l->back, standart_destructor);
  ck_assert (*(int *)l->front->data == a);
  ck_assert (*(int *)l->back->data == a);
  ck_assert (list_size (l) == 1);
  list_clear (l, standart_destructor);

  list_push_front (l, &a);
  list_push_back (l, &e);
  list_insert_many (l, l->front->next, 3, &b, &c, &d);

  list_erase_range (l, list_begin (l)->next, l->back->prev,
                    standart_destructor);
  ck_assert (*(int *)l->front->data == a);
  ck_assert (*(int *)l->back->data == e);
  ck_assert (list_size (l) == 2);
  list_clear (l, standart_destructor);

  list_push_front (l, &a);
  list_push_back (l, &e);
  list_insert_many (l, l->front->next, 3, &b, &c, &d);

  list_erase_range (l, list_begin (l)->next, list_begin (l)->next,
                    standart_destructor);
  ck_assert (*(int *)l->front->data == a);
  ck_assert (*(int *)l->front->next->data == c);
  ck_assert (*(int *)l->front->next->next->data == d);
  ck_assert (*(int *)l->back->data == e);
  ck_assert (list_size (l) == 4);
  list_clear (l, standart_destructor);

  list_push_front (l, &a);
  list_push_back (l, &e);
  list_insert_many (l, l->front->next, 3, &b, &c, &d);

  list_erase_range (l, NULL, list_begin (l)->next, standart_destructor);
  ck_assert (*(int *)l->front->data == a);
  ck_assert (*(int *)l->front->next->data == b);
  ck_assert (*(int *)l->front->next->next->data == c);
  ck_assert (*(int *)l->front->next->next->next->data == d);
  ck_assert (*(int *)l->back->data == e);
  ck_assert (list_size (l) == 5);
  list_clear (l, standart_destructor);

  list_push_front (l, &a);
  list_push_back (l, &e);
  list_insert_many (l, l->front->next, 3, &b, &c, &d);

  list_erase_range (l, list_begin (l)->next, NULL, standart_destructor);
  ck_assert (*(int *)l->front->data == a);
  ck_assert (*(int *)l->back->data == a);
  ck_assert (list_size (l) == 1);
  list_clear (l, standart_destructor);

  list_destroy (l, standart_destructor);
}

START_TEST (list_test_9)
{
  int pattern = 1;
  list *l = list_create ();
  int arr[10] = { 1, 2, 3, 2, 2, 3, 1, 1, 2, 1 };

  for (int i = 0; i < 10; i++)
    {
      list_push_back (l, arr + i);
    }

  list_remove (l, &pattern, cmp, standart_destructor);

  ck_assert_uint_eq (list_size (l), 6);
  ck_assert (*(int *)l->front->data == arr[1]);
  ck_assert (*(int *)l->front->next->data == arr[2]);
  ck_assert (*(int *)l->front->next->next->data == arr[3]);
  ck_assert (*(int *)l->front->next->next->next->data == arr[4]);
  ck_assert (*(int *)l->back->data == arr[8]);
  ck_assert (*(int *)l->back->prev->data == arr[5]);
  list_clear (l, standart_destructor);

  for (int i = 0; i < 10; i++)
    {
      list_push_back (l, arr + i);
    }
  pattern = 5;
  list_remove (l, &pattern, cmp, standart_destructor);
  ck_assert (list_size (l) == 10);

  list_destroy (l, standart_destructor);
}

START_TEST (list_test_10)
{
  list *l = list_create ();
  int arr[10] = { 1, 2, 3, 2, 2, 3, 1, 1, 2, 1 };

  for (int i = 0; i < 10; i++)
    {
      list_push_back (l, arr + i);
    }

  list_remove_if (l, predicate3, standart_destructor);

  ck_assert_uint_eq (list_size (l), 4);
  ck_assert (*(int *)l->front->data == arr[0]);
  ck_assert (*(int *)l->front->next->data == arr[6]);
  ck_assert (*(int *)l->front->next->next->data == arr[7]);
  ck_assert (*(int *)l->front->next->next->next->data == arr[9]);
  list_clear (l, standart_destructor);

  for (int i = 0; i < 10; i++)
    {
      list_push_back (l, arr + i);
    }

  list_remove_if (l, predicate4, standart_destructor);
  ck_assert (list_size (l) == 10);

  list_destroy (l, standart_destructor);
}

START_TEST (list_test_11)
{
  int pattern = 1;
  list *l = list_create ();
  int arr[10] = { 1, 2, 3, 2, 2, 3, 1, 1, 2, 1 };

  for (int i = 0; i < 10; i++)
    {
      list_push_back (l, arr + i);
    }

  ck_assert (list_find (l, &pattern, cmp) == list_begin (l));
  list_erase (l, list_begin (l), standart_destructor);
  ck_assert (list_find (l, &pattern, cmp) == list_rbegin(l)->prev->prev->prev);
  list_erase (l, l->back->prev->prev->prev, standart_destructor);
  ck_assert (list_find (l, &pattern, cmp) == list_rbegin(l)->prev->prev);
  list_erase (l, l->back->prev->prev, standart_destructor);
  ck_assert (list_find (l, &pattern, cmp) == list_rbegin(l));
  list_erase (l, l->back, standart_destructor);
  ck_assert (list_find (l, &pattern, cmp) == list_end ());
  list_clear (l, standart_destructor);

  for (int i = 0; i < 10; i++)
    {
      list_push_back (l, arr + i);
    }

  ck_assert (list_rfind (l, &pattern, cmp) == l->back);
  list_erase (l, l->back, standart_destructor);
  ck_assert (list_rfind (l, &pattern, cmp) == l->back->prev);
  list_erase (l, l->back->prev, standart_destructor);
  ck_assert (list_rfind (l, &pattern, cmp) == l->back->prev);
  list_erase (l, l->back->prev, standart_destructor);
  ck_assert (list_rfind (l, &pattern, cmp) == list_begin (l));
  list_erase (l, list_begin (l), standart_destructor);
  ck_assert (list_rfind (l, &pattern, cmp) == list_end ());
  list_clear (l, standart_destructor);

  list_destroy (l, standart_destructor);
}

START_TEST (list_test_12)
{
  list *l = list_create ();
  int arr[10] = { 1, 2, 3, 2, 2, 3, 1, 1, 2, 1 };

  for (int i = 0; i < 10; i++)
    {
      list_push_back (l, arr + i);
    }

  ck_assert (list_find_if (l, predicate3) == l->front->next);
  list_erase (l, l->front->next, standart_destructor);
  ck_assert (list_find_if (l, predicate3) == l->front->next);
  list_erase (l, l->front->next, standart_destructor);
  ck_assert (list_find_if (l, predicate3) == l->front->next);
  list_erase (l, l->front->next, standart_destructor);
  ck_assert (list_find_if (l, predicate3) == l->front->next);
  list_erase (l, l->front->next, standart_destructor);
  ck_assert (list_find_if (l, predicate3) == l->front->next);
  list_erase (l, l->front->next, standart_destructor);
  ck_assert (list_find_if (l, predicate3) == l->back->prev);
  list_erase (l, l->back->prev, standart_destructor);
  ck_assert (list_find_if (l, predicate3) == list_end ());
  list_clear (l, standart_destructor);

  for (int i = 0; i < 10; i++)
    {
      list_push_back (l, arr + i);
    }

  ck_assert (list_rfind_if (l, predicate3) == l->back->prev);
  list_erase (l, l->back->prev, standart_destructor);
  ck_assert (list_rfind_if (l, predicate3)
             == l->front->next->next->next->next->next);
  list_erase (l, l->front->next->next->next->next->next, standart_destructor);
  ck_assert (list_rfind_if (l, predicate3)
             == l->front->next->next->next->next);
  list_erase (l, l->front->next->next->next->next, standart_destructor);
  ck_assert (list_rfind_if (l, predicate3) == l->front->next->next->next);
  list_erase (l, l->front->next->next->next, standart_destructor);
  ck_assert (list_rfind_if (l, predicate3) == l->front->next->next);
  list_erase (l, l->front->next->next, standart_destructor);
  ck_assert (list_rfind_if (l, predicate3) == l->front->next);
  list_erase (l, l->front->next, standart_destructor);
  ck_assert (list_rfind_if (l, predicate3) == list_end ());
  list_clear (l, standart_destructor);

  list_destroy (l, standart_destructor);
}

Suite *
suite_list ()
{
  Suite *s;
  TCase *tc;

  s = suite_create ("List test");
  tc = tcase_create ("List test");

  tcase_add_test (tc, list_test_1);
  tcase_add_test (tc, list_test_2);
  tcase_add_test (tc, list_test_3);
  tcase_add_test (tc, list_test_4);
  tcase_add_test (tc, list_test_5);
  tcase_add_test (tc, list_test_6);
  tcase_add_test (tc, list_test_7);
  tcase_add_test (tc, list_test_8);
  tcase_add_test (tc, list_test_9);
  tcase_add_test (tc, list_test_10);
  tcase_add_test (tc, list_test_11);
  tcase_add_test (tc, list_test_12);

  suite_add_tcase (s, tc);

  return s;
}