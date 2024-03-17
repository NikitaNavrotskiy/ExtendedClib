#include "test.h"

START_TEST (bitset_test_1)
{
  size_t n = 15;

  bitset *b = bitset_create (n);
  ck_assert (b != NULL);
  ck_assert (bitset_size (b) == 15);

  for (int i = 0; i < 2; i++)
    ck_assert (b->bits[i] == 0);

  ck_assert (bitset_count (b) == 0);

  bitset_set (b, 3);
  bitset_set (b, 14);
  bitset_set (b, 8);

  ck_assert (bitset_count (b) == 3);

  ck_assert (bitset_test (b, 3));
  ck_assert (bitset_test (b, 14));
  ck_assert (bitset_test (b, 8));

  ck_assert (b->bits[0] == 0b00001000);
  ck_assert_uint_eq (b->bits[1], 0b01000001);

  bitset_set_all (b);

  ck_assert (bitset_count (b) == 15);

  ck_assert (bitset_all (b));

  for (int i = 0; i < 1; i++)
    ck_assert (b->bits[i] == 0b11111111);

  bitset_reset (b, 3);
  bitset_reset (b, 14);
  bitset_reset (b, 8);

  ck_assert (!bitset_test (b, 3));
  ck_assert (!bitset_test (b, 14));
  ck_assert (!bitset_test (b, 8));

  ck_assert (b->bits[0] == 0b11110111);
  ck_assert (b->bits[1] == 0b10111110);

  bitset_reset_all (b);

  ck_assert (!bitset_any (b));

  for (int i = 0; i < 2; i++)
    ck_assert (b->bits[i] == 0);

  bitset_destroy (b);
}

START_TEST (bitset_test_2)
{
  int data = 234;
  int cpy = 0;

  bitset *b = bitset_create_from_data (&data, sizeof (data));
  ck_assert (b != NULL);
  ck_assert (bitset_size (b) == 32);

  ck_assert (b->bits[0] == 234);
  for (int i = 1; i < 4; i++)
    ck_assert (b->bits[i] == 0);

  bitset_to_data (b, &cpy, sizeof (int));
  ck_assert (cpy == data);

  bitset_set (b, 3);
  bitset_set (b, 14);
  bitset_set (b, 8);

  ck_assert (bitset_test (b, 3));
  ck_assert (bitset_test (b, 14));
  ck_assert (bitset_test (b, 8));

  ck_assert (b->bits[0] == (0b00001000 | 234));
  ck_assert (b->bits[1] == 0b01000001);
  ck_assert (b->bits[2] == 0b00000000);
  ck_assert (b->bits[3] == 0b00000000);

  bitset_set_all (b);

  ck_assert (bitset_count (b) == 32);

  ck_assert (bitset_any (b));

  for (int i = 0; i < 4; i++)
    ck_assert (b->bits[i] == 0b11111111);

  bitset_reset (b, 3);
  bitset_reset (b, 14);
  bitset_reset (b, 8);

  ck_assert (!bitset_test (b, 3));
  ck_assert (!bitset_test (b, 14));
  ck_assert (!bitset_test (b, 8));

  ck_assert (b->bits[0] == 0b11110111);
  ck_assert (b->bits[1] == 0b10111110);
  ck_assert (b->bits[2] == 0xff);
  ck_assert (b->bits[3] == 0xff);

  bitset_reset_all (b);

  ck_assert (bitset_count (b) == 0);

  ck_assert (!bitset_any (b));

  for (int i = 0; i < 4; i++)
    ck_assert (b->bits[i] == 0);

  bitset_destroy (b);
}

START_TEST (bitset_test_3)
{
  size_t n = 8;

  bitset *b = bitset_create (n);

  bitset_flip (b, 0);
  bitset_flip (b, 1);

  ck_assert_int_eq (b->bits[0], 0b00000011);

  bitset_flip (b, 0);
  bitset_flip (b, 1);

  ck_assert (b->bits[0] == 0);

  bitset_set (b, 0);
  bitset_set (b, 2);
  bitset_set (b, 5);

  ck_assert (b->bits[0] == 0b00100101);

  bitset_flip_all (b);
  ck_assert (b->bits[0] == 0b11011010);

  bitset_flip_all (b);
  ck_assert (b->bits[0] == 0b00100101);

  bitset_destroy (b);
}

Suite *
suite_bitset ()
{
  Suite *s;
  TCase *tc;

  s = suite_create ("Bitset test");
  tc = tcase_create ("Bitset test");

  tcase_add_test (tc, bitset_test_1);
  tcase_add_test (tc, bitset_test_2);
  tcase_add_test (tc, bitset_test_3);

  suite_add_tcase (s, tc);

  return s;
}