/**
 * @file array.h Implementation of Dynamic array data structure
 */

#ifndef _EXTENDED_C_LIB_LIB_ARRAY_H
#define _EXTENDED_C_LIB_LIB_ARRAY_H

#include <stdarg.h>
#include <stdbool.h> // bool
#include <stddef.h>  // size_t
#include <stdlib.h>  // malloc, realloc, free

#include "types.h"

#define ARRAY_CAPACITY_INCREASE_FACTOR 2
#define ARRAY_CAPACITY_DEFAULT 10

/**
 * @struct array
 * @brief Implementation of array.
 * 
 */
typedef struct array
{
  /**
   * @brief Dynamic array for dptr datas.
   */
  dptr *vec;

  /**
   * @brief Current size of array.
   */
  size_t size;

  /**
   * @brief Current capacity of array.
   */
  size_t capacity;
} array;

/**
 * @brief Alias array_iterator
 */
typedef dptr *array_iterator;

////////////////////////////////////////////////////
/*       Public API functions of the array        */
////////////////////////////////////////////////////

/**
 * @brief Function to create new Array.
 * Allocates the memory. Should be
 * destroyed at the end.
 *
 * @param capacity Starting capacity for the array.
 * @return array* Pointer to new array.
 */
array *array_create (size_t capacity);

/**
 * @brief Returns element at the <pos>
 * position, or NULL if out of range.
 *
 * @param arr Pointer to array instance.
 * @param pos Position in array
 * @return dptr Element at the <pos>
 * position.
 */
dptr array_at (array *arr, size_t pos);

/**
 * @brief Returns last element.
 *
 * @param arr Pointer to array instance.
 * @return dptr Last element.
 */
dptr array_back (array *arr);

/**
 * @brief array_iterator to the first element.
 *
 * @param arr Pointer to array instance.
 * @return array_iterator to the first element.
 */
array_iterator array_begin (array *arr);

/**
 * @brief array_iterator to the first element
 * in reverse order.
 *
 * @param arr Pointer to array instance.
 * @return array_iterator to the first element
 * in reverse order.
 */
array_iterator array_rbegin (array *arr);

/**
 * @brief Get array's capacity.
 *
 * @param arr Pointer to array instance.
 * @return size_t Array's capacity.
 */
size_t array_capacity (array *arr);

/**
 * @brief Clear array, but do not free
 * array instance.
 *
 * @param arr Pointer to array instance.
 * @param destr Destructor for datas.
 */
void array_clear (array *arr, void (*destr) (dptr data));

/**
 * @brief Function to copy array.
 * Don't make deep copy, if dptr is the
 * pointer to the another pointer,
 * another pointer will be shared.
 *
 * @param arr Pointer to array instance.
 * @param cpy Funtion that copying data.
 * @return Pointer to the new array.
 */
array *array_copy (const array *arr, dptr (*cpy) (constdptr data));

/**
 * @brief Function to count <data> occurences.
 *
 * @param arr Pointer to array instance.
 * @param data Element to count.
 * @param cmp Function that return
 * true if <data> = element
 * false otherwise.
 * @return size_t Number of occurences.
 */
size_t array_count (const array *arr, constdptr data,
                    bool (*cmp) (constdptr first, constdptr second));

/**
 * @brief Function to count all occurences, that
 * is true for <predicate>.
 *
 * @param arr Pointer to array instance.
 * @param predicate Function that return
 * true if element should be counted and
 * false otherwise.
 * @return size_t Number of occurences.
 */
size_t array_count_if (const array *arr, bool (*predicate) (constdptr data));

/**
 * @brief Returns pointer to the start of
 * raw array.
 *
 * @param arr Pointer to array instance.
 * @return dptr Pointer to raw array.
 */
dptr array_data (array *arr);

/**
 * @brief Destructor for array.
 *
 * @param arr Pointer to array instance.
 * @param destr Destru tor for datas.
 */
void array_destroy (array *arr, void (*destr) (dptr data));

/**
 * @brief Inserting <data> in where position.
 *
 * @param arr Pointer to array instance.
 * @param where Position to insert.
 * @param data Element to insert.
 * @return array_iterator Iterator to
 * inserted element.
 */
array_iterator array_emplace (array *arr, array_iterator where, dptr data);

/**
 * @brief Inserting <data> into the last position.
 *
 * @param arr Pointer to array instance.
 * @param data Element to insert.
 * @return array_iterator Iterator to
 * inserted element.
 */
void array_emplace_back (array *arr, dptr data);

/**
 * @brief checks if array is empty.
 *
 * @param arr Pointer to array instance.
 * @return true if array is empty.
 * @return false if array is not empty.
 */
bool array_empty (array *arr);

/**
 * @brief NULL iterator.
 *
 * @return array_iterator NULL.
 */
array_iterator array_end ();

/**
 * @brief NULL iterator.
 *
 * @return array_iterator NULL.
 */
array_iterator array_rend ();

/**
 * @brief Erasing <where> element.
 * <where> have to not be NULL.
 *
 * @param arr Pointer to array instance.
 * @param where Iterator on element to erase.
 * @param destr Desturctor for data.
 * @return array_iterator Next element after
 * erased.
 */
array_iterator array_erase (array *arr, array_iterator where,
                            void (*destr) (dptr data));

/**
 * @brief Erasing elements from <first> to <last>
 * elements (ALL INCLUDED). <first> and <last>
 * have to not be NULL.
 *
 * @param arr Pointer to array instance.
 * @param first First element to erase.
 * @param last Last element to erase.
 * @param destr Desturctor for data.
 * @return array_iterator
 */
array_iterator array_erase_many (array *arr, array_iterator first,
                                 array_iterator last,
                                 void (*destr) (dptr data));

/**
 * @brief Function to find first occurence
 * of <data>.
 *
 * @param arr Pointer to array instance.
 * @param data Element to find.
 * @param cmp Function that return
 * true if <data> = element
 * false otherwise.
 * @return array_iterator to the first occurence
 * or NULL if element hasn't found.
 */
array_iterator array_find (const array *arr, constdptr data,
                           bool (*cmp) (constdptr first, constdptr second));

/**
 * @brief Function to find first occurences, that
 * is true for <predicate>.
 *
 * @param arr Pointer to array instance.
 * @param predicate Function that return
 * true if element is equal and should be
 * found and false otherwise.
 * @return array_iterator to the first occurence
 * or NULL if element hasn't found.
 */
array_iterator array_find_if (const array *arr,
                              bool (*predicate) (constdptr data));

/**
 * @brief Function to find first occurence
 * of <data> in reverse array.
 *
 * @param arr Pointer to array instance.
 * @param data Element to find.
 * @param cmp Function that return
 * true if <data> = element
 * false otherwise.
 * @return array_iterator to the first occurence
 * or NULL if element hasn't found.
 */
array_iterator array_rfind (const array *arr, constdptr data,
                            bool (*cmp) (constdptr first, constdptr second));

/**
 * @brief Function to find first occurences, that
 * is true for <predicate> in reverse array.
 *
 * @param arr Pointer to array instance.
 * @param predicate Function that return
 * true if element is equal and should be
 * found and false otherwise.
 * @return array_iterator to the first occurence
 * or NULL if element hasn't found.
 */
array_iterator array_rfind_if (const array *arr,
                               bool (*predicate) (constdptr data));

/**
 * @brief Returns first element of the
 * array.
 *
 * @param arr Pointer to array instance.
 * @return dptr First element.
 */
dptr array_front (array *arr);

/**
 * @brief Inserting element <data> into <where> position.
 * If <where> == NULL, insert to the end.
 *
 * @param arr Pointer to array instance.
 * @param where Place to insert element.
 * @param data Element to insert.
 * @return array_iterator Iterator to inserted element.
 */
array_iterator array_insert (array *arr, array_iterator where, dptr data);

/**
 * @brief Inserting <count> elements, listed in
 * ... params into the <where> position.
 *
 * @param arr Pointer to array instance.
 * @param where Place to insert elements.
 * @param count Number of elements.
 * @param ... Elements to insert.
 * @return array_iterator Iterator to first inserted
 * element.
 */
array_iterator array_insert_many (array *arr, array_iterator where,
                                  size_t count, ...);

/**
 * @brief Function to insert data into the
 * begin.
 * @param arr Pointer to array instance.
 * @param destr Desturctor for data.
 */
void array_pop_back (array *arr, void (*destr) (dptr data));

/**
 * @brief Function to insert data into the
 * end.
 * @param arr Pointer to array instance.
 * @param data Element to insert.
 */
void array_push_back (array *arr, dptr data);

/**
 * @brief Reserves capacity. If count <
 * current size, capacity will be shrinked to
 * fit.
 * @param arr Pointer to array instance.
 * @param count
 */
void array_reserve (array *arr, size_t count);

/**
 * @brief Function to remove all occurences of
 * <data>
 *
 * @param arr Pointer to array instance.
 * @param data Element to remove.
 * @param cmp Function that return
 * true if <data> = element
 * false otherwise.
 * @param destr Pointer to function, to
 * free memory of datas correctly.
 */
void array_remove (array *arr, dptr data,
                   bool (*cmp) (constdptr first, constdptr second),
                   void (*destr) (dptr data));

/**
 * @brief Function to remove all occurences, that
 * is true for <predicate>.
 *
 * @param arr Pointer to array instance.
 * @param destr Pointer to function, to
 * free memory of datas correctly.
 * @param predicate Function that return
 * true if element should be removed and
 * false otherwise.
 */
void array_remove_if (array *arr, bool (*predicate) (constdptr data),
                      void (*destr) (dptr data));

/**
 * @brief Function to reverce elements in
 * the array.
 *
 * @param arr Pointer to array instance.
 */
void array_reverse (array *arr);

/**
 * @brief Function to sort the array.
 *
 * @param arr Pointer to array instance.
 * @param cmp Function of comparing
 * two elements for sorting.
 * return int < 0 if first < second
 * return int > 0 if first > second
 * return int = 0 if first = second.
 */
void array_sort (array *arr, int (*cmp) (constdptr first, constdptr second));

/**
 * @brief Reduce capacity to <size> size.
 *
 * @param arr Pointer to array instance.
 */
void array_shrink_to_fit (array *arr);

/**
 * @brief Returns size of array.
 *
 * @param arr Pointer to array instance.
 * @return size_t Size of array.
 */
size_t array_size (array *arr);

/**
 * @brief Function to unique array,
 * by removing extra elements.
 *
 * @param arr Pointer to array instance.
 * @param predicate Function of
 * comparing for unique.
 * return true if first = second.
 * return fasle if first != second.
 */
void array_unique (array *arr,
                   bool (*predicate) (constdptr first, constdptr second));

#endif