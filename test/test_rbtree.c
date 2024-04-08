#include "test.h"
#include <check.h>
#include <stdbool.h>
#include <strings.h>

bool
__rbtree_is_bst (rbtree *tree, struct __rbt_node *root)
{
  if (!root)
    return true;

  return ((!root->left || tree->cmp (root->data, root->left->data) >= 0)
          && (!root->right || tree->cmp (root->data, root->right->data) <= 0))
         && __rbtree_is_bst (tree, root->left)
         && __rbtree_is_bst (tree, root->right);
}

bool
__rbtree_is_no_red_red (struct __rbt_node *root)
{
  if (!root)
    return true;

  if (root->is_red
      && ((root->left != NULL && root->left->is_red)
          || (root->right != NULL && root->right->is_red)))
    return false;

  return __rbtree_is_no_red_red (root->left)
         && __rbtree_is_no_red_red (root->right);
}

int
__rbtree_black_height (struct __rbt_node *nd)
{
  if (nd == NULL)
    return 1;

  int left_height = __rbtree_black_height (nd->left);
  // int right_height = __rbtree_black_height (nd->right);

  if (nd->is_red == false)
    return 1 + left_height;
  return left_height;
}

bool
__rbtree_is_black_height_same (struct __rbt_node *root)
{
  if (!root)
    return true;

  bool left = __rbtree_is_black_height_same (root->left);
  bool right = __rbtree_is_black_height_same (root->right);

  if (left && right
      && __rbtree_black_height (root->left)
             == __rbtree_black_height (root->right))
    return true;
  return false;
}

bool
__rbtree_is_correct (rbtree *tree)
{
  if (!tree->root)
    return true;

  return (!tree->root || !tree->root->is_red)
         && __rbtree_is_black_height_same (tree->root)
         && __rbtree_is_no_red_red (tree->root)
         && __rbtree_is_bst (tree, tree->root);
}

static int
cmp (constdptr first, constdptr second)
{
  return *(int *)first - *(int *)second;
}

static void
destr (dptr data)
{
  data = data;
}

START_TEST (rbtree_test_1)
{
  rbtree *tree = rbtree_create (cmp, NULL, false);

  int arr[9] = { 1, 2, 3, 4, 5, 6, 7, 9, 8 };

  for (int i = 0; i < 9; i++)
    {
      ck_assert_int_eq (*(int *)rbtree_insert (tree, arr + i)->data, arr[i]);
      ck_assert (__rbtree_is_correct (tree));
      ck_assert (rbtree_size (tree) == (size_t)(i + 1));
    }

  ck_assert (tree->root->is_red == false);
  ck_assert (tree->root->data == arr + 3);

  ck_assert (tree->root->left->is_red == true);
  ck_assert (tree->root->left->data == arr + 1);

  ck_assert (tree->root->right->is_red == true);
  ck_assert (tree->root->right->data == arr + 5);

  ck_assert (tree->root->left->left->is_red == false);
  ck_assert (tree->root->left->left->data == arr);

  ck_assert (tree->root->left->right->is_red == false);
  ck_assert (tree->root->left->right->data == arr + 2);

  ck_assert (tree->root->right->left->is_red == false);
  ck_assert (tree->root->right->left->data == arr + 4);

  ck_assert (tree->root->right->right->is_red == false);
  ck_assert (tree->root->right->right->data == arr + 8);

  ck_assert (tree->root->right->right->left->is_red == true);
  ck_assert (tree->root->right->right->left->data == arr + 6);

  ck_assert (tree->root->right->right->right->is_red == true);
  ck_assert (tree->root->right->right->right->data == arr + 7);

  for (int i = 0; i < 9; i++)
    {
      rbtree_iterator del = rbtree_find (tree, arr + i);
      rbtree_iterator res = rbtree_erase (tree, del);
      //  if (i == 8)
      //   ck_assert (res == NULL);
      //  else
      //    ck_assert (res->data == arr + i + 1);
      res = res;
      ck_assert (__rbtree_is_correct (tree));
      ck_assert (rbtree_size (tree) == (size_t)(8 - i));
    }

  rbtree_destroy (tree);
}

START_TEST (rbtree_test_2)
{
  rbtree *tree = rbtree_create (cmp, NULL, false);

  int arr[9] = { 2, 1, 3, 4, 5, 6, 7, 8, 9 };

  for (int i = 8; i >= 0; i--)
    {
      rbtree_insert (tree, arr + i);
      ck_assert (__rbtree_is_correct (tree));
    }

  ck_assert (tree->root->is_red == false);
  ck_assert (tree->root->data == arr + 5);

  ck_assert (tree->root->left->is_red == true);
  ck_assert (tree->root->left->data == arr + 3);

  ck_assert (tree->root->right->is_red == true);
  ck_assert (tree->root->right->data == arr + 7);

  ck_assert (tree->root->left->left->is_red == false);
  ck_assert (tree->root->left->left->data == arr);

  ck_assert (tree->root->left->right->is_red == false);
  ck_assert (tree->root->left->right->data == arr + 4);

  ck_assert (tree->root->right->left->is_red == false);
  ck_assert (tree->root->right->left->data == arr + 6);

  ck_assert (tree->root->right->right->is_red == false);
  ck_assert (tree->root->right->right->data == arr + 8);

  ck_assert (tree->root->left->left->left->is_red == true);
  ck_assert (tree->root->left->left->left->data == arr + 1);

  ck_assert (tree->root->left->left->right->is_red == true);
  ck_assert (tree->root->left->left->right->data == arr + 2);

  for (int i = 8; i >= 0; i--)
    {
      rbtree_remove (tree, arr + i);
      ck_assert (__rbtree_is_correct (tree));
    }

  rbtree_destroy (tree);
}

START_TEST (rbtree_test_3)
{
  rbtree *tree = rbtree_create (cmp, NULL, false);
  int arr[100];

  for (int j = 0; j < 20; j++)
    {
      for (int i = 0; i < 100; i++)
        {
          int randint = rand ();
          arr[i] = randint;
        }

      for (int i = 0; i < 100; i++)
        {
          rbtree_insert (tree, arr + i);
          ck_assert (__rbtree_is_correct (tree));
          ck_assert (rbtree_contains (tree, arr + i));
          ck_assert (rbtree_size (tree) == (size_t)i + 1);
        }
      rbtree_iterator prev = rbtree_begin (tree);
      for (rbtree_iterator beg = rbtree_begin (tree); beg != rbtree_end ();
           beg = rbtree_next (beg))
        {
          ck_assert (tree->cmp (prev->data, beg->data) <= 0);
          prev = beg;
        }

      prev = rbtree_rbegin (tree);
      for (rbtree_iterator beg = rbtree_rbegin (tree); beg != rbtree_rend ();
           beg = rbtree_prev (beg))
        {
          ck_assert (tree->cmp (prev->data, beg->data) >= 0);
          prev = beg;
        }

      size_t count = rbtree_size (tree);
      while (tree->root)
        {
          int index = rand () % 100;
          rbtree_iterator tmp = rbtree_find (tree, arr + index);

          if (tmp)
            {
              rbtree_remove (tree, arr + index);
              ck_assert (tree->size == count - 1);
              count = tree->size;
            }
          ck_assert (__rbtree_is_correct (tree));
        }
    }

  rbtree_destroy (tree);
}

START_TEST (rbtree_test_4)
{
  rbtree *tree = rbtree_create (cmp, destr, true);
  int arr[100];

  for (int j = 0; j < 20; j++)
    {
      for (int i = 0; i < 100; i++)
        {
          int randint = rand () % 100;
          arr[i] = randint;
        }

      for (int i = 0; i < 100; i++)
        {
          rbtree_insert (tree, arr + i);
          ck_assert (__rbtree_is_correct (tree));
          ck_assert (rbtree_contains (tree, arr + i));
          ck_assert (rbtree_size (tree) == (size_t)i + 1);
        }
      rbtree_iterator prev = rbtree_begin (tree);
      for (rbtree_iterator beg = rbtree_begin (tree); beg != rbtree_end ();
           beg = rbtree_next (beg))
        {
          ck_assert (tree->cmp (prev->data, beg->data) <= 0);
          prev = beg;
        }

      prev = rbtree_rbegin (tree);
      for (rbtree_iterator beg = rbtree_rbegin (tree); beg != rbtree_rend ();
           beg = rbtree_prev (beg))
        {
          ck_assert (tree->cmp (prev->data, beg->data) >= 0);
          prev = beg;
        }

      size_t count = rbtree_size (tree);
      while (tree->root)
        {
          int index = rand () % 100;
          rbtree_iterator tmp = rbtree_find (tree, arr + index);

          if (tmp)
            {
              rbtree_remove (tree, arr + index);
              ck_assert (tree->size == count - 1);
              count = tree->size;
            }
          ck_assert (__rbtree_is_correct (tree));
        }
    }

  rbtree_destroy (tree);
}

START_TEST (rbtree_test_5)
{
  rbtree *tree = rbtree_create (cmp, destr, false);

  int arr[9] = { 2, 1, 3, 4, 5, 6, 7, 8, 9 };

  for (int i = 8; i >= 0; i--)
    {
      rbtree_insert (tree, arr + i);
      ck_assert (__rbtree_is_correct (tree));
    }

  rbtree_clear (tree);
  ck_assert (tree->size == 0);
  ck_assert (rbtree_empty (tree));

  rbtree_destroy (tree);
}

Suite *
suite_rbtree ()
{
  Suite *s;
  TCase *tc;

  s = suite_create ("Red-black Tree test");
  tc = tcase_create ("Red-black Tree test");

  tcase_add_test (tc, rbtree_test_1);
  tcase_add_test (tc, rbtree_test_2);
  tcase_add_test (tc, rbtree_test_3);
  tcase_add_test (tc, rbtree_test_4);
  tcase_add_test (tc, rbtree_test_5);

  suite_add_tcase (s, tc);

  return s;
}
