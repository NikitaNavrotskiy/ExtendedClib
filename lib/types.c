#include "types.h"

#include <stdlib.h>

/**
 * @brief Implementation of do_node functions.
 */

struct do_node *
__do_node_create (dataptr data, struct do_node *next, struct do_node *prev)
{
  struct do_node *nd = (struct do_node *)malloc (sizeof (struct do_node));

  nd->next = next;
  nd->data = data;
  nd->prev = prev;

  return nd;
}

inline void
__do_node_destroy (struct do_node *node)
{
  free (node);
}

inline dataptr
do_node_get (const struct do_node *nd)
{
  return nd->data;
}

/**
 * @brief Implementation of o_node functions.
 */

struct o_node *
__o_node_create (dataptr data, struct o_node *next)
{
  struct o_node *nd = (struct o_node *)malloc (sizeof (struct o_node));

  nd->next = next;
  nd->data = data;

  return nd;
}

inline void
__o_node_destroy (struct o_node *node)
{
  free (node);
}

inline dataptr
o_node_get (const struct o_node *nd)
{
  return nd->data;
}