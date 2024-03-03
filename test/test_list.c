#include "test.h"



void standart_destructor(dptr data)
{
  data = data;
  return;
}

START_TEST(list_test_1)
{
  int a = 1, b = 2;
  list * l = list_create();
  ck_assert(l != NULL);
  ck_assert(list_empty(l));
  ck_assert(list_size(l) == 0);
  ck_assert(list_back(l) == NULL);
  ck_assert(list_front(l) == NULL);
  ck_assert(list_begin(l) == NULL);
  ck_assert(list_end() == NULL);

  list_push_back(l, &a);
  ck_assert(!list_empty(l));
  ck_assert(list_size(l) == 1);
  ck_assert(*(int *)list_back(l) == a);
  ck_assert(*(int *)list_front(l) == a);
  ck_assert(*(int *)list_begin(l)->data == a);
  ck_assert(list_end() == NULL);

  list_pop_back(l, standart_destructor);
  
  ck_assert(list_empty(l));
  ck_assert(list_size(l) == 0);
  ck_assert(list_back(l) == NULL);
  ck_assert(list_front(l) == NULL);
  ck_assert(list_begin(l) == NULL);
  ck_assert(list_end() == NULL);

  list_push_front(l, &a);
  ck_assert(!list_empty(l));
  ck_assert(list_size(l) == 1);
  ck_assert(*(int *)list_back(l) == a);
  ck_assert(*(int *)list_front(l) == a);
  ck_assert(*(int *)list_begin(l)->data == a);
  ck_assert(list_end() == NULL);

  list_pop_front(l, standart_destructor);
  ck_assert(list_empty(l));
  ck_assert(list_size(l) == 0);
  ck_assert(list_back(l) == NULL);
  ck_assert(list_front(l) == NULL);
  ck_assert(list_begin(l) == NULL);
  ck_assert(list_end() == NULL);

  list_push_back(l, &a);
  ck_assert(!list_empty(l));
  ck_assert(list_size(l) == 1);
  ck_assert(*(int *)list_back(l) == a);
  ck_assert(*(int *)list_front(l) == a);
  ck_assert(*(int *)list_begin(l)->data == a);
  ck_assert(list_end() == NULL);

  list_push_back(l, &b);
  ck_assert(!list_empty(l));
  ck_assert(list_size(l) == 2);
  ck_assert(*(int *)list_back(l) == b);
  ck_assert(*(int *)list_front(l) == a);
  ck_assert(*(int *)list_begin(l)->data == a);
  ck_assert(list_end() == NULL);  

  list_pop_back(l, standart_destructor);
  ck_assert(!list_empty(l));
  ck_assert(list_size(l) == 1);
  ck_assert(*(int *)list_back(l) == a);
  ck_assert(*(int *)list_front(l) == a);
  ck_assert(*(int *)list_begin(l)->data == a);
  ck_assert(list_end() == NULL);

  list_push_front(l, &b);
  ck_assert(!list_empty(l));
  ck_assert(list_size(l) == 2);
  ck_assert(*(int *)list_back(l) == a);
  ck_assert(*(int *)list_front(l) == b);
  ck_assert(*(int *)list_begin(l)->data == b);
  ck_assert(list_end() == NULL);  

  list_pop_front(l, standart_destructor);
  ck_assert(!list_empty(l));
  ck_assert(list_size(l) == 1);
  ck_assert(*(int *)list_back(l) == a);
  ck_assert(*(int *)list_front(l) == a);
  ck_assert(*(int *)list_begin(l)->data == a);
  ck_assert(list_end() == NULL);

  list_clear(l, standart_destructor);
  ck_assert(list_empty(l));
  ck_assert(list_size(l) == 0);
  ck_assert(list_size(l) == 0);
  ck_assert(list_back(l) == NULL);
  ck_assert(list_front(l) == NULL);
  ck_assert(list_begin(l) == NULL);
  ck_assert(list_end() == NULL);  

  int i;
  int arr[1000] = {0};
  for(i = 0; i < 1000; i++)
  {
    arr[i] = i;
    list_push_back(l, arr + i);
    ck_assert(!list_empty(l));
    ck_assert(list_size(l) == (size_t)(arr[i] + 1));
    ck_assert_uint_eq(*(int *)list_back(l), arr[i]);
    ck_assert_uint_eq(*(int *)list_front(l), 0);
    ck_assert(list_begin(l)->data == (dptr)arr);
    ck_assert(list_end() == NULL);    
  }

  for(i = 999; i > 0; i--)
  {
    ck_assert(!list_empty(l));
    list_pop_back(l, standart_destructor);
    ck_assert(list_size(l) == (size_t)arr[i]);
    ck_assert_uint_eq(*(int *)list_back(l), arr[i] - 1);
    ck_assert(*(int *)list_front(l) == 0);
    ck_assert(list_begin(l)->data == (dptr)arr);
    ck_assert(list_end() == NULL);    
  }

  list_pop_back(l, standart_destructor);
  ck_assert(list_empty(l));
  ck_assert(list_size(l) == 0);
  ck_assert(list_back(l) == NULL);
  ck_assert(list_front(l) == NULL);
  ck_assert(list_begin(l) == NULL);
  ck_assert(list_end() == NULL); 

  for(int i = 0; i < 1000; i++)
    arr[i] = 0;

  for(i = 0; i < 1000; i++)
  {
    arr[i] = i;
    list_push_front(l, arr + i);
    ck_assert(!list_empty(l));
    ck_assert(list_size(l) == (size_t)(arr[i] + 1));
    ck_assert_uint_eq(*(int *)list_back(l), 0);
    ck_assert_uint_eq(*(int *)list_front(l), i);
    ck_assert_ptr_eq(list_begin(l)->data, (dptr)(arr + i));
    ck_assert(list_end() == NULL);    
  }

  for(i = 999; i > 0; i--)
  {
    list_pop_front(l, standart_destructor);
    ck_assert(!list_empty(l));
    ck_assert(list_size(l) == (size_t)arr[i]);
    ck_assert_uint_eq(*(int *)list_back(l), 0);
    ck_assert(*(int *)list_front(l) == arr[i] - 1);
    ck_assert(list_begin(l)->data == (dptr)(arr + i - 1));
    ck_assert(list_end() == NULL);    
  }

  list_pop_back(l, standart_destructor);
  ck_assert(list_empty(l));
  ck_assert(list_size(l) == 0);
  ck_assert(list_back(l) == NULL);
  ck_assert(list_front(l) == NULL);
  ck_assert(list_begin(l) == NULL);
  ck_assert(list_end() == NULL); 


  list_destroy(l, standart_destructor);
}


dptr copy_func(dptr val)
{
  return val;
}

START_TEST(list_test_2)
{
  list * l = list_create();
  ck_assert(l != NULL);
  ck_assert(list_empty(l));
  ck_assert(list_size(l) == 0);
  ck_assert(list_back(l) == NULL);
  ck_assert(list_front(l) == NULL);
  ck_assert(list_begin(l) == NULL);
  ck_assert(list_end() == NULL);

  int arr[1000] = {0};
  for(int i = 0; i < 1000; i++)
  {
    arr[i] = i;
    list_push_back(l, arr + i);  
  }

  list *lcp = list_copy(l, copy_func);

  ck_assert_uint_eq(list_size(l), list_size(lcp));
  for(list_iterator li = list_begin(l), licp = list_begin(lcp); li != list_end() && licp != list_end(); li = li->next, licp = licp->next)
    ck_assert_int_eq(*(int *)li->data, *(int *)licp->data);

  list_destroy(l, standart_destructor);
  list_destroy(lcp, standart_destructor);
}


bool cmp(constdptr f, constdptr s)
{
  return (*(int *)f == *(int *)s);
}

bool predicate1(constdptr d)
{
  return (*(int *)d) >= 2 && (*(int *)d) < 4;
}

bool predicate2(constdptr d)
{
  return (*(int *)d) < 2 || (*(int *)d) > 3;
}

START_TEST(list_test_3)
{
    list *l = list_create();
    int arr[10][50] = {0};

    for(int j = 0; j < 10; j++)
    {
      for(int i = 0; i < 5; i++)
      {
        arr[j][i] = i;
        list_push_back(l, &arr[j][i]);
      }
    }

    int i;
    for(i = 0; i < 5; i++)
    {
      ck_assert_uint_eq(list_count(l, &i, cmp), 10);
    }

    i = 6;
    ck_assert(list_count(l, &i, cmp) == 0);


    ck_assert(list_count_if(l, predicate1) == 20);
    ck_assert(list_count_if(l, predicate2) == 30);

    list_destroy(l, standart_destructor);
}


START_TEST(list_test_4)
{
  list *l = list_create();
  int a = 1, b = 2, c = 3, d = 4;

  list_emplace(l, NULL, &b);
  ck_assert(!list_empty(l));
  ck_assert(list_size(l) == 1);
  ck_assert(*(int *)list_back(l) == b);
  ck_assert(*(int *)list_front(l) == b);
  ck_assert(*(int *)list_begin(l)->data == b);
  ck_assert(list_end() == NULL);

  list_emplace(l, NULL, &c);
  ck_assert(!list_empty(l));
  ck_assert(list_size(l) == 2);
  ck_assert(*(int *)list_back(l) == c);
  ck_assert(*(int *)list_front(l) == b);
  ck_assert(*(int *)list_begin(l)->data == b);
  ck_assert(list_end() == NULL);

  list_emplace(l, list_begin(l), &a);
  ck_assert(!list_empty(l));
  ck_assert(list_size(l) == 3);
  ck_assert(*(int *)list_back(l) == c);
  ck_assert(*(int *)list_front(l) == a);
  ck_assert(*(int *)list_begin(l)->data == a);
  ck_assert(list_end() == NULL);
  
  list_emplace(l, list_begin(l)->next->next, &d);
  ck_assert(*(int *)l->back->prev->data == d);
  ck_assert(*(int *)l->front->next->next->data == d);
  ck_assert(!list_empty(l));
  ck_assert(list_size(l) == 4);
  ck_assert(*(int *)list_back(l) == c);
  ck_assert(*(int *)list_front(l) == a);
  ck_assert(*(int *)list_begin(l)->data == a);
  ck_assert(list_end() == NULL);

  list_destroy(l, standart_destructor);
}


START_TEST(list_test_5)
{
  int a = 1, b = 2;
  list * l = list_create();
  ck_assert(l != NULL);
  ck_assert(list_empty(l));
  ck_assert(list_size(l) == 0);
  ck_assert(list_back(l) == NULL);
  ck_assert(list_front(l) == NULL);
  ck_assert(list_begin(l) == NULL);
  ck_assert(list_end() == NULL);

  list_emplace_back(l, &a);
  ck_assert(!list_empty(l));
  ck_assert(list_size(l) == 1);
  ck_assert(*(int *)list_back(l) == a);
  ck_assert(*(int *)list_front(l) == a);
  ck_assert(*(int *)list_begin(l)->data == a);
  ck_assert(list_end() == NULL);

  list_pop_back(l, standart_destructor);
  
  ck_assert(list_empty(l));
  ck_assert(list_size(l) == 0);
  ck_assert(list_back(l) == NULL);
  ck_assert(list_front(l) == NULL);
  ck_assert(list_begin(l) == NULL);
  ck_assert(list_end() == NULL);

  list_emplace_front(l, &a);
  ck_assert(!list_empty(l));
  ck_assert(list_size(l) == 1);
  ck_assert(*(int *)list_back(l) == a);
  ck_assert(*(int *)list_front(l) == a);
  ck_assert(*(int *)list_begin(l)->data == a);
  ck_assert(list_end() == NULL);

  list_pop_front(l, standart_destructor);
  ck_assert(list_empty(l));
  ck_assert(list_size(l) == 0);
  ck_assert(list_back(l) == NULL);
  ck_assert(list_front(l) == NULL);
  ck_assert(list_begin(l) == NULL);
  ck_assert(list_end() == NULL);

  list_emplace_back(l, &a);
  ck_assert(!list_empty(l));
  ck_assert(list_size(l) == 1);
  ck_assert(*(int *)list_back(l) == a);
  ck_assert(*(int *)list_front(l) == a);
  ck_assert(*(int *)list_begin(l)->data == a);
  ck_assert(list_end() == NULL);

  list_emplace_back(l, &b);
  ck_assert(!list_empty(l));
  ck_assert(list_size(l) == 2);
  ck_assert(*(int *)list_back(l) == b);
  ck_assert(*(int *)list_front(l) == a);
  ck_assert(*(int *)list_begin(l)->data == a);
  ck_assert(list_end() == NULL);  

  list_pop_back(l, standart_destructor);
  ck_assert(!list_empty(l));
  ck_assert(list_size(l) == 1);
  ck_assert(*(int *)list_back(l) == a);
  ck_assert(*(int *)list_front(l) == a);
  ck_assert(*(int *)list_begin(l)->data == a);
  ck_assert(list_end() == NULL);

  list_emplace_front(l, &b);
  ck_assert(!list_empty(l));
  ck_assert(list_size(l) == 2);
  ck_assert(*(int *)list_back(l) == a);
  ck_assert(*(int *)list_front(l) == b);
  ck_assert(*(int *)list_begin(l)->data == b);
  ck_assert(list_end() == NULL);  

  list_pop_front(l, standart_destructor);
  ck_assert(!list_empty(l));
  ck_assert(list_size(l) == 1);
  ck_assert(*(int *)list_back(l) == a);
  ck_assert(*(int *)list_front(l) == a);
  ck_assert(*(int *)list_begin(l)->data == a);
  ck_assert(list_end() == NULL);

  list_clear(l, standart_destructor);
  ck_assert(list_empty(l));
  ck_assert(list_size(l) == 0);
  ck_assert(list_size(l) == 0);
  ck_assert(list_back(l) == NULL);
  ck_assert(list_front(l) == NULL);
  ck_assert(list_begin(l) == NULL);
  ck_assert(list_end() == NULL);  

  int i;
  int arr[1000] = {0};
  for(i = 0; i < 1000; i++)
  {
    arr[i] = i;
    list_emplace_back(l, arr + i);
    ck_assert(!list_empty(l));
    ck_assert(list_size(l) == (size_t)(arr[i] + 1));
    ck_assert_uint_eq(*(int *)list_back(l), arr[i]);
    ck_assert_uint_eq(*(int *)list_front(l), 0);
    ck_assert(list_begin(l)->data == (dptr)arr);
    ck_assert(list_end() == NULL);    
  }

  for(i = 999; i > 0; i--)
  {
    ck_assert(!list_empty(l));
    list_pop_back(l, standart_destructor);
    ck_assert(list_size(l) == (size_t)arr[i]);
    ck_assert_uint_eq(*(int *)list_back(l), arr[i] - 1);
    ck_assert(*(int *)list_front(l) == 0);
    ck_assert(list_begin(l)->data == (dptr)arr);
    ck_assert(list_end() == NULL);    
  }

  list_pop_back(l, standart_destructor);
  ck_assert(list_empty(l));
  ck_assert(list_size(l) == 0);
  ck_assert(list_back(l) == NULL);
  ck_assert(list_front(l) == NULL);
  ck_assert(list_begin(l) == NULL);
  ck_assert(list_end() == NULL); 

  for(int i = 0; i < 1000; i++)
    arr[i] = 0;

  for(i = 0; i < 1000; i++)
  {
    arr[i] = i;
    list_emplace_front(l, arr + i);
    ck_assert(!list_empty(l));
    ck_assert(list_size(l) == (size_t)(arr[i] + 1));
    ck_assert_uint_eq(*(int *)list_back(l), 0);
    ck_assert_uint_eq(*(int *)list_front(l), i);
    ck_assert_ptr_eq(list_begin(l)->data, (dptr)(arr + i));
    ck_assert(list_end() == NULL);    
  }

  for(i = 999; i > 0; i--)
  {
    list_pop_front(l, standart_destructor);
    ck_assert(!list_empty(l));
    ck_assert(list_size(l) == (size_t)arr[i]);
    ck_assert_uint_eq(*(int *)list_back(l), 0);
    ck_assert(*(int *)list_front(l) == arr[i] - 1);
    ck_assert(list_begin(l)->data == (dptr)(arr + i - 1));
    ck_assert(list_end() == NULL);    
  }

  list_pop_back(l, standart_destructor);
  ck_assert(list_empty(l));
  ck_assert(list_size(l) == 0);
  ck_assert(list_back(l) == NULL);
  ck_assert(list_front(l) == NULL);
  ck_assert(list_begin(l) == NULL);
  ck_assert(list_end() == NULL); 


  list_destroy(l, standart_destructor);
}


Suite *suite_list()
{
  Suite *s;
  TCase *tc;

  s = suite_create ("List test");
  tc = tcase_create ("List test");

  tcase_add_test (tc, list_test_1);
  tcase_add_test (tc, list_test_2);
  tcase_add_test (tc, list_test_3);
  tcase_add_test (tc, list_test_4);
  tcase_add_test (tc, list_test_5);

  suite_add_tcase (s, tc);

  return s;
}