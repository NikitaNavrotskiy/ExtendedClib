#include "hashset.h"

////////////////////////////////////////////////////
/*       Private functions of the hashset         */
////////////////////////////////////////////////////

/**
 * @brief Function to calculate index
 * in buckets array by value.
 *
 * @param hs Pointer to hashset instance.
 * @param val element to calculate index.
 * @param valsize Size of element.
 * @return hash32 Index for the element.
 */
inline static hash32
__hashset_index_from_val (const hashset *hs, constdptr val, size_t valsize)
{
  return hash (val, valsize) % hashset_bucket_count (hs);
}

/**
 * @brief Function to get bucket by index.
 *
 * @param hs Pointer to hashset instance.
 * @param index Index to get bucket.
 * @return forward_list* Forward list of bucket.
 */
inline static forward_list *
__hashset_bucket_by_index (const hashset *hs, hash32 index)
{
  return array_at (hs->buckets, index);
}

/**
 * @brief Function to get value.
 *
 * @param hs Pointer to hashmap instance.
 * @param val Val to get.
 * @param valsize Size of val.
 * @return dptr Val or NULL.
 */
dptr
__hashmap_get_value (const hashset *hs, constdptr val, size_t valsize)
{
  // Calculating index of bucket by hash.
  hash32 index = __hashset_index_from_val (hs, val, valsize);

  // Getting appropriate bucket.
  forward_list *bucket = __hashset_bucket_by_index (hs, index);

  // Finding pair.
  forward_list_iterator value = forward_list_find (bucket, val, hs->cmp);

  if (value != forward_list_end ())
    return value->data;

  return NULL;
}

/**
 * @brief Function of resizing array of buckets.
 *
 * @param hs Pointer to hashset instance.
 * @param size New size.
 */
static void
__hashset_resize_buckets_array (hashset *hs, size_t size)
{
  // Saving old buckets.
  array *old_buckets = hs->buckets;

  // Creating new buckets.
  hs->buckets = array_create (size);

  // Setting size = 0, because of new insertions.
  hs->size = 0;

  // Creating every bucket.
  for (size_t i = 0; i < size; i++)
    array_push_back (hs->buckets, (dptr *)forward_list_create ());

  // Inserting every element from old buckets to new buckets.
  for (size_t i = 0; i < array_size (old_buckets); i++)
    {
      forward_list_iterator cur
          = forward_list_begin ((forward_list *)array_at (old_buckets, i));

      while (cur)
        {
          hashset_insert (hs, cur->data);
          cur = cur->next;
        }

      forward_list_destroy (array_at (old_buckets, i), hs->destr);
    }

  array_destroy (old_buckets, NULL);
}

////////////////////////////////////////////////////
/*     Public API functions of the hashset        */
////////////////////////////////////////////////////

hashset *
hashset_create (bool (*cmp) (constdptr val1, constdptr val2),
                size_t (*size_func) (constdptr val), void (*destr) (dptr val))
{
  // Allocation memory for the hashset instance.
  hashset *hs = (hashset *)malloc (sizeof (hashset));

  // Creating array of buckets..
  hs->buckets = array_create (HASHSET_STARTING_NUMBER_OF_BUCKETS);

  // Creating buckets (forward lists).
  for (size_t i = 0; i < HASHSET_STARTING_NUMBER_OF_BUCKETS; i++)
    array_push_back (hs->buckets, (dptr *)forward_list_create ());

  hs->size = 0;

  // Setting compare func for vals.
  hs->cmp = cmp;

  // Setting sizeof-func for vals.
  hs->size_func = size_func;

  // Setting destructor provided by user.
  hs->destr = destr;

  return hs;
}

inline size_t
hashset_bucket (const hashset *hs, constdptr val)
{
  return (size_t)__hashset_index_from_val (hs, val, hs->size_func (val));
}

inline size_t
hashset_bucket_count (const hashset *hs)
{
  return array_size (hs->buckets);
}

inline size_t
hashset_bucket_size (const hashset *hs, size_t nbucket)
{
  return forward_list_size (array_at (hs->buckets, nbucket));
}

void
hashset_clear (hashset *hs)
{
  // Calling clear func for every bucket.
  for (size_t i = 0; i < array_size (hs->buckets); i++)
    forward_list_clear (array_at (hs->buckets, i), hs->destr);

  // Setting size = 0
  hs->size = 0;
}

inline bool
hashset_contains (const hashset *hs, constdptr val)
{
  return __hashmap_get_value (hs, val, hs->size_func (val)) != NULL;
}

inline __attribute__ ((always_inline)) bool
hashset_empty (const hashset *hs)
{
  return hs->size == 0;
}

void
hashset_erase (hashset *hs, constdptr val)
{
  // Calculating index of bucket by hash.
  hash32 index = __hashset_index_from_val (hs, val, hs->size_func (val));

  // Getting appropriate bucket.
  forward_list *bucket = __hashset_bucket_by_index (hs, index);

  // Removing element by val.
  forward_list_remove (bucket, (dptr)val, hs->cmp, hs->destr);
  hs->size--;
}

void
hashset_insert (hashset *hs, constdptr val)
{
  // Checking if we need to increase array buckets's size.
  if (hashset_bucket_count (hs) == hs->size)
    __hashset_resize_buckets_array (hs, hs->size
                                            * HASHSET_INCREASE_BUCKETS_FACTOR);

  // Calculating index of bucket by hash.
  hash32 index = __hashset_index_from_val (hs, val, hs->size_func (val));

  // Getting appropriate bucket.
  forward_list *bucket = __hashset_bucket_by_index (hs, index);

  // Checking for existance.
  forward_list_iterator former = forward_list_find (bucket, val, hs->cmp);

  // If not exist => Inserting new pair to the bucket.
  if (former == forward_list_end ())
    {
      forward_list_push_front (bucket, val);
      hs->size++;
    }
}

inline float
hashset_load_factor (const hashset *hs)
{
  return (float)hashset_size (hs) / hashset_bucket_count (hs);
}

void hashmap_rehash (hashset *hs);

inline __attribute__ ((always_inline)) size_t
hashset_size (const hashset *hs)
{
  return hs->size;
}

void
hashset_destroy (hashset *hs)
{
  // Destoying buckets.
  for (size_t i = 0; i < array_size (hs->buckets); i++)
    forward_list_destroy (array_at (hs->buckets, i), hs->destr);

  // Destroying Destroying Array of buckets.
  array_destroy (hs->buckets, NULL);

  // Destroying hashset instance.
  free (hs);
}