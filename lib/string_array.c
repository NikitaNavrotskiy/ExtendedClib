#include "string_array.h"
#include <string.h>

/**
 * @brief Private functions.
 *
 */

/**
 * @brief Function to increase capacity
 * of the string to str.size + <size>.
 * @param str Pointer to the string.
 * @param size How much capacity is needed.
 */
static void
__string_increase_capacity (string *str, size_t size)
{
  if (str->capacity >= str->size + size)
    return;

  size_t new_capacity
      = str->capacity + size * STRING_ARRAY_CAPACITY_INCREASE_FACTOR;

  char *ptr = realloc (str->arr, new_capacity);

  str->capacity = new_capacity;
  str->arr = ptr;
}

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
  if (str->capacity > 0)
    str->arr[0] = '\0';

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
  str->size = len;

  return str;
}

string *
string_create_char (char sym, size_t count)
{
  string *str = string_create_capacity (count + 1);

  for (size_t i = 0; i < count; i++)
    str->arr[i] = sym;

  str->arr[count] = '\0';
  str->size = count;

  return str;
}

string *
string_create_default ()
{
  return string_create_capacity (STRING_ARRAY_CAPACITY_DEFAULT);
}

char
string_at (const string *str, size_t pos)
{
  if (!str || pos >= str->size)
    return '\0';
  return str->arr[pos];
}

string *
string_append (string *str, const string *app)
{
  // If !str => just return empty ptr.
  if (!str)
    return NULL;

  // If !app => just return str.
  if (!app)
    return str;

  size_t len = app->size;

  // Replacing empty space by app string.
  string_replace_substr (str, app, str->size, 0, len);

  return str;
}

string *
string_append_c_str (string *str, const char *c_str)
{
  // If !str => just return empty ptr.
  if (!str)
    return NULL;

  // If !app => just return str.
  if (!c_str)
    return str;

  size_t len = strlen (c_str);

  // Replacing empty space by app string.
  string_replace_subcstr (str, c_str, str->size, 0, len);

  return str;
}

inline char
string_back (const string *str)
{
  if (!str || str->size == 0)
    return '\0';
  return str->arr[str->size - 1];
}

inline string_iterator
string_begin (const string *str)
{
  if (!str || str->size == 0)
    return string_end (str);
  return str->arr;
}

inline const char *
string_c_str (const string *str)
{
  return (const char *)str->arr;
}

inline size_t
string_capacity (const string *str)
{
  if (!str)
    return 0;
  return str->capacity;
}

void
string_clear (string *str)
{
  if (!str)
    return;
  str->size = 0;
}

inline int
string_compare (const string *str1, const string *str2)
{
  if (!str1)
    {
      if (!str2)
        return 0;
      else
        return -1;
    }

  return string_compare_substr (str1, 0, str2, 0, str1->size);
}

inline int
string_compare_c_str (const string *str, const char *c_str)
{
  if (!str)
    {
      if (!c_str)
        return 0;
      else
        return -1;
    }
  if (!c_str)
    return 1;

  size_t len = strlen (c_str);
  size_t cstr_len = len;

  if (str->size < len)
    len = str->size;

  int res = strncmp (str->arr, c_str, len);

  if (res == 0)
    return str->size - cstr_len;
  return res;
}

int
string_compare_substr (const string *str1, size_t offset1, const string *str2,
                       size_t offset2, size_t count)
{
  if (!str1)
    {
      if (!str2)
        return 0;
      else
        return -1;
    }
  if (!str2)
    return 1;

  if (count > str1->size - offset1)
    count = str1->size - offset1;
  if (count > str2->size)
    count = str2->size - offset2;

  int res = strncmp (str1->arr + offset1, str2->arr + offset2, count);

  if (res == 0)
    return str1->size - str2->size;
  return res;
}

inline string *
string_copy (const string *str)
{
  return string_copy_substr (str, 0, str->size);
}

string *
string_copy_substr (const string *str, size_t offset, size_t count)
{
  if (!str)
    return NULL;

  // Out of range.
  if (offset + count > str->size)
    return NULL;

  // Reserving one symbol for '\0'
  string *new_str = string_create_capacity (count + 1);

  for (size_t i = 0; i < count; i++)
    new_str->arr[i] = str->arr[i + offset];

  new_str->size = count;
  new_str->arr[count] = '\0';

  return new_str;
}

const char *
string_data (const string *str)
{
  return (const char *)str->arr;
}

inline __attribute__ ((always_inline)) bool
string_empty (const string *str)
{
  return (!str || str->size == 0);
}

inline string_iterator
string_end (const string *str)
{
  if (str && str->size != 0)
    return str->arr + str->size;
  return NULL;
}

bool
string_ends_with (const string *str, const char *suffix)
{
  if (!str || str->size == 0)
    return false;

  size_t len = strlen (suffix);

  for (size_t i = 0; i < len; i++)
    {
      if (str->arr[str->size - 1] == suffix[i])
        return true;
    }

  return false;
}

string_iterator string_erase_range (string *str, string_iterator first,
                                    string_iterator last);

void string_erase_substr (string *str, size_t offset, size_t count);

ssize_t
string_find (const string *str, char c, size_t offset, size_t count)
{
  if (!str)
    return -1;

  if (offset >= str->size)
    return -1;

  if (offset + count >= str->size)
    count = str->size - offset;

  for (size_t i = 0; i < count; i++)
    {
      if (str->arr[offset + i] == c)
        return offset + i;
    }

  return -1;
}

ssize_t
string_find_any_of (const string *str, const char *charset, size_t offset,
                    size_t count)
{
  if (!str)
    return -1;

  if (offset >= str->size)
    return -1;

  if (offset + count >= str->size)
    count = str->size - offset;

  size_t charset_len = strlen (charset);

  for (size_t i = 0; i < count; i++)
    {
      for (size_t j = 0; j < charset_len; j++)
        {
          if (str->arr[offset + i] == charset[j])
            return offset + i;
        }
    }

  return -1;
}

ssize_t string_find_first_not_of (const string *str, char c, size_t offset,
                                  size_t count);

ssize_t string_find_any_first_not_of (const string *str, const char *charset,
                                      size_t offset, size_t count);

char
string_front (const string *str)
{
  if (str && str->size != 0)
    return str->arr[0];
  return '\0';
}

string_iterator string_insert (string *str, const string *ins, size_t pos);

string_iterator string_insert_c_str (string *str, const char *ins, size_t pos);

string_iterator string_insert_substr (string *str, const string *ins,
                                      size_t pos, size_t offset, size_t count);

string_iterator string_insert_subcstr (string *str, const char *ins,
                                       size_t pos, size_t offset,
                                       size_t count);

string_iterator string_insert_char (string *str, char c, size_t pos,
                                    size_t times);

string_iterator string_insert_iter (string *str, string_iterator iter,
                                    string_iterator first,
                                    string_iterator last);

string_iterator string_insert_iter_char (string *str, string_iterator iter,
                                         char c, size_t count);

inline size_t
string_length (const string *str)
{
  if (!str)
    return 0;
  return str->size;
}

inline void
string_push_back (string *str, char c)
{
  __string_increase_capacity (str, 1);

  str->arr[str->size] = c;
  str->size++;
}

inline void
string_pop_back (string *str)
{
  if (!str || str->size == 0)
    return;

  str->arr[str->size - 1] = '\0';
}

string_iterator
string_rbegin (const string *str)
{
  if (!str || str->size == 0)
    return NULL;
  return str->arr + str->size - 1;
}

inline string_iterator
string_rend (const string *str)
{
  if (!str)
    return NULL;
  return str->arr - 1;
}

inline size_t
string_replace (string *str, const string *rep, size_t pos, size_t count)
{
  return string_replace_substr (str, rep, pos, 0, count);
}

inline size_t
string_replace_c_str (string *str, const char *rep, size_t pos, size_t count)
{
  return string_replace_subcstr (str, rep, pos, 0, count);
}

size_t
string_replace_substr (string *str, const string *rep, size_t pos,
                       size_t offset, size_t count)
{
  if (!str || !rep || pos > str->size)
    return 0;

  // Increase capacity if need.
  if (str->capacity < pos + count + 1)
    __string_increase_capacity (str, pos + count + 1);

  // Replacing symbols.
  for (size_t i = 0; i < count; i++)
    str->arr[i + pos] = rep->arr[i + offset];

  // Setting updated attributes
  str->size = pos + count;
  str->arr[str->size] = '\0';

  return count;
}

size_t
string_replace_subcstr (string *str, const char *rep, size_t pos,
                        size_t offset, size_t count)
{
  // Conditions to extra return.
  if (!str || !rep || pos > str->size)
    return 0;

  // Increase capacity if need.
  if (str->capacity < pos + count + 1)
    __string_increase_capacity (str, pos + count + 1);

  // Replacing symbols.
  for (size_t i = 0; i < count; i++)
    str->arr[i + pos] = rep[i + offset];

  // Setting updated attributes
  str->size = pos + count;
  str->arr[str->size] = '\0';

  return count;
}

size_t
string_replace_char (string *str, char c, size_t pos, size_t times)
{
  if (!str || pos >= str->size)
    return 0;

  __string_increase_capacity (str, pos + times + 1);

  for (size_t i = 0; i < times; i++)
    str->arr[i + pos] = c;

  str->size = pos + times;
  str->arr[str->size] = '\0';

  return times;
}

size_t string_replace_iter (string *str, string_iterator iter,
                            string_iterator first, string_iterator last);

size_t string_replace_iter_char (string *str, string_iterator first,
                                 string_iterator last, char c);

inline void
string_reserve (string *str, size_t count)
{
  __string_increase_capacity (str, str->size + count);
}

void
string_resize (string *str, char c, size_t size)
{
  if (size > str->size)
    {
      __string_increase_capacity (str, size - str->size + 1);
      memset (str->arr + str->size, c, size - str->size);
    }

  str->size = size;
  str->arr[str->size] = '\0';
}

ssize_t
string_rfind (const string *str, char c, size_t offset, size_t count)
{
  if (!str)
    return -1;

  if (offset >= str->size)
    return -1;

  if (offset + count >= str->size)
    count = str->size - offset;

  for (ssize_t i = count - 1; i >= 0; i--)
    {
      if (str->arr[offset + i] == c)
        return offset + i;
    }

  return -1;
}

ssize_t
string_rfind_any_of (const string *str, const char *charset, size_t offset,
                     size_t count)
{
  if (!str)
    return -1;

  if (offset >= str->size)
    return -1;

  if (offset + count >= str->size)
    count = str->size - offset;

  size_t charset_len = strlen (charset);

  for (ssize_t i = count - 1; i >= 0; i--)
    {
      for (size_t j = 0; j < charset_len; j++)
        {
          if (str->arr[offset + i] == charset[j])
            return offset + i;
        }
    }

  return -1;
}

ssize_t string_rfind_first_not_of (const string *str, char c, size_t offset,
                                   size_t count);

ssize_t string_rfind_any_first_not_of (const string *str, const char *charset,
                                       size_t offset, size_t count);

size_t string_shrink_to_fit (string *str);

inline size_t
string_size (const string *str)
{
  if (str)
    return str->size;
  return 0;
}

bool
string_starts_with (const string *str, const char *suffix)
{
  if (!str || str->size == 0)
    return false;

  size_t len = strlen (suffix);

  for (size_t i = 0; i < len; i++)
    {
      if (str->arr[0] == suffix[i])
        return true;
    }

  return false;
}

string *
string_substr (const string *str, size_t offset, size_t count)
{
  if (!str)
    return NULL;

  if (str->size < offset + count)
    count = str->size - offset;

  string *new_str = string_create_capacity (count + 1);
  string_replace_substr (new_str, str, 0, offset, count);

  return new_str;
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
