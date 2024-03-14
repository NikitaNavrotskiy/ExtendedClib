#include "bitset.h"

////////////////////////////////////////////////////
/*         Private functions of the bitset        */
////////////////////////////////////////////////////


////////////////////////////////////////////////////
/*       Public API functions of the bitset       */
////////////////////////////////////////////////////

bitset *bitset_create(size_t n)
{
    bitset *b = (bitset *)malloc(sizeof(bitset));

    b->n = n;
    // allocating n / 8 (from bits in bytes) + extra 1 byte,
    // if some extra bits doesn't fit.
    b->bits = (unsigned char *)calloc(n / 8 + ((n % 8) & 1), sizeof(unsigned char));

    return b;
}

bitset *bitset_create_from_data(dptr data, size_t size)
{
    bitset *b = (bitset *)malloc(sizeof(bitset));

    // Converting bytes to bits.
    b->n = size * 8;
    b->bits = (unsigned char *)malloc(sizeof(unsigned char) * size);

    // copying bits from data to <bits>
    memcpy(b->bits, data, size);

    return b;
}

bool bitset_all(bitset *b);

bool bitset_any(bitset *b);

size_t bitset_count(bitset *b);

void bitset_flip(bitset *b, size_t pos);

void bitset_flip_all(bitset *b);

bool bitset_none(bitset *b);

void bitset_reset(bitset *b, size_t pos)
{
    if(pos >= b->n)
        return;

    // calculating position of byte.
    size_t byte_pos = pos / 8;

    // working with byte.
    char byte = b->bits[byte_pos];

    // setting mask
    char mask = 1 << (pos % 8);

    // Inversing mask
    mask = ~mask;

    // applying mask by & operator.
    byte &= mask;

    // returning byte to array.
    b->bits[byte_pos] = byte;    
}

inline void bitset_reset_all(bitset *b)
{
    // setting all bytes to zero.
    char extra = b->n % 8 != 0 ? 1 : 0;
    memset(b->bits, 0, b->n / 8 + extra);
}

void bitset_set(bitset *b, size_t pos)
{
    if(pos >= b->n)
        return;

    // calculating position of byte.
    size_t byte_pos = pos / 8;

    // working with byte.
    char byte = b->bits[byte_pos];

    // setting mask
    char mask = 1 << (pos % 8);

    // applying mask by | operator.
    byte |= mask;

    // returning byte to array.
    b->bits[byte_pos] = byte;
}

inline void bitset_set_all(bitset *b)
{
    // setting all bytes to one.
    char extra = b->n % 8 != 0 ? 1 : 0;
    memset(b->bits, 0xFF, b->n / 8 + extra);
}

inline __attribute__((__always_inline__)) size_t 
bitset_size(bitset *b)
{
    return b->n;
}

bool bitset_test(bitset *b, size_t pos)
{
    if(pos >= b->n)
        return false;

    // working with byte.
    char byte = b->bits[pos / 8];

    // removing offset.
    byte >>= pos % 8;

    return byte & 1;
}

void bitset_to_data(bitset *b, dptr data, size_t size);

void bitset_destroy(bitset *b)
{
    free(b->bits);
    free(b);
}