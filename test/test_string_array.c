#include "test.h"
#include <check.h>

START_TEST (string_test_1)
{
  const char *c_str = "somewhat";
  const char *app_c_str = "somewhere";
  const char *app2_c_str = "CANNOT";

  string *str = string_create_c_str (c_str);
  string *str_app = string_create_c_str (app_c_str);

  ck_assert (string_size (str) == strlen (c_str));
  ck_assert (string_capacity (str) == strlen (c_str) + 1);
  for (size_t i = 0; i < strlen (c_str); i++)
    ck_assert (c_str[i] == string_at (str, i));

  string_append (str, str_app);

  ck_assert_str_eq (str->arr, "somewhatsomewhere");
  ck_assert (string_size (str) == 17);

  string_append_c_str (str, app2_c_str);

  ck_assert_str_eq (str->arr, "somewhatsomewhereCANNOT");
  ck_assert_uint_eq (string_size (str), 23);

  string_resize (str, 50);

  ck_assert_str_eq (str->arr, "somewhatsomewhereCANNOT");
  ck_assert_uint_eq (string_size (str), 50);

  string_resize (str, 10);

  ck_assert_str_eq (str->arr, "somewhatso");
  ck_assert_uint_eq (string_size (str), 10);

  string_destroy (str_app);
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
