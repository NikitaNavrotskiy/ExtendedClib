#include "map.h"
#include "rbtree.h"
#include "types.h"

/*
 * @brief Need to make fake pair from
 * just key for compare.
 */
#define __MAP_FAKE_PAIR(key, var_name)                                        \
  struct pair var_name = { 0 };                                               \
  var_name.key = (dptr)key;

map *
map_create (int (*cmp) (constdptr first, constdptr second),
            void (*destr) (dptr pair))
{
  map *mp = (map *)malloc (sizeof (map));

  mp->tree = rbtree_create (cmp, destr, false);

  if (!destr)
    mp->tree->destr = pair_destroy_default;

  return mp;
}

dptr
map_at (const map *mp, constdptr key)
{
  __MAP_FAKE_PAIR (key, pr);

  map_iterator iter = map_find (mp, &pr);

  if (!iter)
    return NULL;

  return ((struct pair *)(iter->data))->value;
}

inline map_iterator
map_begin (const map *mp)
{
  if (!mp)
    return NULL;

  return rbtree_begin (mp->tree);
}

inline map_iterator
map_rbegin (const map *mp)
{
  if (!mp)
    return NULL;

  return rbtree_rbegin (mp->tree);
}

inline void
map_clear (map *mp)
{
  if (!mp)
    return;

  rbtree_clear (mp->tree);
}

inline bool
map_contains (const map *mp, constdptr key)
{
  if (!mp)
    return false;

  __MAP_FAKE_PAIR (key, pr);
  return rbtree_contains (mp->tree, &pr);
}

inline size_t
map_count (const map *mp, constdptr key)
{
  if (!mp)
    return 0;

  __MAP_FAKE_PAIR (key, pr);

  return rbtree_count (mp->tree, &pr);
}

inline void
map_destroy (map *mp)
{
  if (!mp)
    return;

  rbtree_destroy (mp->tree);
}

inline map_iterator
map_insert (map *mp, constdptr key, constdptr value)
{
  if (!mp)
    return NULL;

  struct pair *pr = pair_create (key, value);

  return rbtree_insert (mp->tree, pr);
}

inline map_iterator
map_end ()
{
  return NULL;
}

inline map_iterator
map_rend ()
{
  return NULL;
}

inline map_iterator
map_erase (map *mp, map_iterator iter)
{
  if (!mp)
    return NULL;

  return rbtree_erase (mp->tree, iter);
}

inline bool
map_empty (map *mp)
{
  if (!mp)
    return true;

  return rbtree_empty (mp->tree);
}

inline map_iterator
map_find (const map *mp, constdptr key)
{
  if (!mp)
    return NULL;

  __MAP_FAKE_PAIR (key, pr);

  return rbtree_find (mp->tree, &pr);
}

inline void
map_remove (map *mp, constdptr key)
{
  if (!mp)
    return;

  __MAP_FAKE_PAIR (key, pr);

  rbtree_remove (mp->tree, &pr);
}

inline size_t
map_size (const map *mp)
{
  if (!mp)
    return 0;

  return rbtree_size (mp->tree);
}

inline map_iterator
map_next (const_map_iterator iter)
{
  return rbtree_next (iter);
}

inline map_iterator
map_prev (const_map_iterator iter)
{
  return rbtree_prev (iter);
}
