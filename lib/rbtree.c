#include "rbtree.h"

////////////////////////////////////////////////////
/*    Private functions of the Red-black Tree     */
////////////////////////////////////////////////////

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
