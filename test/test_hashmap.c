#include "test.h"

bool cmp_int(constdptr f, constdptr s)
{
    return (*(int *)((struct pair *)f)->key == *(int *)((struct pair *)s)->key);
}


START_TEST(hashmap_test_1)
{
    int a = 24321;//, b = 78938, c = 18346;
    int val1 = 1;//, val2 = 2, val3 = 3;
    hashmap *hm = hashmap_create(cmp_int);

    ck_assert(hm != NULL);
    ck_assert(hashmap_size(hm) == 0);
    ck_assert_uint_eq(hashmap_bucket_count(hm), HASHMAP_STARTING_NUMBER_OF_BUCKETS);

    hashmap_insert(hm, &a, sizeof(a), &val1);
    ck_assert_uint_eq(hashmap_size(hm), 1);
    ck_assert(hashmap_at(hm, &a, sizeof(a)) == &val1);

    hashmap_destroy(hm, NULL);
}


START_TEST(hashmap_test_2)
{

}


Suite *
suite_hashmap ()
{
  Suite *s;
  TCase *tc;

  s = suite_create ("Hashmap test");
  tc = tcase_create ("Hashmap test");

  tcase_add_test (tc, hashmap_test_1);
  tcase_add_test (tc, hashmap_test_2);

  suite_add_tcase (s, tc);

  return s;
}