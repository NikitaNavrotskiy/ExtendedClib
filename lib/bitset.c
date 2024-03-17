#include "bitset.h"

////////////////////////////////////////////////////
/*         Private functions of the bitset        */
////////////////////////////////////////////////////

/**
 * @brief Function to compare bytes.
 *
 * @param b1 First byte.
 * @param b2 Second byte.
 * @return true If bytes are equal.
 * @return false If bytes aren't equal.
 */
inline static bool
__bitset_compare_byte (char b1, char b2)
{
  return (b1 ^ b2) == 0;
}

/**
 * @brief Count bytes from bits (rounding up).
 *
 * @param bits Number of bits.
 * @return size_t Resulting number of bytes.
 */
inline static size_t
__bitset_total_bytes_from_bits (size_t bits)
{
  size_t extra = bits % 8 != 0 ? 1 : 0;
  return extra + bits / 8;
}

static bool
__bitset_test_bit_in_byte (char byte, char nbit)
{
  return (byte & (1 << nbit));
}

/**
 * @brief Number of bits, that are set in byte, where
 * only nbits.
 *
 * @param byte Byte from to count.
 * @param nbits Number of bits.
 * @return char Resulting number of
 * bits are set.
 */
static char
__bitset_count_set_extra_bits (char byte, char nbits)
{
  char res = 0;
  // Setting mask to remove begging bits.
  char mask = 0xFF >> (8 - nbits);

  byte &= mask;

  for (int i = nbits - 1; i >= 0; i--)
    {
      if (__bitset_test_bit_in_byte (byte, i))
        res++;
    }

  return res;
}

////////////////////////////////////////////////////
/*       Public API functions of the bitset       */
////////////////////////////////////////////////////

bitset *
bitset_create (size_t n)
{
  bitset *b = (bitset *)malloc (sizeof (bitset));

  b->n = n;
  // allocating n / 8 (from bits in bytes) + extra 1 byte,
  // if some extra bits doesn't fit.
  b->bits = (unsigned char *)calloc (n / 8 + ((n % 8) & 1),
                                     sizeof (unsigned char));

  return b;
}

bitset *
bitset_create_from_data (dptr data, size_t size)
{
  bitset *b = (bitset *)malloc (sizeof (bitset));

  // Converting bytes to bits.
  b->n = size * 8;
  b->bits = (unsigned char *)malloc (sizeof (unsigned char) * size);

  // copying bits from data to <bits>
  memcpy (b->bits, data, size);

  return b;
}

bool
bitset_all (bitset *b)
{
  size_t nbytes = __bitset_total_bytes_from_bits (b->n);
  size_t i = 0;
  char extra_bits = nbytes - b->n / 8;
  bool res = true;

  // Checking extra part.
  if (extra_bits)
    {
      i = 1;
      res = __bitset_count_set_extra_bits (b->bits[0], b->n - (nbytes - 1) * 8)
            != 0;
    }

  // Checking integral bytes.
  for (; i < nbytes && res; i++)
    res = res || (b->bits[i] != 0);

  return res;
}

bool
bitset_any (bitset *b)
{
  size_t nbytes = __bitset_total_bytes_from_bits (b->n);
  size_t i = 0;
  char extra_bits = nbytes - b->n / 8;
  bool res = false;

  // Checking extra part.
  if (extra_bits)
    {
      i = 1;
      res = extra_bits
            == __bitset_count_set_extra_bits (b->bits[0],
                                              b->n - (nbytes - 1) * 8);
    }

  // Checking integral bytes.
  for (; i < nbytes && !res; i++)
    res |= b->bits[i];

  return res;
}

size_t
bitset_count (bitset *b)
{
  size_t nbytes = __bitset_total_bytes_from_bits (b->n);
  size_t i = 0;
  size_t res = 0;
  char extra_bits = nbytes - b->n / 8;

  // Counting extra part.
  if (extra_bits)
    {
      i = 1;
      res += (size_t)__bitset_count_set_extra_bits (b->bits[0],
                                                    b->n - (nbytes - 1) * 8);
    }

  // Counting integral bytes.
  for (; i < nbytes; i++)
    res += (size_t)__bitset_count_set_extra_bits (b->bits[i], 8);

  return res;
}

void
bitset_flip (bitset *b, size_t pos)
{
  if (pos >= b->n)
    return;

  // getting bit from pos.
  char nbit = pos % 8;

  // making mask
  char mask = 1 << nbit;

  // using ^ to inverse bit.
  b->bits[pos / 8] ^= mask;
}

void
bitset_flip_all (bitset *b)
{
  size_t nbytes = __bitset_total_bytes_from_bits (b->n);

  for (size_t i = 0; i < nbytes; i++)
    b->bits[i] = ~b->bits[i];
}

void
bitset_reset (bitset *b, size_t pos)
{
  if (pos >= b->n)
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

inline void
bitset_reset_all (bitset *b)
{
  // setting all bytes to zero.
  memset (b->bits, 0, __bitset_total_bytes_from_bits (b->n));
}

void
bitset_set (bitset *b, size_t pos)
{
  if (pos >= b->n)
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

inline void
bitset_set_all (bitset *b)
{
  // setting all bytes to one.
  memset (b->bits, 0xFF, __bitset_total_bytes_from_bits (b->n));
}

inline __attribute__ ((__always_inline__)) size_t
bitset_size (bitset *b)
{
  return b->n;
}

bool
bitset_test (bitset *b, size_t pos)
{
  if (pos >= b->n)
    return false;

  // working with byte.
  char byte = b->bits[pos / 8];

  // removing offset.
  byte >>= pos % 8;

  return byte & 1;
}

void
bitset_to_data (bitset *b, dptr data, size_t size)
{
  if (size * 8 != b->n)
    return;

  memcpy (data, b->bits, size);
}

void
bitset_destroy (bitset *b)
{
  free (b->bits);
  free (b);
}