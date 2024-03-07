/**
 * @file hash.c Implementation of hash algorithm
 * for Hashset and Hashmap.
 */

#include "hash.h"


hash32 hash(void *key, size_t len)
{
    hash32 hash = 0;

    for(uint32_t i = 0; i < len; i++)
    {
        hash += ((char *)key)[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}