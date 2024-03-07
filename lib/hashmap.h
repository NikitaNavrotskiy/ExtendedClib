/**
 * @file hashmap.h Implementation of Hashmap
 * (unordered_map in STL) data structure.
 */

#ifndef _EXTENDED_C_LIB_LIB_HASHMAP_H
#define _EXTENDED_C_LIB_LIB_HASHMAP_H

#include <stdlib.h> //malloc, free
#include <stdbool.h> // bool

#include "array.h"
#include "forward_list.h"
#include "hash.h"
#include "types.h"


#define HASHMAP_STARTING_NUMBER_OF_BUCKETS 5
#define HASHMAP_INCREASE_BUCKETS_FACTOR 2


/**
 * @struct hashmap.
 * @brief Implementation of Hashmap data structure.
 */
typedef struct hashmap
{
    /**
     * @brief Counting current number of pairs.
     */
    size_t size;

    /**
     * @brief Array that contains keys and 
     * instances of forward_list.
     */
    array *buckets;

    /**
     * @brief Compare function for keys.
     * Return true if key1 == key2.
     * Return false if key1 != key2.
     */
    bool (*cmp)(constdptr, constdptr);
}hashmap;


/**
 * @brief Public API functions of the hashmap.
 *
 */

/**
 * @brief Function to create new hashmap. Allocates the memory. Should be
 * destroyed at the end.
 * @return Pointer to new hashmap.
 */
hashmap *hashmap_create (bool (*cmp)(constdptr key1, constdptr key2));

/**
 * @brief Function to get value by key from the 
 * hashmap.
 * 
 * @param hm Pointer to the instance of hashmap. 
 * @param key Key for searching.
 * @param keysize Size of the key.
 * @return dptr 
 */
dptr hashmap_at(const hashmap *hm, constdptr key, size_t keysize);

/**
 * @brief Function to get number of bucket for
 * <key> key.
 * 
 * @param hm Pointer to the instance of hashmap. 
 * @param key Key for searching.
 * @return size_t 
 */
size_t hashmap_bucket(const hashmap *hm, constdptr key, size_t keysize);

/**
 * @brief Function to get number of buckets in hashtable.
 * 
 * @param hm Pointer to the instance of hashmap.  
 * @param keysize Size of the key.
 * @return size_t Number of buckets in hashtable.
 */
size_t hashmap_bucket_count(const hashmap *hm);

/**
 * @brief Function to get number of elements
 * in <nbucket> bucket.
 * 
 * @param hm Pointer to the instance of hashmap.  
 * @param nbucket 
 * @return size_t Number of elements in <nbucket>
 * bucket.
 */
size_t hashmap_bucket_size(const hashmap *hm, size_t nbucket);

/**
 * @brief Function to clear hashtable.
 * Do not destroy instance of hashtable.
 * 
 * @param hm Pointer to the instance of hashmap. 
 * @param destr Function to destroy pair.
 */
void hashmap_clear(hashmap *hm, void (*destr) (dptr pair));

/**
 * @brief Function to check if key is in
 * the hashmap.
 * 
 * @param hm Pointer to the instance of hashmap. 
 * @param key Key to check on existense.
 * @param keysize Size of the key.
 * @return true If key is in hashmap.
 * @return false If key is not in hashmap.
 */
bool hashmap_contains(const hashmap *hm, constdptr key, size_t keysize);

/**
 * @brief Function to check if hashmap is empty.
 * 
 * @param hm Pointer to the instance of hashmap.  
 * @return true If hashmap is empty.
 * @return false If hashmap is not empty.
 */
bool hashmap_empty(const hashmap *hm);

/**
 * @brief Function to erase pair by key 
 * from the hashmap.
 * 
 * @param hm Pointer to the instance of hashmap.  
 * @param key Key to find element to erase.
 * @param keysize Size of the key.
 * @param destr Function to destroy pair.
 */
void hashmap_erase(hashmap *hm, constdptr key, size_t keysize, void (*destr) (dptr pair));

/**
 * @brief Function to insert new pair of key, val into
 * the hashmap.
 * 
 * @param hm Pointer to the instance of hashmap.  
 * @param key Key of the pair to insert.
 * @param keysize Size of the key.
 * @param val Val of the pair to insert.
 */
void hashmap_insert(hashmap *hm, constdptr key, size_t keysize, constdptr val);

/**
 * @brief Function to get load of hashmap.
 * 
 * @param hm Pointer to the instance of hashmap.  
 * @return float Size / Number of backets.
 */
float hashmap_load_factor(const hashmap *hm);

/**
 * @brief Function to rehash hashmap.
 * 
 * @param hm Pointer to the instance of hashmap.  
 */
void hashmap_rehash(hashmap *hm);

/**
 * @brief Function to get number of elements
 * if hashmap.
 * 
 * @param hm Pointer to the instance of hashmap.  
 * @return size_t Number of elements in hashmap.
 */
size_t hashmap_size(const hashmap *hm);

/**
 * @brief Destructor for hashmap.
 * 
 * @param hm Pointer to the instance of hashmap.  
 * @param destr Function to destroy pair.
 */
void hashmap_destroy(hashmap *hm, void (*destr) (dptr pair));

#endif