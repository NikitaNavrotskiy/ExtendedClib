#include "test.h"
#include <check.h>

START_TEST (string_test_1)
{
  const char *c_str = "somewhat";

  string *str = string_create_c_str (c_str);
  ck_assert (string_size (str) == strlen (c_str));
  ck_assert (string_capacity (str) == strlen (c_str) + 1);
  for (size_t i = 0; i < strlen (c_str); i++)
    ck_assert (c_str[i] == string_at (str, i));

  string_destroy (str);
}

START_TEST (string_test_2)
{
  size_t n = 15;
  char ch = 'c';

  string *str = string_create_char (ch, n);
  ck_assert (str->size == n);
  ck_assert (str->capacity == n + 1);

  for (size_t i = 0; i < n; i++)
    ck_assert (string_at (str, i) == ch);

  string_destroy (str);
}

START_TEST (string_test_3)
{
  string *str = string_create_default ();
  ck_assert (str);
  ck_assert (str->size == 0);
  ck_assert (str->capacity == STRING_ARRAY_CAPACITY_DEFAULT);

  string_destroy (str);
}

Suite *
suite_string_array ()
{
  Suite *s;
  TCase *tc;

  s = suite_create ("String test");
  tc = tcase_create ("String test");

  tcase_add_test (tc, string_test_1);
  tcase_add_test (tc, string_test_2);
  tcase_add_test (tc, string_test_3);

  suite_add_tcase (s, tc);

  return s;
}
