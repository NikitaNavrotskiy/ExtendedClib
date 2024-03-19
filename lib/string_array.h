/**
 * @file string_array.h Implementation of Dynamic string array data structure
 */

#ifndef _EXTENDED_C_LIB_LIB_STRING_ARRAY_H
#define _EXTENDED_C_LIB_LIB_STRING_ARRAY_H

#include <stdarg.h>
#include <stdbool.h> // bool
#include <stddef.h>  // size_t
#include <stdlib.h>  // malloc, realloc, free
#include <string.h>  // string functions with char *arrays.

#include "types.h"

#define STRING_ARRAY_CAPACITY_INCREASE_FACTOR 2
#define STRING_ARRAY_CAPACITY_DEFAULT 10

/**
 *@brief Implementation of Dynamic string.
 *@struct string
 *
 */
typedef struct string
{
  /**
   * @brief Dynamic char *array.
   */
  char *arr;

  /**
   * @brief Current size of string.
   */
  size_t size;

  /**
   * @brief Current capacity of string.
   */
  size_t capacity;
} string;

/**
 * Alias string_iterator.
 */
typedef char *string_iterator;

////////////////////////////////////////////////////
/*   Public API functions of the string array     */
////////////////////////////////////////////////////

////////////////////////////////////////////////////
/*             Bunch of constructors.             */
////////////////////////////////////////////////////

/**
 * @brief Constructor. Creates new string
 * with <capactiy> capacity.
 * Allocates the memory. Should be
 * destroyed at the end.
 *
 * @param capacity Starting capacity for the string.
 * @return string* Pointer to new string.
 */
string *string_create_capacity (size_t capacity);

/**
 * @brief Constructor. Creates new string
 * from c_str (char * array).
 * Allocates the memory. Should be
 * destroyed at the end.
 *
 * @param c_str Null terminated char array.
 * @return string* Pointer to new string.
 */
string *string_create_c_str (const char *c_str);

/**
 * @brief Constructor. Creates new string
 * with <count> times <sym>.
 * Allocates the memory. Should be
 * destroyed at the end.
 *
 * @param sym Sym in new string.
 * @param count Number of <sym> in new string.
 * @return string* Pointer to new string.
 */
string *string_create_char (char sym, size_t count);

/**
 * @brief Constructor. Creates new string
 * with default params.
 * @return string* Pointer to new string.
 */
string *string_create_default ();

////////////////////////////////////////////////////
/*         End of Bunch of constructors.          */
////////////////////////////////////////////////////

/**
 * @brief Returns symbol at
 * <pos> position. If index out
 * of range => returns '\0'
 *
 * @param str Pointer to string.
 * @param pos Position of symbol.
 * @return char Symbol at <pos>
 * position.
 */
char string_at (const string *str, size_t pos);

/**
 * @brief Appends string and returns str's self.
 *
 * @param str Pointer to string.
 * @param app Pointer to string to append.
 * @return string * The same instance of string.
 */
string *string_append (string *str, const string *app);

/**
 * @brief Appends c-string and returns str's self.
 *
 * @param str Pointer to string.
 * @param c_str Pointer to c_str to append.
 * @return string * The same instance of string.
 */
string *string_append_c_str (string *str, const char *c_str);

/**
 * @brief Returns last symbol of
 * the string. If string is empty,
 * returns '\0'.
 *
 * @param str Pointer to string.
 * @return char Last symbol of the
 * string.
 */
char string_back (const string *str);

/**
 * @brief Returns Iterator to the
 * first symbol of string.
 *
 * @param str Pointer to string.
 * @return string_iterator Iterator
 * to the first symbol.
 */
string_iterator string_begin (const string *str);

char *string_c_str (const string *str);

size_t string_capacity (const string *str);

void string_clear (string *str);

int string_compare (const string *str1, const string *str2);

int string_compare_c_str (const string *str, const char *c_str);

int string_compare_substr (const string *str1, size_t offset1, size_t count1,
                           const string *str2, size_t offset2, size_t count2);

string string_copy (const string *str);

string string_copy_substr (const string *str, size_t offset, size_t count);

char *string_data (const string *str);

bool string_empty (const string *str);

string_iterator string_end ();

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

char string_front (const string *str);

string_iterator string_insert (string *str, const string *ins, size_t pos);

string_iterator string_insert_c_str (string *str, const char *ins, size_t pos);

string_iterator string_insert_substr (string *str, const string *ins,
                                      size_t pos, size_t offset, size_t count);

string_iterator string_insert_sub_c_str (string *str, const char *ins,
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

size_t string_replace_substr (string *str, const string *rep, size_t pos,
                              size_t offset, size_t count);

size_t string_replace_sub_c_str (string *str, const char *rep, size_t pos,
                                 size_t offset, size_t count);

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

size_t string_size (const string *str);

bool string_starts_with (const string *str, const char *suffix);

string *string_substr (const string *str, size_t offset, size_t count);

/**
 * @brief Destructor for string.
 *
 * @param str String to destroy.
 */
void string_destroy (string *str);

#endif
