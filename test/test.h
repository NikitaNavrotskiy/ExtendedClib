#ifndef _TEST_TEST_H
#define _TEST_TEST_H

#include <check.h>
#include <stdio.h> // debug
#include <stdlib.h>
#include <time.h>

#include "../lib/list.h"
#include "../lib/queue.h"
#include "../lib/stack.h"
#include "../lib/forward_list.h"

Suite *suite_queue ();
Suite *suite_stack ();
Suite *suite_list ();
Suite *suite_forward_list();

#endif