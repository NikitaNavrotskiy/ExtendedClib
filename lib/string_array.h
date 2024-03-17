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
 * @brief Destructor for string.
 *
 * @param str String to destroy.
 */
void string_destroy (string *str);

#endif