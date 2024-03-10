#include "forward_list.h"


////////////////////////////////////////////////////
/*   Public API functions of the forward_list     */
////////////////////////////////////////////////////

forward_list *
forward_list_create ()
{
  forward_list *l = (forward_list *)malloc (sizeof (forward_list));

  l->front = NULL;
  l->size = 0;

  return l;
}

inline __attribute__ ((always_inline)) forward_list_iterator
forward_list_begin (const forward_list *l)
{
  return l->front;
}

void
forward_list_clear (forward_list *l, void (*destr) (dptr data))
{
  struct flnode *tmp = l->front;

  /* Deleting all nodes. */
  while (tmp)
    {
      struct flnode *tmp_next = tmp->next;
      __o_node_destroy (tmp, destr);
      tmp = tmp_next;
    }

  /* Set starting values. */
  l->size = 0;
  l->front = NULL;
}

forward_list *
forward_list_copy (const forward_list *l, dptr (*cpy) (const dptr data))
{
  if (!l)
    return NULL;
  /* Creating dest forward list. */
  forward_list *other = forward_list_create ();
  /* Copy values to dest forward list. */
  struct flnode *cur = l->front;
  struct flnode *cur_other = NULL;

  while (cur)
    {
      cur_other
          = forward_list_insert_after (other, cur_other, cpy (cur->data));
      cur = cur->next;
    }

  return other;
}

size_t
forward_list_count (const forward_list *l, constdptr data,
                    bool (*cmp) (constdptr first, constdptr second))
{
  size_t res = 0;
  struct flnode *cur = l->front;

  /* Goes through forward list one by one and count res. */
  while (cur)
    {
      if (cmp (data, cur->data))
        res++;
      cur = cur->next;
    }

  return res;
}

size_t
forward_list_count_if (const forward_list *l,
                       bool (*predicate) (constdptr data))
{
  size_t res = 0;
  struct flnode *cur = l->front;

  /* Goes through forward list one by one and count res. */
  while (cur)
    {
      if (predicate (cur->data))
        res++;
      cur = cur->next;
    }

  return res;
}

void
forward_list_destroy (forward_list *l, void (*destr) (dptr data))
{
  /* Deleting all nodes. */
  forward_list_clear (l, destr);
  /* Frees the memory for struct forward list. */
  free (l);
}

inline __attribute__ ((always_inline)) forward_list_iterator
forward_list_end ()
{
  return NULL;
}

inline void
forward_list_emplace_after (forward_list *l, forward_list_iterator where,
                            constdptr data)
{
  forward_list_insert_after (l, where, data);
}

inline void
forward_list_emplace_front (forward_list *l, constdptr data)
{
  forward_list_push_front (l, data);
}

inline __attribute__ ((always_inline)) bool
forward_list_empty (const forward_list *l)
{
  return l->size == 0;
}

void
forward_list_erase_after (forward_list *l, forward_list_iterator where,
                          void (*destr) (dptr data))
{
  if (!where)
    {
      forward_list_pop_front (l, destr);
      return;
    }

  if (!where->next)
    return;

  /* Changing refernces. */
  struct flnode *tmp = where->next;
  where->next = tmp->next;
  l->size--;

  /* Calling destructor. */
  __o_node_destroy (tmp, destr);
}

inline __attribute__ ((always_inline)) dptr
forward_list_front (const forward_list *l)
{
  return l->front->data;
}

forward_list_iterator
forward_list_find (const forward_list *l, constdptr data,
                   bool (*cmp) (constdptr first, constdptr second))
{
  struct flnode *cur = l->front;

  /* Find first occurence, that cmp() return true. */
  while (cur)
    {
      if (cmp (data, cur->data))
        return cur;
      cur = cur->next;
    }

  return forward_list_end ();
}

forward_list_iterator
forward_list_find_if (const forward_list *l,
                      bool (*predicate) (constdptr data))
{
  struct flnode *cur = l->front;

  /* Find first occurence, that predicate() return true. */
  while (cur)
    {
      if (predicate (cur->data))
        return cur;
      cur = cur->next;
    }

  return forward_list_end ();
}

forward_list_iterator
forward_list_insert_after (forward_list *l, forward_list_iterator where,
                           constdptr data)
{
  if (!where)
    {
      forward_list_push_front (l, data);
      return l->front;
    }

  where->next = __o_node_create (data, where->next);
  l->size++;

  return where->next;
}

forward_list_iterator
forward_list_insert_after_many (forward_list *l, forward_list_iterator where,
                                size_t count, ...)
{
  forward_list_iterator res = NULL;
  /* Using va_list to implement any count of arguments to insert. */
  va_list args;
  /* Count is number of elements. */
  va_start (args, count);

  /* Inserting all elements one by one. */
  for (size_t i = 0; i < count; i++)
    {
      dptr cur = va_arg (args, dptr);
      where = forward_list_insert_after (l, where, cur);

      /* Writing result list_iterator. */
      if (i == 0)
        res = where;
    }

  /* Ending work with va_list. */
  va_end (args);

  return res;
}

void
forward_list_pop_front (forward_list *l, void (*destr) (dptr data))
{
  if (!l->front)
    return;

  struct flnode *tmp = l->front;

  l->front = tmp->next;
  l->size--;

  __o_node_destroy (tmp, destr);
}

inline void
forward_list_push_front (forward_list *l, constdptr data)
{
  l->front = __o_node_create (data, l->front);
  l->size++;
}

void
forward_list_remove (forward_list *l, dptr data,
                     bool (*cmp) (constdptr first, constdptr second),
                     void (*destr) (dptr data))
{
  struct flnode *cur = l->front;
  struct flnode *cur_prev = NULL;

  /* Deleting all nodes if <cmp> returns true. */
  while (cur)
    {
      struct flnode *cur_next = cur->next;

      if (cmp (data, cur->data))
        {
          forward_list_erase_after (l, cur_prev, destr);
          cur = NULL;
        }
      else
        cur_prev = cur;
      cur = cur_next;
    }
}

void
forward_list_remove_if (forward_list *l, bool (*predicate) (constdptr data),
                        void (*destr) (dptr data))
{
  struct flnode *cur = l->front;
  struct flnode *cur_prev = NULL;

  /* Deleting all nodes if <predicate> returns true. */
  while (cur)
    {
      struct flnode *cur_next = cur->next;

      if (predicate (cur->data))
        {
          forward_list_erase_after (l, cur_prev, destr);
          cur = NULL;
        }
      else
        cur_prev = cur;
      cur = cur_next;
    }
}

void forward_list_reverse (forward_list *l);

inline __attribute__ ((always_inline)) size_t
forward_list_size (const forward_list *l)
{
  return l->size;
}

void forward_list_sort (forward_list *l,
                        int (*cmp) (constdptr first, constdptr second));

void forward_list_unique (forward_list *l,
                          bool (*predicate) (constdptr first,
                                             constdptr second));