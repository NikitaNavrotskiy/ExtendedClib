#ifndef _TEST_TEST_H
#define _TEST_TEST_H

#include <check.h>
#include <stdlib.h>
#include <time.h>

#include "../lib/array.h"
#include "../lib/bitset.h"
#include "../lib/forward_list.h"
#include "../lib/hashmap.h"
#include "../lib/hashset.h"
#include "../lib/list.h"
#include "../lib/queue.h"
#include "../lib/rbtree.h"
#include "../lib/stack.h"

#include "../lib/string_array.h"

#include "../lib/linear_allocator.h"
#include "../lib/pool_allocator.h"
#include "../lib/std_allocator.h"

Suite *suite_queue ();
Suite *suite_stack ();
Suite *suite_list ();
Suite *suite_forward_list ();
Suite *suite_array ();
Suite *suite_hashmap ();
Suite *suite_hashset ();
Suite *suite_bitset ();
Suite *suite_rbtree ();

Suite *suite_string_array ();

Suite *suite_linear_allocator ();
Suite *suite_pool_allocator ();
Suite *suite_std_allocator ();

#endif
