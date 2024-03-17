#include "string_array.h"

/**
 * @brief Private functions.
 *
 */

/**
 * @brief Public API functions of the array implementation.
 *
 */

string *
string_create_capacity (size_t capacity)
{
  string *str = (string *)malloc (sizeof (string));

  str->capacity = capacity;
  str->size = 0;
  str->arr = (char *)malloc (sizeof (char) * str->capacity);

  return str;
}

string *
string_create_c_str (const char *c_str)
{
  if (c_str == NULL)
    return NULL;

  size_t len = strlen (c_str);

  string *str = string_create_capacity (len + 1);

  for (size_t i = 0; i < len; i++)
    str->arr[i] = c_str[i];

  str->arr[len] = '\0';
  str->size = len + 1;

  return str;
}

string *
string_create_char (char sym, size_t count)
{
  string *str = string_create_capacity (count + 1);

  for (size_t i = 0; i < count; i++)
    str->arr[i] = sym;

  str->arr[count] = '\0';
  str->size = count + 1;

  return str;
}

string *
string_create_default ()
{
  return string_create_capacity (STRING_ARRAY_CAPACITY_DEFAULT);
}

void
string_destroy (string *str)
{
  if (!str)
    return;

  if (str->arr)
    free (str->arr);

  free (str);
}