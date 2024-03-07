#include "hashmap.h"


/*
    Private function of hashmap.
*/

static hash32 __hashmap_index_from_key(const hashmap *hm, constdptr key, size_t keysize)
{
    return hash(key, keysize) % hashmap_bucket_count(hm);    
}


static struct pair *__hashmap_pair_by_key(const hashmap *hm, constdptr key, size_t keysize)
{
    // Calculating index of bucket by hash.
    hash32 index = __hashmap_index_from_key(hm, key, keysize);

    // Getting appropriate bucket.
    forward_list *bucket = array_at(hm->buckets, index);

    // Finding pair.
    forward_list_iterator pair = forward_list_find(bucket, key, hm->cmp);

    if(pair != forward_list_end())
        return (struct pair *)(pair->data);

    return NULL;  
}


/*
    Public functions of hashmap's API.
*/

hashmap *hashmap_create (bool (*cmp)(constdptr key1, constdptr key2))
{
    // Allocation memory for the hashmap instance.
    hashmap *hm = (hashmap *)malloc(sizeof(hashmap));

    //Creating array of buckets..
    hm->buckets = array_create(HASHMAP_STARTING_NUMBER_OF_BUCKETS);

    // Creating buckets (forward lists).
    for(size_t i = 0; i < array_size(hm->buckets); i++)
        array_push_back(hm->buckets, (dptr *)forward_list_create());

    hm->size = 0;
    hm->cmp = cmp;

    return hm;
}

dptr hashmap_at(const hashmap *hm, constdptr key, size_t keysize)
{
    // Getting pair by key.
    struct pair *pair = __hashmap_pair_by_key(hm, key, keysize);

    // If pair exist, returning its value.
    if(pair)
        return pair->value;
    
    // Else returning NULL.
    return NULL;
}

size_t hashmap_bucket(const hashmap *hm, constdptr key, size_t keysize);

inline size_t hashmap_bucket_count(const hashmap *hm)
{
    return array_size(hm->buckets);
}

inline size_t hashmap_bucket_size(const hashmap *hm, size_t nbucket)
{
    return forward_list_size(array_at(hm->buckets, nbucket));
}

void hashmap_clear(hashmap *hm, void (*destr) (dptr pair))
{
    // Calling clear func for every bucket.
    for(size_t i = 0; i < array_size(hm->buckets); i++)
        forward_list_clear(array_at(hm->buckets, i), destr);

    // Setting size = 0
    hm->size = 0;   
}

bool hashmap_contains(const hashmap *hm, constdptr key, size_t keysize);

inline __attribute__((always_inline)) bool hashmap_empty(const hashmap *hm)
{
    return hm->size == 0;
}

void hashmap_erase(hashmap *hm, constdptr key, size_t keysize, void (*destr) (dptr pair));

void hashmap_insert(hashmap *hm, constdptr key, size_t keysize, constdptr val);

float hashmap_load_factor(const hashmap *hm);

void hashmap_rehash(hashmap *hm);

inline __attribute__((always_inline)) size_t hashmap_size(const hashmap *hm)
{
    return hm->size;
}

void hashmap_destroy(hashmap *hm, void (*destr) (dptr pair))
{
    // Destoying buckets.
    for(size_t i = 0; i < array_size(hm->buckets); i++)
        forward_list_destroy(array_at(hm->buckets, i), destr);

    // Destroying Destroying Array of buckets.
    array_destroy(hm->buckets, NULL);

    // Destroying hashtable instance.
    free(hm);
}
