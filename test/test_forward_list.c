#include "test.h"


static void
standart_destructor (dptr data)
{
  data = data;
  return;
}

static dptr
copy_func (dptr val)
{
  return val;
}

static bool
cmp (constdptr f, constdptr s)
{
  return (*(int *)f == *(int *)s);
}

static bool
predicate1 (constdptr d)
{
  return (*(int *)d) >= 2 && (*(int *)d) < 4;
}

static bool
predicate2 (constdptr d)
{
  return (*(int *)d) < 2 || (*(int *)d) > 3;
}
/* 
static bool
predicate3 (constdptr d)
{
  return (*(int *)d == 2 || (*(int *)d == 3));
}
*/
static bool
predicate4 (constdptr d)
{
  return (*(int *)d > 41);
} 


START_TEST(forward_list_test_1)
{
  int a = 1, b = 2;
    forward_list *l = forward_list_create();
    ck_assert(l != NULL);
    ck_assert(forward_list_size(l) == 0);
    ck_assert(forward_list_empty(l));
    ck_assert(l->front == NULL);
    ck_assert(forward_list_begin(l) == l->front);

    forward_list_emplace_front(l, &a);
    ck_assert(*(int *)forward_list_front(l) == a);
    ck_assert(forward_list_size(l) == 1);
    ck_assert(!forward_list_empty(l));
    ck_assert(forward_list_begin(l) == l->front);

    forward_list_pop_front(l, standart_destructor);
    ck_assert(forward_list_size(l) == 0);
    ck_assert(forward_list_empty(l));
    ck_assert(forward_list_begin(l) == l->front);

    forward_list_emplace_front(l, &a);
    ck_assert(*(int *)forward_list_front(l)== a);
    ck_assert(forward_list_size(l) == 1);
    ck_assert(!forward_list_empty(l));
    ck_assert(forward_list_begin(l) == l->front);
  
    forward_list_emplace_front(l, &b);
    ck_assert(*(int *)forward_list_front(l) == b);
    ck_assert(forward_list_size(l) == 2);
    ck_assert(!forward_list_empty(l));
    ck_assert(forward_list_begin(l) == l->front);

    forward_list_clear(l, standart_destructor);
    ck_assert(l != NULL);
    ck_assert(forward_list_size(l) == 0);
    ck_assert(forward_list_empty(l));
    ck_assert(l->front == NULL);
    ck_assert(forward_list_begin(l) == l->front);

    int arr[1000] = {0};

    for (int i = 0; i < 1000; i++)
    arr[i] = 0;

    for (int i = 0; i < 1000; i++)
    {
      arr[i] = i;
      forward_list_emplace_front (l, arr + i);
      ck_assert (!forward_list_empty (l));
      ck_assert (forward_list_size (l) == (size_t)(arr[i] + 1));
      ck_assert_uint_eq (*(int *)forward_list_front (l), i);
      ck_assert_ptr_eq (forward_list_begin (l)->data, (dptr)(arr + i));
      ck_assert (forward_list_end () == NULL);
    }

    for (int i = 999; i > 0; i--)
    {
      forward_list_pop_front (l, standart_destructor);
      ck_assert (!forward_list_empty (l));
      ck_assert (forward_list_size (l) == (size_t)arr[i]);
      ck_assert (*(int *)forward_list_front (l) == arr[i] - 1);
      ck_assert (forward_list_begin (l)->data == (dptr)(arr + i - 1));
      ck_assert (forward_list_end () == NULL);
    }

    forward_list_destroy(l, standart_destructor);
}


START_TEST(forward_list_test_2)
{
  forward_list *l = forward_list_create();
  int arr[1000] = { 0 };

  for (int i = 999; i >= 0; i--)
    {
      arr[i] = i;
      forward_list_emplace_front (l, arr + i);
    }

    forward_list *lcp = forward_list_copy (l, copy_func);

    ck_assert_uint_eq(forward_list_size(l), forward_list_size(lcp));
    for (forward_list_iterator li = forward_list_begin (l), licp = forward_list_begin (lcp);
      li != forward_list_end () && licp != forward_list_end ();
      li = li->next, licp = licp->next)
    ck_assert_int_eq (*(int *)li->data, *(int *)licp->data);

  forward_list_destroy (l, standart_destructor);
  forward_list_destroy (lcp, standart_destructor);
}


START_TEST(forward_list_test_3)
{
  forward_list *l = forward_list_create ();
  int arr[10][50] = { 0 };

  for (int j = 9; j >= 0; j--)
    {
      for (int i = 4; i >= 0; i--)
        {
          arr[j][i] = i;
          forward_list_push_front (l, &arr[j][i]);
        }
    }

  int i;
  for (i = 0; i < 5; i++)
    {
      ck_assert_uint_eq (forward_list_count (l, &i, cmp), 10);
    }

  i = 6;
  ck_assert (forward_list_count (l, &i, cmp) == 0);

  ck_assert (forward_list_count_if (l, predicate1) == 20);
  ck_assert (forward_list_count_if (l, predicate2) == 30);

  forward_list_destroy (l, standart_destructor);
}


START_TEST(forward_list_test_4)
{
  int pattern = 1;
  forward_list *l = forward_list_create ();
  int arr[10] = { 1, 2, 3, 4, 5, 6, 1, 1, 7, 1 };

  for (int i = 9; i >= 0; i--)
    {
      forward_list_push_front (l, arr + i);
    }

  forward_list_remove (l, &pattern, cmp, standart_destructor);

  ck_assert_uint_eq (forward_list_size (l), 6);
  ck_assert_int_eq (*(int *)l->front->data, arr[1]);
  ck_assert_int_eq (*(int *)l->front->next->data, arr[2]);
  ck_assert_int_eq (*(int *)l->front->next->next->data, arr[3]);
  ck_assert_int_eq (*(int *)l->front->next->next->next->data, arr[4]);
  ck_assert_int_eq (*(int *)l->front->next->next->next->next->next->data, arr[8]);
  ck_assert_int_eq (*(int *)l->front->next->next->next->next->data, arr[5]);
  forward_list_clear (l, standart_destructor);

  for (int i = 9; i >= 0; i--)
    {
      forward_list_push_front (l, arr + i);
    }
  pattern = 14;
  forward_list_remove (l, &pattern, cmp, standart_destructor);
  ck_assert (forward_list_size (l) == 10);

  forward_list_destroy (l, standart_destructor);
}


START_TEST(forward_list_test_5)
{
  forward_list *l = forward_list_create ();
  int arr[10] = { 1, 1, 2, 2, 3, 4, 5, 5, 6, 6 };

  for (int i = 9; i >= 0; i--)
    {
      forward_list_push_front (l, arr + i);
    }

  forward_list_remove_if (l, predicate2, standart_destructor);

  ck_assert_uint_eq (forward_list_size (l), 3);
  ck_assert_int_eq (*(int *)l->front->data, arr[2]);
  ck_assert_int_eq (*(int *)l->front->next->data, arr[3]);
  ck_assert_int_eq (*(int *)l->front->next->next->data, arr[4]);
  forward_list_clear (l, standart_destructor);

  for (int i = 9; i >= 0; i--)
    {
      forward_list_push_front (l, arr + i);
    }

  forward_list_remove_if (l, predicate4, standart_destructor);
  ck_assert (forward_list_size (l) == 10);

  forward_list_destroy (l, standart_destructor);  
}


Suite *
suite_forward_list ()
{
  Suite *s;
  TCase *tc;

  s = suite_create ("Forward List test");
  tc = tcase_create ("Forward List test");

  tcase_add_test (tc, forward_list_test_1);
  tcase_add_test (tc, forward_list_test_2);
  tcase_add_test (tc, forward_list_test_3);
  tcase_add_test (tc, forward_list_test_4);
  tcase_add_test (tc, forward_list_test_5);  

  suite_add_tcase (s, tc);

  return s;
}