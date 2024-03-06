/**
 * @file types.c Implementation of types functions.
 */

#include "types.h"

#include <stdlib.h>

/**
 * @brief Implementation of do_node functions.
 */

struct do_node *
__do_node_create (constdptr data, struct do_node *next, struct do_node *prev)
{
  struct do_node *nd = (struct do_node *)malloc (sizeof (struct do_node));

  nd->next = next;
  nd->data = (dptr)data;
  nd->prev = prev;

  return nd;
}

inline __attribute__ ((always_inline)) void
__do_node_destroy (struct do_node *node, void (*destr) (dptr data))
{
  if (destr)
    destr (node->data);
  free (node);
}

inline dptr
do_node_get (const struct do_node *nd)
{
  if (nd)
    return nd->data;
  return NULL;
}

/**
 * @brief Implementation of o_node functions.
 */

struct o_node *
__o_node_create (constdptr data, struct o_node *next)
{
  struct o_node *nd = (struct o_node *)malloc (sizeof (struct o_node));

  nd->next = next;
  nd->data = (dptr)data;

  return nd;
}

inline __attribute__ ((always_inline)) void
__o_node_destroy (struct o_node *node, void (*destr) (dptr data))
{
  if (destr)
    destr (node->data);
  free (node);
}

inline dptr
o_node_get (const struct o_node *nd)
{
  if (nd)
    return nd->data;
  return NULL;
}