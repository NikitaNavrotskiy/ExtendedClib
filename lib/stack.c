#include "stack.h"

////////////////////////////////////////////////////
/*      Public API functions of the stack         */
////////////////////////////////////////////////////

stack *
stack_create (void (*destr) (dptr data))
{
  stack *st = (stack *)malloc (sizeof (stack));

  st->size = 0;
  st->top = NULL;
  st->destr = destr;

  return st;
}

void
stack_push (stack *s, constdptr data)
{
  if (!s)
    return;

  s->top = __o_node_create (data, s->top);
  s->size++;
}

void
stack_pop (stack *s)
{
  if (!s || s->size == 0)
    return;

  /* Save old top to not lose references. */
  struct snode *tmp = s->top;

  /* Changing top. */
  s->top = tmp->next;
  s->size--;

  /* Destroy old top node. */
  __o_node_destroy (tmp, s->destr);
}

inline dptr
stack_top (const stack *s)
{
  if (!s)
    return NULL;
  return o_node_get (s->top);
}

inline size_t
stack_size (const stack *s)
{
  if (!s)
    return 0;

  return s->size;
}

inline bool
stack_empty (const stack *s)
{
  if (!s)
    return true;

  return s->size == 0;
}

void
stack_destroy (stack *s)
{
  if (!s)
    return;

  /* Destroying stack from the top, one by one.
  tmp is to save references of deleting element. */
  struct snode *tmp = s->top;

  while (tmp)
    {
      struct snode *tmp_next = tmp->next;
      __o_node_destroy (tmp, s->destr);
      tmp = tmp_next;
    }

  free (s);
}
