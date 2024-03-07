#include "hashmap.h"

/*
    Private function of hashmap.
*/

static hash32
__hashmap_index_from_key (const hashmap *hm, constdptr key, size_t keysize)
{
  return hash (key, keysize) % hashmap_bucket_count (hm);
}

inline static forward_list *
__hashmap_bucket_by_index (const hashmap *hm, hash32 index)
{
  return array_at (hm->buckets, index);
}

static struct pair *
__hashmap_pair_by_key (const hashmap *hm, constdptr key, size_t keysize)
{
  // Calculating index of bucket by hash.
  hash32 index = __hashmap_index_from_key (hm, key, keysize);

  // Getting appropriate bucket.
  forward_list *bucket = __hashmap_bucket_by_index (hm, index);

  struct pair pattern = {(dptr)key, NULL};
  // Finding pair.
  forward_list_iterator pair = forward_list_find (bucket, &pattern, hm->cmp);

  if (pair != forward_list_end ())
    return (struct pair *)(pair->data);

  return NULL;
}

/*
    Public functions of hashmap's API.
*/

hashmap *
hashmap_create (bool (*cmp) (constdptr pair1, constdptr pair2))
{
  // Allocation memory for the hashmap instance.
  hashmap *hm = (hashmap *)malloc (sizeof (hashmap));

  // Creating array of buckets..
  hm->buckets = array_create (HASHMAP_STARTING_NUMBER_OF_BUCKETS);

  // Creating buckets (forward lists).
  for (size_t i = 0; i < HASHMAP_STARTING_NUMBER_OF_BUCKETS; i++)
    array_push_back (hm->buckets, (dptr *)forward_list_create ());

  hm->size = 0;
  hm->cmp = cmp;

  return hm;
}

dptr
hashmap_at (const hashmap *hm, constdptr key, size_t keysize)
{
  // Getting pair by key.
  struct pair *pair = __hashmap_pair_by_key (hm, key, keysize);

  // If pair exist, returning its value.
  if (pair)
    return pair->value;

  // Else returning NULL.
  return NULL;
}

inline size_t
hashmap_bucket (const hashmap *hm, constdptr key, size_t keysize)
{
  return (size_t)__hashmap_index_from_key (hm, key, keysize);
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
hashmap_clear (hashmap *hm, void (*destr) (dptr pair))
{
  // Setting default destructor if destr == NULL
  if(!destr)
    destr = pair_destroy_default;

  // Calling clear func for every bucket.
  for (size_t i = 0; i < array_size (hm->buckets); i++)
    forward_list_clear (array_at (hm->buckets, i), destr);

  // Setting size = 0
  hm->size = 0;
}

inline bool
hashmap_contains (const hashmap *hm, constdptr key, size_t keysize)
{
  return __hashmap_pair_by_key (hm, key, keysize) != NULL;
}

inline __attribute__ ((always_inline)) bool
hashmap_empty (const hashmap *hm)
{
  return hm->size == 0;
}

void
hashmap_erase (hashmap *hm, constdptr key, size_t keysize,
               void (*destr) (dptr pair))
{
  // Checking if key is exist
  if(!hashmap_contains(hm, key, keysize))
    return;

  // Setting default destructor if destr == NULL
  if(!destr)
    destr = pair_destroy_default;

  // Calculating index of bucket by hash.
  hash32 index = __hashmap_index_from_key (hm, key, keysize);

  // Getting appropriate bucket.
  forward_list *bucket = __hashmap_bucket_by_index (hm, index);

  // Creating fake pair to set pattern to search.
  struct pair pattern = { (dptr)key, NULL };

  // Removing element by key.
  forward_list_remove (bucket, &pattern, hm->cmp, destr);
  hm->size--;
}

void
hashmap_insert (hashmap *hm, constdptr key, size_t keysize, constdptr val)
{
  // Calculating index of bucket by hash.
  hash32 index = __hashmap_index_from_key (hm, key, keysize);

  // Getting appropriate bucket.
  forward_list *bucket = __hashmap_bucket_by_index (hm, index);

  // Creating new pair from <key> and <val>
  struct pair *pair = pair_create (key, val);

  // Inserting new pair to the bucket.
  forward_list_push_front (bucket, (constdptr)pair);
  hm->size++;
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
hashmap_destroy (hashmap *hm, void (*destr) (dptr pair))
{
  // Setting default destructor if destr == NULL
  if(!destr)
    destr = pair_destroy_default;

  // Destoying buckets.
  for (size_t i = 0; i < array_size (hm->buckets); i++)
    forward_list_destroy (array_at (hm->buckets, i), destr);

  // Destroying Destroying Array of buckets.
  array_destroy (hm->buckets, NULL);

  // Destroying hashtable instance.
  free (hm);
}
