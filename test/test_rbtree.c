#include "test.h"
#include <check.h>
#include <stdbool.h>

static int
cmp (constdptr first, constdptr second)
{
  return *(int *)first - *(int *)second;
}

START_TEST (rbtree_test_1)
{
  rbtree *tree = rbtree_create (cmp, NULL, false);

  int arr[9] = { 1, 2, 3, 4, 5, 6, 7, 9, 8 };

  for (int i = 0; i < 9; i++)
    {
      rbtree_insert (tree, arr + i);
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
      rbtree_remove (tree, arr + i);
    }

  rbtree_destoy (tree);
}

START_TEST (rbtree_test_2)
{
  rbtree *tree = rbtree_create (cmp, NULL, false);

  int arr[9] = { 2, 1, 3, 4, 5, 6, 7, 8, 9 };

  for (int i = 8; i >= 0; i--)
    {
      rbtree_insert (tree, arr + i);
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

  rbtree_destoy (tree);
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

  suite_add_tcase (s, tc);

  return s;
}
