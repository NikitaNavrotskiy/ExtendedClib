#include "test.h"

START_TEST (queue_test_1)
{
  int a = 4, b = 5, c = 6;

  queue *q = queue_create ();
  ck_assert (q != NULL);
  ck_assert (queue_empty (q));
  ck_assert (queue_size (q) == 0);

  queue_push (q, &a);
  ck_assert (queue_size (q) == 1);
  ck_assert (!queue_empty (q));
  ck_assert (*(int *)queue_front (q) == a);
  ck_assert (*(int *)queue_back (q) == a);

  queue_push (q, &b);
  ck_assert (queue_size (q) == 2);
  ck_assert (!queue_empty (q));
  ck_assert (*(int *)queue_front (q) == b);
  ck_assert (*(int *)queue_back (q) == a);

  queue_push (q, &c);
  ck_assert (queue_size (q) == 3);
  ck_assert (!queue_empty (q));
  ck_assert (*(int *)queue_front (q) == c);
  ck_assert (*(int *)queue_back (q) == a);

  queue_pop (q, NULL);
  ck_assert (queue_size (q) == 2);
  ck_assert (!queue_empty (q));
  ck_assert (*(int *)queue_front (q) == c);
  ck_assert (*(int *)queue_back (q) == b);

  queue_pop (q, NULL);
  ck_assert (queue_size (q) == 1);
  ck_assert (!queue_empty (q));
  ck_assert (*(int *)queue_front (q) == c);
  ck_assert (*(int *)queue_back (q) == c);

  queue_pop (q, NULL);
  ck_assert (q != NULL);
  ck_assert (queue_empty (q));
  ck_assert (queue_size (q) == 0);

  queue_destroy (q, NULL);
}

START_TEST (queue_test_2)
{
  char *one = "one", *two = "two", *three = "three", *four = "four",
       *five = "five";

  queue *q = queue_create ();
  ck_assert (q != NULL);
  ck_assert (queue_empty (q));
  ck_assert (queue_size (q) == 0);

  queue_push (q, one);
  ck_assert (queue_size (q) == 1);
  ck_assert (!queue_empty (q));
  ck_assert_str_eq ((char *)queue_front (q), one);
  ck_assert_str_eq ((char *)queue_back (q), one);
  ck_assert ((char *)queue_front (q) == one);
  ck_assert ((char *)queue_back (q) == one);

  queue_push (q, two);
  ck_assert (queue_size (q) == 2);
  ck_assert (!queue_empty (q));
  ck_assert_str_eq ((char *)queue_front (q), two);
  ck_assert_str_eq ((char *)queue_back (q), one);
  ck_assert ((char *)queue_front (q) == two);
  ck_assert ((char *)queue_back (q) == one);

  queue_push (q, three);
  ck_assert (queue_size (q) == 3);
  ck_assert (!queue_empty (q));
  ck_assert_str_eq ((char *)queue_front (q), three);
  ck_assert_str_eq ((char *)queue_back (q), one);
  ck_assert ((char *)queue_front (q) == three);
  ck_assert ((char *)queue_back (q) == one);

  queue_pop (q, NULL);
  ck_assert (queue_size (q) == 2);
  ck_assert (!queue_empty (q));
  ck_assert_str_eq ((char *)queue_front (q), three);
  ck_assert_str_eq ((char *)queue_back (q), two);
  ck_assert ((char *)queue_front (q) == three);
  ck_assert ((char *)queue_back (q) == two);

  queue_pop (q, NULL);
  ck_assert (queue_size (q) == 1);
  ck_assert (!queue_empty (q));
  ck_assert_str_eq ((char *)queue_front (q), three);
  ck_assert_str_eq ((char *)queue_back (q), three);
  ck_assert ((char *)queue_front (q) == three);
  ck_assert ((char *)queue_back (q) == three);

  queue_push (q, four);
  ck_assert (queue_size (q) == 2);
  ck_assert (!queue_empty (q));
  ck_assert_str_eq ((char *)queue_front (q), four);
  ck_assert_str_eq ((char *)queue_back (q), three);
  ck_assert ((char *)queue_front (q) == four);
  ck_assert ((char *)queue_back (q) == three);

  queue_pop (q, NULL);
  ck_assert (queue_size (q) == 1);
  ck_assert (!queue_empty (q));
  ck_assert_str_eq ((char *)queue_front (q), four);
  ck_assert_str_eq ((char *)queue_back (q), four);
  ck_assert ((char *)queue_front (q) == four);
  ck_assert ((char *)queue_back (q) == four);

  queue_pop (q, NULL);
  ck_assert (q != NULL);
  ck_assert (queue_empty (q));
  ck_assert (queue_size (q) == 0);

  queue_push (q, five);
  ck_assert (queue_size (q) == 1);
  ck_assert (!queue_empty (q));
  ck_assert_str_eq ((char *)queue_front (q), five);
  ck_assert_str_eq ((char *)queue_back (q), five);
  ck_assert ((char *)queue_front (q) == five);
  ck_assert ((char *)queue_back (q) == five);

  queue_pop (q, NULL);
  ck_assert (q != NULL);
  ck_assert (queue_empty (q));
  ck_assert (queue_size (q) == 0);

  queue_destroy (q, NULL);
}

START_TEST (queue_test_3)
{
  int i, j;
  queue *q = queue_create ();
  queue *q1 = queue_create ();
  srand (time (NULL));

  for (j = 0; j < 100; j++)
    {
      for (i = 0; i < 10000; i++)
        {
          int r = rand ();
          if (r % 2 == 0 && !queue_empty (q))
            queue_pop (q, NULL);
          else
            queue_push (q, &i);
        }
    }
  while (!queue_empty (q))
    queue_pop (q, NULL);

  queue_destroy (q, NULL);

  i = 0;
  j = 0;
  for (j = 0; j < 100; j++)
    {
      for (i = 0; i < 10000; i++)
        {
          int r = rand ();
          if (r % 2 == 0 && !queue_empty (q1))
            queue_pop (q1, NULL);
          else
            queue_push (q1, &i);
        }
    }

  queue_destroy (q1, NULL);
}

Suite *
suite_queue ()
{
  Suite *s;
  TCase *tc;

  s = suite_create ("Queue test");
  tc = tcase_create ("Queue test");

  tcase_add_test (tc, queue_test_1);
  tcase_add_test (tc, queue_test_2);
  tcase_add_test (tc, queue_test_3);

  suite_add_tcase (s, tc);

  return s;
}