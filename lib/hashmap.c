#include "hashmap.h"

////////////////////////////////////////////////////
/*       Private functions of the hashmap         */
////////////////////////////////////////////////////

/**
 * @brief Function to calculate index
 * in buckets array by key.
 *
 * @param hm Pointer to hashmap instance.
 * @param key Key to calculate index.
 * @param keysize Size of key.
 * @return hash32 Index for the key.
 */
inline static hash32
__hashmap_index_from_key (const hashmap *hm, constdptr key, size_t keysize)
{
  return hash (key, keysize) % hashmap_bucket_count (hm);
}

/**
 * @brief Function to get bucket by index.
 *
 * @param hm Pointer to hashmap instance.
 * @param index Index to get bucket.
 * @return forward_list* Forward list of bucket.
 */
inline static forward_list *
__hashmap_bucket_by_index (const hashmap *hm, hash32 index)
{
  return array_at (hm->buckets, index);
}

/**
 * @brief Function to get pair of elements
 * by key.
 *
 * @param hm Pointer to hashmap instance.
 * @param key Key to calculate index.
 * @param keysize Size of key.
 * @return struct pair* Pair of elements.
 */
static struct pair *
__hashmap_pair_by_key (const hashmap *hm, constdptr key, size_t keysize)
{
  // Calculating index of bucket by hash.
  hash32 index = __hashmap_index_from_key (hm, key, keysize);

  // Getting appropriate bucket.
  forward_list *bucket = __hashmap_bucket_by_index (hm, index);

  struct pair pattern = { (dptr)key, NULL };
  // Finding pair.
  forward_list_iterator pair = forward_list_find (bucket, &pattern, hm->cmp);

  if (pair != forward_list_end ())
    return (struct pair *)(pair->data);

  return NULL;
}

/**
 * @brief Function of resizing array of buckets.
 *
 * @param hm Pointer to hashmap instance.
 * @param size New size.
 */
static void
__hashmap_resize_buckets_array (hashmap *hm, size_t size)
{
  // Saving old buckets.
  array *old_buckets = hm->buckets;

  // Creating new buckets.
  hm->buckets = array_create (size);

  // Setting size = 0, because of new insertions.
  hm->size = 0;

  // Creating every bucket.
  for (size_t i = 0; i < size; i++)
    array_push_back (hm->buckets, (dptr *)forward_list_create ());

  // Inserting every element from old buckets to new buckets.
  for (size_t i = 0; i < array_size (old_buckets); i++)
    {
      forward_list_iterator cur
          = forward_list_begin ((forward_list *)array_at (old_buckets, i));

      while (cur)
        {
          struct pair *cur_pair = (struct pair *)(cur->data);
          hashmap_insert (hm, cur_pair->key, cur_pair->value);
          cur = cur->next;
        }

      forward_list_destroy (array_at (old_buckets, i), hm->destr);
    }

  array_destroy (old_buckets, NULL);
}

////////////////////////////////////////////////////
/*     Public API functions of the hashset        */
////////////////////////////////////////////////////

hashmap *
hashmap_create (bool (*cmp) (constdptr pair1, constdptr pair2),
                size_t (*size_func) (constdptr key), void (*destr) (dptr pair))
{
  // Allocation memory for the hashmap instance.
  hashmap *hm = (hashmap *)malloc (sizeof (hashmap));

  // Creating array of buckets..
  hm->buckets = array_create (HASHMAP_STARTING_NUMBER_OF_BUCKETS);

  // Creating buckets (forward lists).
  for (size_t i = 0; i < HASHMAP_STARTING_NUMBER_OF_BUCKETS; i++)
    array_push_back (hm->buckets, (dptr *)forward_list_create ());

  hm->size = 0;

  // Setting compare func for keys.
  hm->cmp = cmp;

  // Setting sizeof-func for keys.
  hm->size_func = size_func;

  // Setting destructor for the pair, provided by user.
  if (destr)
    hm->destr = destr;
  else
    hm->destr = pair_destroy_default;

  return hm;
}

dptr
hashmap_at (const hashmap *hm, constdptr key)
{
  // Getting pair by key.
  struct pair *pair = __hashmap_pair_by_key (hm, key, hm->size_func (key));

  // If pair exist, returning its value.
  if (pair)
    return pair->value;

  // Else returning NULL.
  return NULL;
}

inline size_t
hashmap_bucket (const hashmap *hm, constdptr key)
{
  return (size_t)__hashmap_index_from_key (hm, key, hm->size_func (key));
}

inline size_t
hashmap_bucket_count (const hashmap *hm)
{
  return array_size (hm->buckets);
}

inline size_t
hashmap_bucket_size (const hashmap *hm, size_t nbucket)
{
  return forward_list_size (array_at (hm->buckets, nbucket));
}

void
hashmap_clear (hashmap *hm)
{
  // Calling clear func for every bucket.
  for (size_t i = 0; i < array_size (hm->buckets); i++)
    forward_list_clear (array_at (hm->buckets, i), hm->destr);

  // Setting size = 0
  hm->size = 0;
}

inline bool
hashmap_contains (const hashmap *hm, constdptr key)
{
  return __hashmap_pair_by_key (hm, key, hm->size_func (key)) != NULL;
}

inline __attribute__ ((always_inline)) bool
hashmap_empty (const hashmap *hm)
{
  return hm->size == 0;
}

void
hashmap_erase (hashmap *hm, constdptr key)
{
  // Calculating index of bucket by hash.
  hash32 index = __hashmap_index_from_key (hm, key, hm->size_func (key));

  // Getting appropriate bucket.
  forward_list *bucket = __hashmap_bucket_by_index (hm, index);

  // Creating fake pair to set pattern to search.
  struct pair pattern = { (dptr)key, NULL };

  // Removing element by key.
  forward_list_remove (bucket, &pattern, hm->cmp, hm->destr);
  hm->size--;
}

void
hashmap_insert (hashmap *hm, constdptr key, constdptr val)
{
  // Checking if we need to increase array buckets's size.
  if (hashmap_bucket_count (hm) == hm->size)
    __hashmap_resize_buckets_array (hm, hm->size
                                            * HASHMAP_INCREASE_BUCKETS_FACTOR);

  // Calculating index of bucket by hash.
  hash32 index = __hashmap_index_from_key (hm, key, hm->size_func (key));

  // Getting appropriate bucket.
  forward_list *bucket = __hashmap_bucket_by_index (hm, index);

  // Creating pattern to find
  struct pair pattern = { (dptr)key, NULL };

  // Checking for existance.
  forward_list_iterator former = forward_list_find (bucket, &pattern, hm->cmp);

  // If not exist => Inserting new pair to the bucket.
  if (former == forward_list_end ())
    {
      // Creating new pair from <key> and <val>
      struct pair *pair = pair_create (key, val);
      forward_list_push_front (bucket, (constdptr)pair);
      hm->size++;
      return;
    }
  // Else, updating value
  ((struct pair *)(former->data))->value = (dptr)val;
}

inline float
hashmap_load_factor (const hashmap *hm)
{
  return (float)hashmap_size (hm) / hashmap_bucket_count (hm);
}

void hashmap_rehash (hashmap *hm);

inline __attribute__ ((always_inline)) size_t
hashmap_size (const hashmap *hm)
{
  return hm->size;
}

void
hashmap_destroy (hashmap *hm)
{
  // Destoying buckets.
  for (size_t i = 0; i < array_size (hm->buckets); i++)
    forward_list_destroy (array_at (hm->buckets, i), hm->destr);

  // Destroying Destroying Array of buckets.
  array_destroy (hm->buckets, NULL);

  // Destroying hashtable instance.
  free (hm);
}
