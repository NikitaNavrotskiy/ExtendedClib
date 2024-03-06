/**
 * @file array.c Implementation of public array's API functions. 
 */

#include "array.h"


array *array_create(size_t size)
{
    array *arr = (array *)malloc(sizeof(array));

    arr->size = size;
    arr->capacity = (size_t)(arr->size * ARRAY_CAPACITY_INCREASE_FACTOR);
    arr->vec = malloc(sizeof(dptr) * arr->capacity);

    return arr;
}

inline dptr array_at(array *arr, size_t pos)
{
    if(pos < arr->size)
        return arr->vec[pos];
    return NULL;
}

inline
dptr array_back(array *arr)
{
    if(arr->size == 0)
        return NULL;
    return arr->vec[arr->size - 1];
}

inline
array_iterator array_begin(array *arr)
{
    if(arr->size == 0)
        return NULL;
    return arr->vec;
}

inline
array_iterator array_rbegin(array *arr)
{
    if(arr->size == 0)
        return NULL;
    return arr->vec + arr->size - 1;    
}

inline __attribute__ ((always_inline))
size_t array_capacity(array *arr)
{
    return arr->capacity;
}

void array_clear(array *arr, void (*destr)(dptr data))
{
    for(size_t i = 0; i < arr->size; i++)
        destr(arr->vec[i]);

    arr->size = 0;
}

array *array_copy (const array *arr, dptr (*cpy) (const dptr data));


size_t array_count (const array *arr, constdptr data,
                   bool (*cmp) (constdptr first, constdptr second));

size_t array_count_if (const array *arr, bool (*predicate) (constdptr data));

inline
dptr array_data(array *arr)
{
    return array_front(arr);
}

void array_destroy(array *arr, void (*destr)(dptr data))
{
    array_clear(arr, destr);
    free(arr->vec);
    free(arr);
}

inline
array_iterator array_emplace(array *arr, array_iterator where, dptr data)
{
    return array_insert(arr, where, data);
}

inline
void array_emplace_back(array *arr, dptr data)
{
    array_push_back(arr, data);
}

bool array_empty(array *arr)
{
    return arr->size == 0;
}

array_iterator array_end()
{
    return NULL;
}

array_iterator array_rend()
{
    return NULL;
}

array_iterator array_erase(array *arr, array_iterator where, void (*destr)(dptr data));

array_iterator array_erase_many(array *arr, array_iterator first, array_iterator last, void (*destr)(dptr data));

dptr array_front(array *arr)
{
    if(arr->size == 0)
        return NULL;
    return arr->vec;
}

array_iterator array_find (const array *arr, constdptr data,
                         bool (*cmp) (constdptr first, constdptr second));

array_iterator array_find_if (const array *arr, bool (*predicate) (constdptr data));

array_iterator array_insert(array *arr, array_iterator where, dptr data);

array_iterator array_insert_many(array *arr, array_iterator where, size_t count, ...);

void array_pop_back(array *arr, dptr data, void (*destr)(dptr data));

void array_push_back(array *arr, dptr data);

void array_reserve(array *arr, size_t count)
{
    arr->capacity = count;
    arr->vec = realloc(arr->vec, sizeof(dptr) * count);
}

void array_shrink_to_fit(array *arr)
{
    arr->vec = realloc(arr->vec, sizeof(dptr) * arr->size);
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

inline __attribute__ ((always_inline))
size_t array_size(array *arr)
{
    return arr->size;
}