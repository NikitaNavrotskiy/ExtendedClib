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

inline static void
__array_increase_capacity_if_need (array *arr)
{
  if (arr->size == arr->capacity)
    __array_increase_capacity (
        arr, (size_t)(arr->capacity * ARRAY_CAPACITY_INCREASE_FACTOR));
}

inline static size_t
__array_count_index_of_iterator (array *arr, array_iterator where)
{
  return (size_t)(where - arr->vec);
}

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
  array *arr = (array *)malloc (sizeof (array));

  arr->size = 0;
  arr->capacity = (capacity == 0) ? ARRAY_CAPACITY_DEFAULT : capacity;
  arr->vec = (dptr *)malloc (sizeof (dptr) * arr->capacity);

  return arr;
}

inline dptr
array_at (array *arr, size_t pos)
{
  if (arr && pos < arr->size)
    return arr->vec[pos];
  return NULL;
}

inline dptr
array_back (array *arr)
{
  if (!arr || arr->size == 0)
    return NULL;
  return arr->vec[arr->size - 1];
}

inline array_iterator
array_begin (array *arr)
{
  if (!arr || arr->size == 0)
    return NULL;
  return arr->vec;
}

inline array_iterator
array_rbegin (array *arr)
{
  if (!arr || arr->size == 0)
    return NULL;
  return arr->vec + arr->size - 1;
}

inline __attribute__ ((always_inline)) size_t
array_capacity (array *arr)
{
  if (!arr)
    return 0;
  return arr->capacity;
}

void
array_clear (array *arr, void (*destr) (dptr data))
{
  if (!arr)
    return;

  if(destr)
  {
    for (size_t i = 0; i < arr->size; i++)
      destr (arr->vec[i]);
  }
  arr->size = 0;
}

array *
array_copy (const array *arr, dptr (*cpy) (constdptr data))
{
  if (!arr)
    return NULL;

  array *other = (array *)malloc (sizeof (array));

  other->vec = malloc (sizeof (dptr) * arr->capacity);
  other->capacity = arr->capacity;
  other->size = arr->size;

  for (size_t i = 0; i < other->size; i++)
    other->vec[i] = cpy (arr->vec[i]);

  return other;
}

size_t
array_count (const array *arr, constdptr data,
             bool (*cmp) (constdptr first, constdptr second))
{
  if (!arr)
    return 0;

  size_t res = 0;

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
  if (!arr)
    return 0;

  size_t res = 0;

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
  if (!arr)
    return array_end ();
  return arr->vec;
}

void
array_destroy (array *arr, void (*destr) (dptr data))
{
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
  if (!arr)
    return;
  array_push_back (arr, data);
}

bool
array_empty (array *arr)
{
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
  if (!arr || !where)
    return array_end ();

  if (!__array_is_iterator_from_range (arr, where))
    return array_end ();

  dptr tmp = *where;
  size_t index = __array_count_index_of_iterator (arr, where);

  if(destr)
    destr (tmp);

  if (index == arr->size - 1)
    {
      array_pop_back (arr, destr);
      return array_end ();
    }

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
  if (!arr || arr->size == 0)
    return NULL;
  return arr->vec[0];
}

array_iterator
array_find (const array *arr, constdptr data,
            bool (*cmp) (constdptr first, constdptr second))
{
  if (!arr)
    return array_end ();

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
  if (!arr)
    return array_end ();

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
  if (!arr)
    return array_end ();

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
  if (!arr)
    return array_end ();

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
  if (!arr)
    return array_end ();

  if (!where)
    {
      array_push_back (arr, data);
      return arr->vec[arr->size - 1];
    }

  if (!__array_is_iterator_from_range (arr, where))
    return array_end ();

  long index = (long)__array_count_index_of_iterator (arr, where);

  __array_increase_capacity_if_need (arr);

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
  if (!arr || array_empty (arr))
    return;
  if(destr)
    destr (arr->vec[arr->size - 1]);
  arr->size--;
}

void
array_push_back (array *arr, dptr data)
{
  if (!arr)
    return;

  __array_increase_capacity_if_need (arr);

  arr->vec[arr->size] = data;
  arr->size++;
}

inline void
array_reserve (array *arr, size_t count)
{
  if (!arr || count < arr->size)
    return;
  __array_increase_capacity (arr, count);
}

inline void
array_shrink_to_fit (array *arr)
{
  if (!arr)
    return;
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

inline __attribute__ ((always_inline)) size_t
array_size (array *arr)
{
  if (!arr)
    return 0;
  return arr->size;
}