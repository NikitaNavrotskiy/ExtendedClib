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
stack_push (stack *s, constdptr data)
{
  s->top = __o_node_create (data, s->top);
  s->size++;
}

void
stack_pop (stack *s, void (*destr) (dptr data))
{
  /* Save old top to not lose references. */
  struct snode *tmp = s->top;

  /* Changing top. */
  s->top = tmp->next;
  s->size--;

  /* Destroy old top node. */
  __o_node_destroy (tmp, destr);
}

inline __attribute__ ((always_inline)) dptr
stack_top (const stack *s)
{
  return o_node_get (s->top);
}

inline __attribute__ ((always_inline)) size_t
stack_size (const stack *s)
{
  return s->size;
}

inline __attribute__ ((always_inline)) bool
stack_empty (const stack *s)
{
  return s->size == 0;
}

void
stack_destroy (stack *s, void (*destr) (dptr data))
{
  /* Destroying stack from the top, one by one.
  tmp is to save references of deleting element. */
  struct snode *tmp = s->top;

  while (tmp)
    {
      struct snode *tmp_next = tmp->next;
      __o_node_destroy (tmp, destr);
      tmp = tmp_next;
    }

  free (s);
}