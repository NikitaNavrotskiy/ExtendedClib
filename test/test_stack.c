#include "test.h"

START_TEST (stack_test_1)
{
  int a = 4, b = 5, c = 6;

  stack *s = stack_create ();
  ck_assert (s != NULL);
  ck_assert (stack_empty (s));
  ck_assert (stack_size (s) == 0);

  stack_push (s, &a);
  ck_assert (!stack_empty (s));
  ck_assert (stack_size (s) == 1);
  ck_assert_int_eq (*(int *)stack_top (s), a);

  stack_push (s, &b);
  ck_assert (!stack_empty (s));
  ck_assert (stack_size (s) == 2);
  ck_assert (*(int *)stack_top (s) == b);

  stack_push (s, &c);
  ck_assert (!stack_empty (s));
  ck_assert (stack_size (s) == 3);
  ck_assert (*(int *)stack_top (s) == c);

  stack_pop (s);
  ck_assert (!stack_empty (s));
  ck_assert (stack_size (s) == 2);
  ck_assert (*(int *)stack_top (s) == b);

  stack_pop (s);
  ck_assert (!stack_empty (s));
  ck_assert (stack_size (s) == 1);
  ck_assert (*(int *)stack_top (s) == a);

  stack_pop (s);
  ck_assert (stack_empty (s));
  ck_assert (stack_size (s) == 0);

  stack_destroy (s);
}

START_TEST (stack_test_2)
{
  char *one = "one", *two = "two", *three = "three", *four = "four",
       *five = "five";

  stack *s = stack_create ();
  ck_assert (s != NULL);
  ck_assert (stack_empty (s));
  ck_assert (stack_size (s) == 0);

  stack_push (s, one);
  ck_assert (stack_size (s) == 1);
  ck_assert (!stack_empty (s));
  ck_assert_str_eq ((char *)stack_top (s), one);
  ck_assert ((char *)stack_top (s) == one);

  stack_push (s, two);
  ck_assert (stack_size (s) == 2);
  ck_assert (!stack_empty (s));
  ck_assert_str_eq ((char *)stack_top (s), two);
  ck_assert ((char *)stack_top (s) == two);

  stack_push (s, three);
  ck_assert (stack_size (s) == 3);
  ck_assert (!stack_empty (s));
  ck_assert_str_eq ((char *)stack_top (s), three);
  ck_assert ((char *)stack_top (s) == three);

  stack_pop (s);
  ck_assert (stack_size (s) == 2);
  ck_assert (!stack_empty (s));
  ck_assert_str_eq ((char *)stack_top (s), two);
  ck_assert ((char *)stack_top (s) == two);

  stack_pop (s);
  ck_assert (stack_size (s) == 1);
  ck_assert (!stack_empty (s));
  ck_assert_str_eq ((char *)stack_top (s), one);
  ck_assert ((char *)stack_top (s) == one);

  stack_push (s, four);
  ck_assert (stack_size (s) == 2);
  ck_assert (!stack_empty (s));
  ck_assert_str_eq ((char *)stack_top (s), four);
  ck_assert ((char *)stack_top (s) == four);

  stack_pop (s);
  ck_assert (stack_size (s) == 1);
  ck_assert (!stack_empty (s));
  ck_assert_str_eq ((char *)stack_top (s), one);
  ck_assert ((char *)stack_top (s) == one);

  stack_pop (s);
  ck_assert (s != NULL);
  ck_assert (stack_empty (s));
  ck_assert (stack_size (s) == 0);

  stack_push (s, five);
  ck_assert (stack_size (s) == 1);
  ck_assert (!stack_empty (s));
  ck_assert_str_eq ((char *)stack_top (s), five);
  ck_assert ((char *)stack_top (s) == five);

  stack_pop (s);
  ck_assert (s != NULL);
  ck_assert (stack_empty (s));
  ck_assert (stack_size (s) == 0);

  stack_destroy (s);
}

START_TEST (stack_test_3)
{
  int i, j;
  stack *s = stack_create ();
  stack *s1 = stack_create ();
  srand (time (NULL));

  for (j = 0; j < 100; j++)
    {
      for (i = 0; i < 10000; i++)
        {
          int r = rand ();
          if (r % 2 == 0 && !stack_empty (s))
            stack_pop (s);
          else
            stack_push (s, &i);
        }
    }
  while (!stack_empty (s))
    stack_pop (s);

  stack_destroy (s);

  i = 0;
  j = 0;
  for (j = 0; j < 100; j++)
    {
      for (i = 0; i < 10000; i++)
        {
          int r = rand ();
          if (r % 2 == 0 && !stack_empty (s1))
            stack_pop (s1);
          else
            stack_push (s1, &i);
        }
    }

  stack_destroy (s1);
}

Suite *
suite_stack ()
{
  Suite *s;
  TCase *tc;

  s = suite_create ("Stack test");
  tc = tcase_create ("Stack test");

  tcase_add_test (tc, stack_test_1);
  tcase_add_test (tc, stack_test_2);
  tcase_add_test (tc, stack_test_3);

  suite_add_tcase (s, tc);

  return s;
}