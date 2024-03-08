#include "array.h"

/**
 * @brief Private functions.
 *
 */

/**
 * @brief Function to increase capacity if
 * capacity == size and new more space.
 *
 * @param arr Pointer to array instance.
 * @param capacity Capacity.
 */
static void
__array_increase_capacity (array *arr, size_t capacity)
{
  dptr *ptr = realloc (arr->vec, sizeof (dptr) * capacity);

  arr->capacity = capacity;
  arr->vec = ptr;
}

/**
 * @brief Function to check capacity and
 * increase if need.
 *
 * @param arr Pointer to array instance.
 */
inline static void
__array_increase_capacity_if_need (array *arr)
{
  if (arr->size == arr->capacity)
    __array_increase_capacity (
        arr, (size_t)(arr->capacity * ARRAY_CAPACITY_INCREASE_FACTOR));
}

/**
 * @brief Function to get to know index
 * of iterator.
 *
 * @param arr Pointer to array instance.
 * @param where Iterator, index to know.
 * @return size_t Index on array, which
 * iterator points.
 */
inline static size_t
__array_count_index_of_iterator (array *arr, array_iterator where)
{
  return (size_t)(where - arr->vec);
}

/**
 * @brief Function to check if iterator from array.
 *
 * @param arr Pointer to array instance.
 * @param where Iterator to check
 * @return true If iterator from array.
 * @return false If iterator not from array.
 */
inline static bool
__array_is_iterator_from_range (array *arr, array_iterator where)
{
  return arr->vec <= where && where < arr->vec + arr->size;
}

/**
 * @brief Public API functions of the array implementation.
 *
 */

array *
array_create (size_t capacity)
{
  // Allocating memory for array instance..
  array *arr = (array *)malloc (sizeof (array));

  // Setting starting values.
  arr->size = 0;
  arr->capacity = (capacity == 0) ? ARRAY_CAPACITY_DEFAULT : capacity;

  // Allocating memory for array.
  arr->vec = (dptr *)malloc (sizeof (dptr) * arr->capacity);

  return arr;
}

inline dptr
array_at (array *arr, size_t pos)
{
  // Checking if arr is not NULL and pos is
  // not out of range.
  if (arr && pos < arr->size)
    return arr->vec[pos];
  return NULL;
}

inline dptr
array_back (array *arr)
{
  // Checking if arr is not NULL and arr is not empty.
  if (!arr || arr->size == 0)
    return NULL;
  return arr->vec[arr->size - 1];
}

inline array_iterator
array_begin (array *arr)
{
  // Checking if arr is not NULL and arr is not empty.
  if (!arr || arr->size == 0)
    return NULL;
  return arr->vec;
}

inline array_iterator
array_rbegin (array *arr)
{
  // Checking if arr is not NULL and arr is not empty.
  if (!arr || arr->size == 0)
    return NULL;
  return arr->vec + arr->size - 1;
}

inline __attribute__ ((always_inline)) size_t
array_capacity (array *arr)
{
  // Checking if arr is NULL.
  if (!arr)
    return 0;
  return arr->capacity;
}

void
array_clear (array *arr, void (*destr) (dptr data))
{
  // Checking if arr is not NULL.
  if (!arr)
    return;

  // Checking if destr is not NULL
  // If not NULL, calling user's destructor
  // for every item in array.
  if (destr)
    {
      for (size_t i = 0; i < arr->size; i++)
        destr (arr->vec[i]);
    }
  arr->size = 0;
}

array *
array_copy (const array *arr, dptr (*cpy) (constdptr data))
{
  // Checking if arr is not NULL.
  if (!arr)
    return NULL;

  // Allocating memory for copy array.
  array *other = (array *)malloc (sizeof (array));

  other->vec = malloc (sizeof (dptr) * arr->capacity);
  other->capacity = arr->capacity;
  other->size = arr->size;

  // Coping all from arr array to other array.
  for (size_t i = 0; i < other->size; i++)
    other->vec[i] = cpy (arr->vec[i]);

  return other;
}

size_t
array_count (const array *arr, constdptr data,
             bool (*cmp) (constdptr first, constdptr second))
{
  // Checking if arr is not NULL.
  if (!arr)
    return 0;

  size_t res = 0;

  // For every item in array
  // Checking for cmp()
  for (size_t i = 0; i < arr->size; i++)
    {
      if (cmp (data, arr->vec[i]))
        res++;
    }

  return res;
}

size_t
array_count_if (const array *arr, bool (*predicate) (constdptr data))
{
  // Checking if arr is not NULL.
  if (!arr)
    return 0;

  size_t res = 0;

  // For every item in array
  // Checking for predicate()
  for (size_t i = 0; i < arr->size; i++)
    {
      if (predicate (arr->vec[i]))
        res++;
    }

  return res;
}

inline dptr
array_data (array *arr)
{
  // Checking if arr is not NULL.
  if (!arr)
    return array_end ();
  return arr->vec;
}

void
array_destroy (array *arr, void (*destr) (dptr data))
{
  // Checking if arr is not NULL.
  if (!arr)
    return;

  array_clear (arr, destr);
  free (arr->vec);
  free (arr);
}

inline array_iterator
array_emplace (array *arr, array_iterator where, dptr data)
{
  return array_insert (arr, where, data);
}

inline void
array_emplace_back (array *arr, dptr data)
{
  // Checking if arr is not NULL.
  if (!arr)
    return;
  array_push_back (arr, data);
}

bool
array_empty (array *arr)
{
  // Checking if arr is not NULL.
  if (!arr)
    return true;
  return arr->size == 0;
}

array_iterator
array_end ()
{
  return NULL;
}

array_iterator
array_rend ()
{
  return NULL;
}

array_iterator
array_erase (array *arr, array_iterator where, void (*destr) (dptr data))
{
  // Checking if arr is not NULL and <where> in not NULL.
  if (!arr || !where)
    return array_end ();

  // Checking for appropriate iterator.
  if (!__array_is_iterator_from_range (arr, where))
    return array_end ();

  // Saving element to delete.
  dptr tmp = *where;

  // Calculating index from iterator.
  size_t index = __array_count_index_of_iterator (arr, where);

  // If destr != NULL, destructing data
  if (destr)
    destr (tmp);

  // If last element, pop him back.
  if (index == arr->size - 1)
    {
      array_pop_back (arr, destr);
      return array_end ();
    }
  // Else moving all from index + 1  << 1
  for (size_t i = index + 1; i < arr->size; i++)
    arr->vec[i - 1] = arr->vec[i];
  arr->size--;

  return arr->vec + index;
}

array_iterator array_erase_many (array *arr, array_iterator first,
                                 array_iterator last,
                                 void (*destr) (dptr data));

dptr
array_front (array *arr)
{
  // Checking if arr is not NULL and
  // array is not empty.
  if (!arr || arr->size == 0)
    return NULL;
  return arr->vec[0];
}

array_iterator
array_find (const array *arr, constdptr data,
            bool (*cmp) (constdptr first, constdptr second))
{
  // Checking if arr is not NULL
  if (!arr)
    return array_end ();

  // For every item in array
  // Checking for cmp()
  for (size_t i = 0; i < arr->size; i++)
    {
      if (cmp (arr->vec[i], data))
        return (arr->vec + i);
    }

  return array_end ();
}

array_iterator
array_find_if (const array *arr, bool (*predicate) (constdptr data))
{
  // Checking if arr is not NULL
  if (!arr)
    return array_end ();

  // For every item in array
  // Checking for predicate()
  for (size_t i = 0; i < arr->size; i++)
    {
      if (predicate (arr->vec[i]))
        return (arr->vec + i);
    }

  return array_end ();
}

array_iterator
array_rfind (const array *arr, constdptr data,
             bool (*cmp) (constdptr first, constdptr second))
{
  // Checking if arr is not NULL
  if (!arr)
    return array_end ();

  // For every item in array
  // Checking for cmp()
  for (size_t i = arr->size - 1; i < arr->size; i--)
    {
      if (cmp (arr->vec[i], data))
        return (arr->vec + i);
    }

  return array_rend ();
}

array_iterator
array_rfind_if (const array *arr, bool (*predicate) (constdptr data))
{
  // Checking if arr is not NULL
  if (!arr)
    return array_end ();

  // For every item in array
  // Checking for predicate()
  for (size_t i = arr->size - 1; i < arr->size; i--)
    {
      if (predicate (arr->vec[i]))
        return (arr->vec + i);
    }

  return array_rend ();
}

array_iterator
array_insert (array *arr, array_iterator where, dptr data)
{
  // Checking if arr is not NULL
  if (!arr)
    return array_end ();

  // Checking if <where> is NULL,
  // Just pushing back <data>
  if (!where)
    {
      array_push_back (arr, data);
      return arr->vec[arr->size - 1];
    }

  // Checking if iterator is not appropriate.
  if (!__array_is_iterator_from_range (arr, where))
    return array_end ();

  // Calculating index
  long index = (long)__array_count_index_of_iterator (arr, where);

  // If need, increasing capacity.
  __array_increase_capacity_if_need (arr);

  // Moving all elems from size - 1 to index >> 1
  for (int i = arr->size - 1; i >= index; i--)
    arr->vec[i + 1] = arr->vec[i];

  arr->vec[index] = data;
  arr->size++;

  return arr->vec + index;
}

array_iterator array_insert_many (array *arr, array_iterator where,
                                  size_t count, ...);

void
array_pop_back (array *arr, void (*destr) (dptr data))
{
  // Checking if arr is not NULL
  if (!arr || array_empty (arr))
    return;
  // Checking if destr is not NULL
  // And calling destr for every item
  if (destr)
    destr (arr->vec[arr->size - 1]);
  arr->size--;
}

void
array_push_back (array *arr, dptr data)
{
  // Checking if arr is not NULL
  if (!arr)
    return;

  __array_increase_capacity_if_need (arr);

  arr->vec[arr->size] = data;
  arr->size++;
}

inline void
array_reserve (array *arr, size_t count)
{
  // Checking if arr is not NULL and appropriate <count>.
  if (!arr || count < arr->size)
    return;

  // Setting new capacity.
  __array_increase_capacity (arr, count);
}

inline void
array_shrink_to_fit (array *arr)
{
  // Checking if arr is not NULL
  if (!arr)
    return;

  // Setting new capacity.
  __array_increase_capacity (arr, arr->size);
}

void array_remove (array *arr, dptr data,
                   bool (*cmp) (constdptr first, constdptr second),
                   void (*destr) (dptr data));

void array_remove_if (array *arr, bool (*predicate) (constdptr data),
                      void (*destr) (dptr data));

void array_reverse (array *arr);

void array_sort (array *arr, int (*cmp) (constdptr first, constdptr second));

void array_unique (array *arr,
                   bool (*predicate) (constdptr first, constdptr second));

inline size_t
array_size (array *arr)
{
  // Checking if arr is not NULL
  if (!arr)
    return 0;
  return arr->size;
}