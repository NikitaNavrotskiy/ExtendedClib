#include "set.h"
#include "rbtree.h"

////////////////////////////////////////////////////
/*       Public API functions of the Set          */
////////////////////////////////////////////////////

set *
set_create (int (*cmp) (constdptr first, constdptr second),
            void (*destr) (dptr data))
{
  set *st = (set *)malloc (sizeof (set));

  st->tree = rbtree_create (cmp, destr, false);

  return st;
}

inline set_iterator
set_begin (const set *st)
{
  if (!st)
    return NULL;
  return rbtree_begin (st->tree);
}

inline set_iterator
set_rbegin (const set *st)
{
  if (!st)
    return NULL;
  return rbtree_rbegin (st->tree);
}

inline void
set_clear (set *st)
{
  if (!st)
    return;
  rbtree_clear (st->tree);
}

inline bool
set_contains (const set *st, constdptr data)
{
  if (!st)
    return false;
  return rbtree_contains (st->tree, data);
}

size_t
set_count (const set *st, constdptr data)
{
  if (!st)
    return 0;

  return rbtree_count (st->tree, data);
}

inline void
set_destroy (set *st)
{
  if (!st)
    return;

  rbtree_destroy (st->tree);
  free (st);
}

inline set_iterator
set_insert (set *st, constdptr data)
{
  if (!st)
    return NULL;

  return rbtree_insert (st->tree, data);
}

inline set_iterator
set_end ()
{
  return rbtree_end ();
}

inline set_iterator
set_rend ()
{
  return rbtree_rend ();
}

inline set_iterator
set_erase (set *st, set_iterator iter)
{
  if (!st)
    return NULL;

  return rbtree_erase (st->tree, iter);
}

inline bool
set_empty (set *st)
{
  if (!st)
    return true;

  return rbtree_empty (st->tree);
}

inline set_iterator
set_find (const set *st, constdptr data)
{
  if (!st)
    return NULL;

  return rbtree_find (st->tree, data);
}

inline void
set_remove (set *st, constdptr data)
{
  set_erase (st, set_find (st, data));
}

inline size_t
set_size (const set *st)
{
  if (!st)
    return 0;

  return rbtree_size (st->tree);
}

inline set_iterator
set_next (const_set_iterator iter)
{
  return rbtree_next (iter);
}

inline set_iterator
set_prev (const_set_iterator iter)
{
  return rbtree_prev (iter);
}
