#include "rbtree.h"
#include <stdbool.h>

////////////////////////////////////////////////////
/*    Private functions of the Red-black Tree     */
////////////////////////////////////////////////////

/**
 * @brief Little swap macroses
 */
#define __RBNODE_SWAP(a, b)                                                   \
  do                                                                          \
    {                                                                         \
      struct __rbt_node *tmp = a;                                             \
      a = b;                                                                  \
      b = tmp;                                                                \
    }                                                                         \
  while (0)

#define __RBNODE_VALUES_SWAP(a, b)                                            \
  do                                                                          \
    {                                                                         \
      dptr tmp = a->data;                                                     \
      a->data = b->data;                                                      \
      b->data = tmp;                                                          \
    }                                                                         \
  while (0)

static void __rbtree_balance_on_erase (rbtree *tree, struct __rbt_node *del,
                                       bool flag_not_recurs_call);

/**
 * @brief Function to create rbtree node.
 *
 * @param data Data of new element.
 * @param left Pointer to the left child.
 * @param right Pointer to the right child.
 * @param parent Pointer to the parent.
 * @param is_red Color flag.
 */
static struct __rbt_node *
__rbt_node_create (constdptr data, dptr left, dptr right, dptr parent,
                   bool is_red)
{
  struct __rbt_node *nd
      = (struct __rbt_node *)malloc (sizeof (struct __rbt_node));

  nd->left = left;
  nd->right = right;
  nd->data = (dptr)data;
  nd->parent = parent;
  nd->is_red = is_red;

  return nd;
}

/**
 * @brief Function to destroy node with given destructor.
 *
 * @param nd rbtree node to destroy.
 * @param destr - Destructor function.
 */
inline static void
__rbt_node_destroy (struct __rbt_node *nd, void (*destr) (dptr data))
{
  if (destr)
    destr (nd->data);

  free (nd);
}

#ifdef DEBUG

bool
__rbtree_is_root_black (struct __rbt_node *root)
{
  if (!root)
    return true;
  return root->is_red == false;
}

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
  int right_height = __rbtree_black_height (nd->right);

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

  return __rbtree_is_black_height_same (tree->root)
         && __rbtree_is_no_red_red (tree->root)
         && __rbtree_is_root_black (tree->root)
         && __rbtree_is_bst (tree, tree->root);
}

#endif // DEBUG

/**
 * @brief Function to destroy rbtree recursively.
 *
 * @param root Node that is root in this context.
 * @param destr Destructor function.
 */
static void
__rbtree_recursive_destroy (struct __rbt_node *root, void (*destr) (dptr data))
{
  if (!root)
    return;
  __rbtree_recursive_destroy (root->left, destr);
  __rbtree_recursive_destroy (root->right, destr);

  __rbt_node_destroy (root, destr);
}

/**
 * @brief Funciton to find element recursively.
 *
 * @param tree Pointer to the Red-black tree instanse.
 * @param root Local root node.
 * @param data Data to find.
 * @return rbtree_iterator Iterator to found element
 * or Null iterator if has not found.
 */
static rbtree_iterator
__rbtree_recursive_find (const rbtree *tree, struct __rbt_node *root,
                         constdptr data)
{
  if (!root)
    return NULL;

  int cmp_res = tree->cmp (root->data, data);

  if (cmp_res == 0)
    return root;
  else if (cmp_res <= 0)
    return __rbtree_recursive_find (tree, root->right, data);
  return __rbtree_recursive_find (tree, root->left, data);
}

/**
 * @brief Function to make left rotate relatively
 * given root (root->right will be new local root).
 *
 * @param tree Pointer to Red-black Tree instanse.
 * @param root Pointer to local root node.
 */
static void
__rbtree_left_rotate (rbtree *tree, struct __rbt_node *root)
{
  // Saving reference to right child of local root.
  struct __rbt_node *right_child = root->right;

  // Moving new right child for the root.
  root->right = right_child->left;

  // If new right child of root is not null,
  // Making reference to his new parent.
  if (right_child->left)
    right_child->left->parent = root;

  // changing parent of right subtree.
  right_child->parent = root->parent;

  // If new root does not have parents =>
  // this node is new root of entire rbtree,
  // else Making right references of upper level
  // parent.
  if (root->parent)
    {
      if (root->parent->left == root)
        root->parent->left = right_child;
      else
        root->parent->right = right_child;
    }
  else
    tree->root = right_child;

  // Making new left child for new local root.
  // and new parent for new root.
  right_child->left = root;
  root->parent = right_child;
}

/**
 * @brief Function to make right rotate relatively
 * given root (root->left will be new local root).
 *
 * @param tree Pointer to Red-black Tree instanse.
 * @param root Pointer to local root node.
 */
static void
__rbtree_right_rotate (rbtree *tree, struct __rbt_node *root)
{
  // Saving reference to left child of local root.
  struct __rbt_node *left_child = root->left;

  // Moving new left child for the root.
  root->left = left_child->right;

  // If new left child of root is not null,
  // Making reference to his new parent.
  if (left_child->right)
    left_child->right->parent = root;

  // changing parent of left subtree.
  left_child->parent = root->parent;

  // If new root does not have parents =>
  // this node is new root of entire rbtree,
  // else Making right references of upper level
  // parent.
  if (root->parent)
    {
      if (root->parent->right == root)
        root->parent->right = left_child;
      else
        root->parent->left = left_child;
    }
  else
    tree->root = left_child;

  // Making new left child for new local root.
  // and new parent for new root.
  left_child->right = root;
  root->parent = left_child;
}

/**
 * @brief Function to get minimum (the most left child).
 *
 * @param root Local root node.
 * @return struct __rbt_node * Pointer to corresponding
 * node.
 */
static struct __rbt_node *
__rbtree_get_min (struct __rbt_node *root)
{
  if (!root)
    return NULL;

  struct __rbt_node *tmp = root;

  while (tmp->left)
    tmp = tmp->left;

  return tmp;
}

/**
 * @brief Function to get maximum (the most right child).
 *
 * @param root Local root node.
 * @return struct __rbt_node * Pointer to corresponding
 * node.
 */
static struct __rbt_node *
__rbtree_get_max (struct __rbt_node *root)
{
  if (!root)
    return NULL;

  struct __rbt_node *tmp = root;

  while (tmp->right)
    tmp = tmp->right;

  return tmp;
}

static rbtree_iterator
__rbtree_balance_on_insert (rbtree *tree, rbtree_iterator nd)
{
  rbtree_iterator res = nd;
  struct __rbt_node *parent = nd->parent;

  while (nd != tree->root && parent->is_red)
    {
      struct __rbt_node *grandparent = parent->parent;

      if (grandparent->left == parent)
        {
          struct __rbt_node *uncle = grandparent->right;

          if (uncle && uncle->is_red)
            {
              parent->is_red = false;
              uncle->is_red = false;
              grandparent->is_red = true;

              nd = grandparent;
              parent = nd->parent;
            }
          else
            {
              if (parent->right == nd)
                {
                  __rbtree_left_rotate (tree, parent);
                  __RBNODE_SWAP (nd, parent);
                  res = parent;
                }

              __rbtree_right_rotate (tree, grandparent);
              grandparent->is_red = true;
              parent->is_red = false;

              break;
            }
        }
      else
        {
          struct __rbt_node *uncle = grandparent->left;

          if (uncle && uncle->is_red)
            {
              parent->is_red = false;
              uncle->is_red = false;
              grandparent->is_red = true;

              nd = grandparent;
              parent = nd->parent;
            }
          else
            {
              if (parent->left == nd)
                {
                  __rbtree_right_rotate (tree, parent);
                  __RBNODE_SWAP (nd, parent);
                  res = parent;
                }

              __rbtree_left_rotate (tree, grandparent);
              grandparent->is_red = true;
              parent->is_red = false;

              break;
            }
        }
    }

  tree->root->is_red = false;

  return res;
}

static rbtree_iterator
__rbtree_insert_without_balance (rbtree *tree, constdptr data)
{
  struct __rbt_node *cur = tree->root, *prev = NULL;
  bool dont_insert = false;

  while (cur)
    {
      prev = cur;

      int cmp_res = tree->cmp (cur->data, data);

      if (cmp_res < 0)
        cur = cur->right;
      else if (cmp_res > 0)
        cur = cur->left;
      else if (!tree->allow_same)
        {
          dont_insert = true;
          break;
        }
      else
        cur = cur->right;
    }

  if (!dont_insert)
    {
      struct __rbt_node *new_node
          = __rbt_node_create (data, NULL, NULL, prev, true);

      if (prev)
        {
          if (tree->cmp (new_node->data, prev->data) < 0)
            prev->left = new_node;
          else
            prev->right = new_node;
        }
      else
        {
          tree->root = new_node;
        }

      return new_node;
    }

  return NULL;
}

static void
__rbtree_balance_on_erase_left (rbtree *tree, struct __rbt_node *del,
                                bool flag_not_recurs_call)
{
  struct __rbt_node *parent = del->parent;
  struct __rbt_node *sibling = parent->right;

  if (sibling->is_red)
    {
      parent->is_red = true;
      sibling->is_red = false;
      __rbtree_left_rotate (tree, parent);
      parent = sibling->left;
      sibling = parent->right;
    }

  if (!sibling->right || !sibling->right->is_red)
    {
      if (!sibling->left || !sibling->left->is_red)
        {
          bool is_red_parent = parent->is_red;
          sibling->is_red = true;
          parent->is_red = false;

          if (is_red_parent)
            return;

          __rbtree_balance_on_erase (tree, parent, flag_not_recurs_call);
          return;
        }
      sibling->left->is_red = false;
      sibling->is_red = true;
      __rbtree_right_rotate (tree, sibling);
      sibling = sibling->parent;
    }

  if (sibling->right && sibling->right->is_red)
    {
      sibling->right->is_red = false;
      sibling->is_red = parent->is_red;
      parent->is_red = false;
      __rbtree_left_rotate (tree, parent);
      return;
    }
}

static void
__rbtree_balance_on_erase_right (rbtree *tree, struct __rbt_node *del,
                                 bool flag_not_recurs_call)
{
  struct __rbt_node *parent = del->parent;
  struct __rbt_node *sibling = parent->left;

  if (sibling->is_red)
    {
      parent->is_red = true;
      sibling->is_red = false;
      __rbtree_right_rotate (tree, parent);
      parent = sibling->right;
      sibling = parent->left;
    }

  if (!sibling->left || !sibling->left->is_red)
    {
      if (!sibling->right || !sibling->right->is_red)
        {
          bool is_red_parent = parent->is_red;
          sibling->is_red = true;
          parent->is_red = false;

          if (is_red_parent)
            return;

          __rbtree_balance_on_erase (tree, parent, flag_not_recurs_call);
          return;
        }
      sibling->right->is_red = false;
      sibling->is_red = true;
      __rbtree_left_rotate (tree, sibling);
      sibling = sibling->parent;
    }

  if (sibling->left && sibling->left->is_red)
    {
      sibling->left->is_red = false;
      sibling->is_red = parent->is_red;
      parent->is_red = false;
      __rbtree_right_rotate (tree, parent);
      return;
    }
}

void
__rbtree_balance_on_erase (rbtree *tree, struct __rbt_node *del,
                           bool flag_not_recurs_call)
{
  if (del->is_red || del == tree->root)
    return;

  if (del->parent)
    {
      if (del->parent->left == del)
        {
          if (flag_not_recurs_call)
            del->parent->left = del->left;
          __rbtree_balance_on_erase_left (tree, del, false);
        }
      else if (del->parent->right == del)
        {
          if (flag_not_recurs_call)
            del->parent->right = del->right;
          __rbtree_balance_on_erase_right (tree, del, false);
        }
    }
}

static rbtree_iterator
__rbtree_erase_handler (rbtree *tree, rbtree_iterator iter)
{
  rbtree_iterator res = NULL;

  struct __rbt_node *replace = NULL;

  if (iter->right && iter->left)
    {
      replace = __rbtree_get_max (iter->left);
      __RBNODE_VALUES_SWAP (iter, replace);
    }
  else if (iter->right && iter->right->is_red)
    {
      replace = iter->right;
      __RBNODE_VALUES_SWAP (iter, replace);
    }
  else if (iter->left && iter->left->is_red)
    {
      replace = iter->left;
      __RBNODE_VALUES_SWAP (iter, replace);
    }
  else
    replace = iter;

  res = replace->right != NULL ? __rbtree_get_min (replace->right)
                               : replace->parent;

  if (replace->is_red)
    {
      if (replace->right == NULL && replace->left == NULL)
        {
          if (replace->parent)
            {
              if (replace->parent->left == replace)
                replace->parent->left = NULL;
              else if (replace->parent->right == replace)
                replace->parent->right = NULL;
            }
          __rbt_node_destroy (replace, tree->destr);
          tree->size--;
        }
    }
  else
    {
      if (replace == tree->root)
        {
          tree->root = NULL;
          __rbt_node_destroy (replace, tree->destr);
        }
      else if (replace->left)
        {
          __RBNODE_VALUES_SWAP (replace, replace->left);
          __rbt_node_destroy (replace->left, tree->destr);
          replace->left = NULL;
        }
      else
        {
          __rbtree_balance_on_erase (tree, replace, true);
          __rbt_node_destroy (replace, tree->destr);
        }
      tree->size--;
    }
  return res;
}

////////////////////////////////////////////////////
/*   Public API functions of the Red-black Tree    */
////////////////////////////////////////////////////

rbtree *
rbtree_create (int (*cmp) (constdptr first, constdptr second),
               void (*destr) (dptr data), bool allow_same)
{
  rbtree *tree = (rbtree *)malloc (sizeof (rbtree));

  tree->root = NULL;
  tree->size = 0;
  tree->cmp = cmp;
  tree->destr = destr;
  tree->allow_same = allow_same;

  return tree;
}

rbtree_iterator
rbtree_begin (const rbtree *tree)
{
  if (!tree)
    return NULL;

  return __rbtree_get_min (tree->root);
}

inline rbtree_iterator
rbtree_rbegin (const rbtree *tree)
{
  if (!tree)
    return NULL;

  return __rbtree_get_max (tree->root);
}

inline void
rbtree_clear (rbtree *tree)
{
  if (tree)
    __rbtree_recursive_destroy (tree->root, tree->destr);

  tree->root = NULL;
  tree->size = 0;
}

inline bool
rbtree_contains (const rbtree *tree, constdptr data)
{
  return rbtree_find (tree, data) != NULL;
}

size_t rbtree_count (const rbtree *tree, constdptr data);

inline void
rbtree_destroy (rbtree *tree)
{
  if (tree)
    __rbtree_recursive_destroy (tree->root, tree->destr);

  free (tree);
}

rbtree_iterator
rbtree_insert (rbtree *tree, constdptr data)
{
  if (!tree)
    return NULL;

  rbtree_iterator inserted_node = __rbtree_insert_without_balance (tree, data);

  if (inserted_node)
    {
      inserted_node = __rbtree_balance_on_insert (tree, inserted_node);
      tree->size++;
    }

  return inserted_node;
}

inline rbtree_iterator
rbtree_end ()
{
  return NULL;
}

inline rbtree_iterator
rbtree_rend ()
{
  return NULL;
}

rbtree_iterator
rbtree_erase (rbtree *tree, rbtree_iterator iter)
{
  if (!tree || !iter)
    return NULL;
  return __rbtree_erase_handler (tree, iter);
}

inline bool
rbtree_empty (rbtree *tree)
{
  if (!tree)
    return true;
  return rbtree_size (tree) == 0;
}

inline rbtree_iterator
rbtree_find (const rbtree *tree, constdptr data)
{
  if (!tree)
    return NULL;
  return __rbtree_recursive_find (tree, tree->root, data);
}

inline void
rbtree_remove (rbtree *tree, constdptr data)
{
  rbtree_erase (tree, rbtree_find (tree, data));
}

inline size_t
rbtree_size (const rbtree *tree)
{
  if (!tree)
    return 0;

  return tree->size;
}

rbtree_iterator
rbtree_next (const_rbtree_iterator iter)
{
  if (!iter)
    return NULL;

  if (iter->right)
    return __rbtree_get_min (iter->right);

  rbtree_iterator parent = iter->parent;
  rbtree_iterator cur = (rbtree_iterator)iter;

  while (parent && cur == parent->right)
    {
      cur = parent;
      parent = parent->parent;
    }

  return parent;
}

rbtree_iterator
rbtree_prev (const_rbtree_iterator iter)
{
  if (!iter)
    return NULL;

  if (iter->left)
    return __rbtree_get_max (iter->left);

  rbtree_iterator parent = iter->parent;
  rbtree_iterator cur = (rbtree_iterator)iter;

  while (parent && cur == parent->left)
    {
      cur = parent;
      parent = parent->parent;
    }

  return parent;
}
