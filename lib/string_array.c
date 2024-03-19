#include "string_array.h"

/**
 * @brief Private functions.
 *
 */

/**
 * @brief Function to increase capacity
 * of the string to str.size + <size>.
 *
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

  // Increase capacity if need.
  __string_increase_capacity (str, len);

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

  // Increase capacity if need.
  __string_increase_capacity (str, len);

  // Replacing empty space by app string.
  string_replace_subcstr (str, c_str, str->size, 0, len);

  // changing size.
  str->size = len + str->size - 1;

  // adding '\0'
  str->arr[str->size] = '\0';

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

inline __attribute__ ((always_inline)) size_t
string_capacity (const string *str)
{
  return str->capacity;
}

void string_clear (string *str);

int string_compare (const string *str1, const string *str2);

int string_compare_c_str (const string *str, const char *c_str);

int string_compare_substr (const string *str1, size_t offset1, size_t count1,
                           const string *str2, size_t offset2, size_t count2);

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

bool string_ends_with (const string *str, const char *suffix);

string_iterator string_erase_range (string *str, string_iterator first,
                                    string_iterator last);

void string_erase_substr (string *str, size_t offset, size_t count);

size_t string_find (const string *str, char c, size_t offset, size_t count);

size_t string_find_any_of (const string *str, const char *charset,
                           size_t offset, size_t count);

size_t string_find_first_not_of (const string *str, char c, size_t offset,
                                 size_t count);

size_t string_find_any_first_not_of (const string *str, const char *charset,
                                     size_t offset, size_t count);

size_t string_find_first_of (const string *str, char c, size_t offset,
                             size_t count);

size_t string_find_any_first_of (const string *str, const char *charset,
                                 size_t offset, size_t count);

size_t string_find_last_not_of (const string *str, char c, size_t offset,
                                size_t count);

size_t string_find_any_last_not_of (const string *str, const char *charset,
                                    size_t offset, size_t count);

size_t string_find_last_of (const string *str, char c, size_t offset,
                            size_t count);

size_t string_find_any_last_of (const string *str, const char *charset,
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

size_t string_length (const string *str);

void string_push_back (string *str, char c);

void string_pop_back (string *str);

string_iterator string_rbegin (const string *str);

string_iterator string_rend ();

size_t string_replace (string *str, const string *rep, size_t pos,
                       size_t count);

size_t string_replace_c_str (string *str, const char *rep, size_t pos,
                             size_t count);

size_t
string_replace_substr (string *str, const string *rep, size_t pos,
                       size_t offset, size_t count)
{
  if (!str || !rep || pos >= str->size)
    return 0;

  // Calculating how many symbols will be replaced.
  // If not enough space, will be replaced only symbols,
  // that fit into current string.
  size_t res = str->size - pos >= count ? count : str->size - pos;

  for (size_t i = 0; i < res; i++)
    str->arr[i + pos] = rep->arr[i + offset];

  return res;
}
size_t
string_replace_subcstr (string *str, const char *rep, size_t pos,
                        size_t offset, size_t count)
{
  // Conditions to extra return.
  if (!str || !rep || pos >= str->size)
    return 0;

  // Calculating how many symbols will be replaced.
  // If not enough space, will be replaced only symbols,
  // that fit into current string.
  size_t res = str->size - pos >= count ? count : str->size - pos;

  for (size_t i = 0; i < res; i++)
    str->arr[i + pos] = rep[i + offset];

  return res;
}

size_t string_replace_char (string *str, char c, size_t pos, size_t times);

size_t string_replace_iter (string *str, string_iterator iter,
                            string_iterator first, string_iterator last);

size_t string_replace_iter_char (string *str, string_iterator first,
                                 string_iterator last, char c);

void string_reserve (string *str, size_t count);

void string_resize (string *str);

size_t string_rfind (const string *str, char c, size_t offset, size_t count);

size_t string_rfind_any_of (const string *str, const char *charset,
                            size_t offset, size_t count);

size_t string_shrink_to_fit (string *str);

inline size_t
string_size (const string *str)
{
  if (str)
    return str->size;
  return 0;
}

bool string_starts_with (const string *str, const char *suffix);

string *string_substr (const string *str, size_t offset, size_t count);

void
string_destroy (string *str)
{
  if (!str)
    return;

  if (str->arr)
    free (str->arr);

  free (str);
}
