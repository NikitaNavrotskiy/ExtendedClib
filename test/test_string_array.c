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
  ck_assert (string_back (str) == 't');
  ck_assert (string_front (str) == 's');
  ck_assert (*string_begin (str) == 's');
  ck_assert (*(string_end (str) - 1) == 't');
  string_append (str, str_app);

  ck_assert_str_eq (str->arr, "somewhatsomewhere");
  ck_assert (string_size (str) == 17);
  ck_assert (string_back (str) == 'e');
  ck_assert (string_front (str) == 's');
  ck_assert (*string_begin (str) == 's');
  ck_assert (*(string_end (str) - 1) == 'e');

  string_append_c_str (str, app2_c_str);

  ck_assert_str_eq (string_c_str (str), "somewhatsomewhereCANNOT");
  ck_assert_uint_eq (string_size (str), 23);
  ck_assert (string_back (str) == 'T');
  ck_assert (string_front (str) == 's');
  ck_assert (*string_begin (str) == 's');
  ck_assert (*(string_end (str) - 1) == 'T');

  string_resize (str, ' ', 50);
  ck_assert_str_eq (string_c_str (str),
                    "somewhatsomewhereCANNOT                           ");
  ck_assert_uint_eq (string_size (str), 50);
  ck_assert_int_eq (string_find (str, 'C', 0, str->size), 17);
  ck_assert_int_eq (string_find (str, 'D', 0, str->size), -1);
  ck_assert_int_eq (string_rfind (str, 'C', 0, str->size), 17);
  ck_assert_int_eq (string_rfind (str, 'D', 0, str->size), -1);
  ck_assert_int_eq (string_find (str, 'T', 0, str->size), 22);
  ck_assert_int_eq (string_rfind (str, 'T', 0, str->size), 22);
  ck_assert_int_eq (string_find (str, 'C', 0, 16), -1);
  ck_assert_int_eq (string_find (str, 'D', 0, 100), -1);
  ck_assert_int_eq (string_rfind (str, 'C', 0, 16), -1);
  ck_assert_int_eq (string_rfind (str, 'D', 0, 100), -1);
  ck_assert_int_eq (string_find (str, 'T', 0, 16), -1);
  ck_assert_int_eq (string_rfind (str, 'T', 0, 16), -1);
  ck_assert (string_back (str) == ' ');
  ck_assert (*string_rbegin (str) == ' ');
  ck_assert (string_front (str) == 's');
  ck_assert (*string_begin (str) == 's');
  ck_assert (*(string_end (str) - 1) == ' ');
  string_resize (str, ' ', 10);

  ck_assert_str_eq (string_data (str), "somewhatso");
  ck_assert_uint_eq (string_size (str), 10);
  ck_assert (string_back (str) == 'o');
  ck_assert (string_front (str) == 's');
  ck_assert (*string_begin (str) == 's');
  ck_assert (*(string_end (str) - 1) == 'o');

  string *cpy = string_copy (str);
  ck_assert_str_eq (string_c_str (cpy), "somewhatso");
  ck_assert_uint_eq (string_size (cpy), 10);
  ck_assert (string_back (cpy) == 'o');
  ck_assert (*string_rbegin (cpy) == 'o');
  ck_assert (string_front (cpy) == 's');
  ck_assert (*string_begin (cpy) == 's');
  ck_assert (*(string_end (cpy) - 1) == 'o');
  ck_assert (!string_empty (str));

  string_clear (str);
  ck_assert (str->size == 0);
  ck_assert (string_length (str) == 0);
  ck_assert (string_empty (str));

  string_destroy (cpy);
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

  ck_assert (string_starts_with (str, "c"));
  ck_assert (string_ends_with (str, "c"));
  ck_assert (!string_starts_with (str, "Dhdhrbv"));
  ck_assert (!string_ends_with (str, "Afrghr"));

  string_destroy (str);
}

START_TEST (string_test_3)
{
  string *str = string_create_default ();
  string *str1 = string_create_c_str ("some text");
  ck_assert (str);
  ck_assert (str->size == 0);
  ck_assert (str->capacity == STRING_ARRAY_CAPACITY_DEFAULT);

  string_append_c_str (str, "some text");

  ck_assert (string_compare (str, str1) == 0);
  ck_assert (string_compare_c_str (str, str1->arr) == 0);

  string_append_c_str (str, "a");
  ck_assert (string_compare (str, str1) > 0);
  ck_assert (string_compare (str1, str) < 0);
  ck_assert (string_compare_c_str (str, str1->arr) > 0);
  ck_assert (string_compare_c_str (str1, str->arr) < 0);
  ck_assert (string_compare (str, NULL) > 0);
  ck_assert (string_compare_c_str (str, NULL) > 0);
  ck_assert (string_compare (NULL, NULL) == 0);
  ck_assert (string_compare_c_str (NULL, NULL) == 0);
  ck_assert (string_compare (NULL, str) < 0);
  ck_assert (string_compare_c_str (NULL, str->arr) < 0);
  ck_assert (string_compare_substr (NULL, 0, NULL, 0, 23) == 0);
  ck_assert (string_compare_substr (NULL, 0, str, 0, 12) < 0);

  string_destroy (str1);
  string_destroy (str);
}

START_TEST (string_test_4)
{
  string *str = string_create_c_str ("Something");
  string *substr = string_substr (str, 3, 4);
  ck_assert_str_eq (string_c_str (substr), "ethi");
  string *substr1 = string_substr (str, 0, 3);
  ck_assert_str_eq (string_c_str (substr1), "Som");
  string *substr2 = string_substr (str, 0, str->size + 3);
  ck_assert_str_eq (string_c_str (substr2), "Something");

  ck_assert (string_rend (str) + 1 == str->arr);

  string_reserve (str, 47);
  ck_assert_uint_eq (string_capacity (str), 47);

  string_push_back (str, 'S');
  ck_assert_str_eq (str->arr, "SomethingS");

  string_pop_back (str);
  ck_assert_str_eq (str->arr, "Something");

  string_clear (str);
  ck_assert (str->size == 0);
  ck_assert_str_eq (str->arr, "");

  string_destroy (str);
  string_destroy (substr2);
  string_destroy (substr1);
  string_destroy (substr);
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
  tcase_add_test (tc, string_test_4);

  suite_add_tcase (s, tc);

  return s;
}
