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

/**
 * @brief Returns const c-style string
 * from str. Should not be freed, only
 * through destructor of string.
 *
 * @param Pointer to string.
 * @return const char * c-style string.
 */
const char *string_c_str (const string *str);

/**
 * @brief Returns current capacity
 * of the string.
 *
 * @param str Pointer to string.
 * @return size_t Capacity.
 */
size_t string_capacity (const string *str);

/**
 * @brief Clearing string, but
 * do not free it.
 *
 * @param str Pointer to the string.
 */
void string_clear (string *str);

/**
 * @brief Compare <str1> and <str2>.
 *
 * @param str1 Pointer to the first string.
 * @param str2 Pointer to the second string.
 * @return int Return
 * (int < 0) if str2 > str1 or str1 is Null,
 * (int > 0) if str2 < str1 or str2 is Null,
 * (int = 0) if str1 = str2.
 */
int string_compare (const string *str1, const string *str2);

/**
 * @brief Compare <str1> and <c_str>.
 *
 * @param str1 Pointer string.
 * @param c_str Pointer to c-style string.
 * @return int Return
 * (int < 0) if c_str > str or str is Null,
 * (int > 0) if c_str < str or c_str is Null,
 * (int = 0) if str = c_str.
 */
int string_compare_c_str (const string *str, const char *c_str);

/**
 * @brief Compare substr of <str1> and
 * substr of <str2>.
 *
 * @param str1 Pointer to the first string.
 * @param offset1 Starting index for comparing
 * for str1.
 * @param str2 Pointer to the second string.
 * @param offset2 Starting index for comparing
 * for str2.
 * @param count Number of symbols for comparing
 * @return int Return
 * (int < 0) if str2 > str1 or str1 is Null,
 * (int > 0) if str2 < str1 or str2 is Null,
 * (int = 0) if str1 = str2.
 */
int string_compare_substr (const string *str1, size_t offset1,
                           const string *str2, size_t offset2, size_t count);

/**
 * @brief Return new instance that
 * copies str.
 *
 * @param str Pointer to string.
 * @return string * New instance of string
 * that copies old string.
 */
string *string_copy (const string *str);

/**
 * @brief Return new instance that
 * copies substring of str.
 *
 * @param str Pointer to string.
 * @return string * New instance of string
 * that copies substring of old string.
 */
string *string_copy_substr (const string *str, size_t offset, size_t count);

/**
 * @brief Returns const c-style string
 * from str. Should not be freed, only
 * through destructor of string.
 *
 * @param Pointer to string.
 * @return const char * c-style string.
 */
const char *string_data (const string *str);

/**
 * @brief Checking that <str> is empty.
 *
 * @param str Pointer to the string.
 * @return bool
 * true if str is empty.
 * false if str is not empty.
 */
bool string_empty (const string *str);

/**
 * @brief Returns iterator to the element after
 * last (to '\0').
 *
 * @param str Pointer to the string.
 * @return string_iterator Iterator to
 * the element after last.
 */
string_iterator string_end (const string *str);

/**
 * @brief Checking if string ends with one
 * of the symbols in suffix.
 *
 * @param str Pointer to the string.
 * @param suffix c-style string with
 * symbols to find.
 * @return bool
 * true If one of the symbols of suffix is ends of
 * string.
 * false otherwise.
 */
bool string_ends_with (const string *str, const char *suffix);

/**
 * @brief Erase symbols from <first> to <last> iterators.
 * Iterators Should be not NULL. first and last included.
 *
 * @param str Pointer to the string.
 * @param first Iterator where erasing starts from.
 * @param last Iterator where erasing finishes.
 * @return string_iterator Iterator to the first element
 * after last deleted.
 */
string_iterator string_erase_range (string *str, string_iterator first,
                                    string_iterator last);

/**
 * @brief Erase <count> symbols from <offset> index.
 *
 * @param str Pointer to the string.
 * @param offset Index of first element to erase.
 * @param count Number of symbols to erase.
 */
void string_erase_substr (string *str, size_t offset, size_t count);

/**
 * @brief Returns index of first found <c> in <str> in
 * range of indexes from <offset> to <offset> + <count> - 1.
 *
 * @param str Pointer to the string.
 * @param c Symbol to find.
 * @param offset First index to find in.
 * @param count Number of symbols to find in.
 * @return Index of first found element or -1 if
 * not found.
 */
ssize_t string_find (const string *str, char c, size_t offset, size_t count);

/**
 * @brief Returns index of first found symbol from
 * <charset> in <str> in range of indexes from <offset>
 * to <offset> + <count> - 1.
 *
 * @param str Pointer to the string.
 * @param charset Symbols to find.
 * @param offset First index to find in.
 * @param count Number of symbols to find in.
 * @return Index of first found element or -1 if
 * not found.
 */
ssize_t string_find_any_of (const string *str, const char *charset,
                            size_t offset, size_t count);

/**
 * @brief Returns index of first element from
 * that not equal to <c> from <str> in
 * range of indexes from <offset>
 * to <offset> + <count> - 1.
 *
 * @param str Pointer to the string.
 * @param c Symbols to find.
 * @param offset First index to find in.
 * @param count Number of symbols to find in.
 * @return Index of first found element or -1 if
 * not found.
 */
ssize_t string_find_first_not_of (const string *str, char c, size_t offset,
                                  size_t count);

/**
 * @brief Returns index of first found symbol not from
 * <charset> in <str> in range of indexes from <offset>
 * to <offset> + <count> - 1.
 *
 * @param str Pointer to the string.
 * @param charset Symbols to find.
 * @param offset First index to find in.
 * @param count Number of symbols to find in.
 * @return Index of first found element or -1 if
 * not found.
 */
ssize_t string_find_any_first_not_of (const string *str, const char *charset,
                                      size_t offset, size_t count);

char string_front (const string *str);

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

string_iterator string_rend (const string *str);

size_t string_replace (string *str, const string *rep, size_t pos,
                       size_t count);

size_t string_replace_c_str (string *str, const char *rep, size_t pos,
                             size_t count);

size_t string_replace_substr (string *str, const string *rep, size_t pos,
                              size_t offset, size_t count);

size_t string_replace_subcstr (string *str, const char *rep, size_t pos,
                               size_t offset, size_t count);

size_t string_replace_char (string *str, char c, size_t pos, size_t times);

size_t string_replace_iter (string *str, string_iterator iter,
                            string_iterator first, string_iterator last);

size_t string_replace_iter_char (string *str, string_iterator first,
                                 string_iterator last, char c);

void string_reserve (string *str, size_t count);

void string_resize (string *str, char c, size_t size);
/**
 * @brief Returns index of last found <c> in <str> in
 * range of indexes from <offset> to <offset> + <count> - 1.
 *
 * @param str Pointer to the string.
 * @param c Symbol to find.
 * @param offset First index to find in.
 * @param count Number of symbols to find in.
 * @return Index of last found element or -1 if
 * not found.
 */
ssize_t string_rfind (const string *str, char c, size_t offset, size_t count);

/**
 * @brief Returns index of last found symbol from
 * <charset> in <str> in range of indexes from <offset>
 * to <offset> + <count> - 1.
 *
 * @param str Pointer to the string.
 * @param charset Symbols to find.
 * @param offset First index to find in.
 * @param count Number of symbols to find in.
 * @return Index of last found element or -1 if
 * not found.
 */
ssize_t string_rfind_any_of (const string *str, const char *charset,
                             size_t offset, size_t count);

/**
 * @brief Returns index of last element from that not equal to <c>
 * from <str> in range of indexes from <offset>
 * to <offset> + <count> - 1.
 *
 * @param str Pointer to the string.
 * @param c Symbols to find.
 * @param offset First index to find in.
 * @param count Number of symbols to find in.
 * @return Index of last found element or -1 if
 * not found.
 */
ssize_t string_rfind_any_first_not_of (const string *str, const char *charset,
                                       size_t offset, size_t count);

/**
 * @brief Removing extra capacity from
 * string.
 *
 * @param str Pointer to the string.
 * @return size_t New capacity.
 */
size_t string_shrink_to_fit (string *str);

/**
 * @brief Return size of the string.
 *
 * @param str Pointer to the string.
 * @return size_t Size of the string.
 */
size_t string_size (const string *str);

/**
 * @brief Checking if string starts with one
 * of the symbols in suffix.
 *
 * @param str Pointer to the string.
 * @param suffix c-style string with
 * symbols to find.
 * @return bool
 * true If one of the symbols of suffix is ends of
 * string.
 * false otherwise.
 */
bool string_starts_with (const string *str, const char *suffix);

/**
 * @brief Creating new instance of string from
 * substring of str. substring is count elements
 * from offset index.
 *
 * @param str Pointer to the string.
 * @param offset Staring element of substring.
 * @param count Number of elements in substring.
 * @return Substing in new string instance.
 */
string *string_substr (const string *str, size_t offset, size_t count);

/**
 * @brief Destructor for string.
 *
 * @param str String to destroy.
 */
void string_destroy (string *str);

#endif
