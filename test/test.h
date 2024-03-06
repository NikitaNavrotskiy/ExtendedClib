#ifndef _TEST_TEST_H
#define _TEST_TEST_H

#include <check.h>
#include <stdlib.h>
#include <time.h>

#include "../lib/forward_list.h"
#include "../lib/list.h"
#include "../lib/queue.h"
#include "../lib/stack.h"

#include "../lib/linear_allocator.h"
#include "../lib/pool_allocator.h"

Suite *suite_queue ();
Suite *suite_stack ();
Suite *suite_list ();
Suite *suite_forward_list ();

Suite *suite_linear_allocator ();
Suite *suite_pool_allocator ();

#endif