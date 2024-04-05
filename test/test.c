#include "test.h"

void
run_one_test (Suite *test)
{
  SRunner *sr = srunner_create (test);
  srunner_set_fork_status (sr, CK_FORK);
  srunner_run_all (sr, CK_NORMAL);
  srunner_free (sr);
}

void
run_tests ()
{
  Suite *list[] = { suite_queue (),
                    suite_stack (),
                    suite_list (),
                    suite_forward_list (),
                    suite_array (),
                    suite_hashmap (),
                    suite_hashset (),
                    suite_bitset (),
                    suite_rbtree (),
                    suite_string_array (),
                    suite_linear_allocator (),
                    suite_pool_allocator (),
                    suite_std_allocator (),
                    NULL };

  for (Suite **cur = list; *cur; cur++)
    run_one_test (*cur);
}

int
main ()
{
  run_tests ();
}
