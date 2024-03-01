/**
 * @file Implementation of stack's API functions.
 */

#include "stack.h"

stack *
stack_create ()
{
  stack *st = (stack *)malloc (sizeof (stack));

  st->size = 0;
  st->top = NULL;

  return st;
}

void
stack_push (stack *s, dataptr data)
{
  s->top = __o_node_create (data, s->top);
  s->size++;
}

void
stack_pop (stack *s)
{
  /* Save old top to not lose references. */
  struct o_node *tmp = s->top;

  /* Changing top. */
  s->top = tmp->next;
  s->size--;

  /* Destroy old top node. */
  __o_node_destroy (tmp);
}

inline dataptr
stack_top (const stack *s)
{
  return s->top->data;
}

inline size_t
stack_size (const stack *s)
{
  return s->size;
}

inline bool
stack_empty (const stack *s)
{
  return s->size == 0;
}

void
stack_destroy (stack *s)
{
  /* Destroying stack from the top, one by one.
  tmp is to save references of deleting element. */
  struct o_node *tmp = s->top;

  while (tmp)
    {
      struct o_node *tmp_next = tmp->next;
      __o_node_destroy (tmp);
      tmp = tmp_next;
    }

  free (s);
}