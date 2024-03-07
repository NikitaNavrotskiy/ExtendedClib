#include "list.h"

list *
list_create ()
{
  list *l = (list *)malloc (sizeof (list));

  l->front = NULL;
  l->back = NULL;
  l->size = 0;

  return l;
}

inline __attribute__ ((always_inline)) dptr
list_back (const list *l)
{
  return do_node_get (l->back);
}

inline __attribute__ ((always_inline)) list_iterator
list_begin (const list *l)
{
  return l->front;
}

inline __attribute__ ((always_inline)) list_iterator
list_rbegin (const list *l)
{
  return l->back;
}

void
list_clear (list *l, void (*destr) (dptr data))
{
  struct lnode *tmp = l->front;

  /* Deleting all nodes. */
  while (tmp)
    {
      struct lnode *tmp_next = tmp->next;
      __do_node_destroy (tmp, destr);
      tmp = tmp_next;
    }

  /* Set starting values. */
  l->size = 0;
  l->front = NULL;
  l->back = NULL;
}

list *
list_copy (const list *l, dptr (*cpy) (const dptr data))
{
  if (!l)
    return NULL;
  /* Creating dest list. */
  list *other = list_create ();
  /* Copy values to dest list. */
  struct lnode *cur = l->front;

  while (cur)
    {
      list_push_back (other, cpy (cur->data));
      cur = cur->next;
    }

  return other;
}

size_t
list_count (const list *l, constdptr data,
            bool (*cmp) (constdptr first, constdptr second))
{
  size_t res = 0;
  struct lnode *cur = l->front;

  /* Goes through list one by one and count res. */
  while (cur)
    {
      if (cmp (data, cur->data))
        res++;
      cur = cur->next;
    }

  return res;
}

size_t
list_count_if (const list *l, bool (*predicate) (constdptr data))
{
  size_t res = 0;
  struct lnode *cur = l->front;

  /* Goes through list one by one and count res. */
  while (cur)
    {
      if (predicate (cur->data))
        res++;
      cur = cur->next;
    }

  return res;
}

inline void
list_destroy (list *l, void (*destr) (dptr data))
{
  /* Deleting all nodes. */
  list_clear (l, destr);
  /* Frees the memory for struct list. */
  free (l);
}

inline __attribute__ ((always_inline)) list_iterator
list_end ()
{
  return NULL;
}

inline __attribute__ ((always_inline)) list_iterator
list_rend ()
{
  return NULL;
}

inline void
list_emplace (list *l, list_iterator where, constdptr data)
{
  list_insert (l, where, data);
}

inline void
list_emplace_front (list *l, constdptr data)
{
  list_push_front (l, data);
}

inline void
list_emplace_back (list *l, constdptr data)
{
  list_push_back (l, data);
}

inline __attribute__ ((always_inline)) bool
list_empty (const list *l)
{
  return l->size == 0;
}

void
list_erase (list *l, list_iterator where, void (*destr) (dptr data))
{
  /* Null check. */
  if (!where)
    return;

  struct lnode *tmp = where;

  /* Changing references. */
  if (where->next)
    where->next->prev = where->prev;
  else
    l->back = where->prev;
  if (where->prev)
    where->prev->next = where->next;
  else
    l->front = where->next;
  l->size--;

  __do_node_destroy (tmp, destr);
}

void
list_erase_range (list *l, list_iterator first, list_iterator last,
                  void (*destr) (dptr data))
{
  struct lnode *tmp = first;
  /* Goes throw list from first to the last elem. */

  while (tmp && tmp != last)
    {
      struct lnode *tmp_next = tmp->next;
      list_erase (l, tmp, destr);
      tmp = tmp_next;
    }

  if (last && tmp == last)
    list_erase (l, tmp, destr);
}

inline __attribute__ ((always_inline)) dptr
list_front (const list *l)
{
  return do_node_get (l->front);
}

list_iterator
list_find (const list *l, constdptr data,
           bool (*cmp) (constdptr first, constdptr second))
{
  struct lnode *cur = l->front;

  /* Find first occurence, that cmp() return true. */
  while (cur)
    {
      if (cmp (data, cur->data))
        return cur;
      cur = cur->next;
    }

  return list_end ();
}

list_iterator
list_find_if (const list *l, bool (*predicate) (constdptr data))
{
  struct lnode *cur = l->front;

  /* Find first occurence, that predicate() return true. */
  while (cur)
    {
      if (predicate (cur->data))
        return cur;
      cur = cur->next;
    }

  return list_end ();
}

list_iterator
list_rfind (const list *l, constdptr data,
            bool (*cmp) (constdptr first, constdptr second))
{
  struct lnode *cur = l->back;

  /* Find first occurence in reverse order, that cmp() return true. */
  while (cur)
    {
      if (cmp (data, cur->data))
        return cur;
      cur = cur->prev;
    }

  return list_rend ();
}

list_iterator
list_rfind_if (const list *l, bool (*predicate) (constdptr data))
{
  struct lnode *cur = l->back;

  /* Find first occurence in reverse order, that predicate() return true. */
  while (cur)
    {
      if (predicate (cur->data))
        return cur;
      cur = cur->prev;
    }

  return list_rend ();
}

list_iterator
list_insert (list *l, list_iterator where, constdptr data)
{
  /* New element goes to the end if !where. */
  if (!where)
    {
      list_push_back (l, data);
      return l->back;
    }
  else if (!where->prev)
    {
      list_push_front (l, data);
      return l->front;
    }
  else
    {
      /* If new element going to the middle. */
      where->prev->next = __do_node_create (data, where, where->prev);
      where->prev = where->prev->next;

      l->size++;
    }

  return where->prev;
}

list_iterator
list_insert_many (list *l, list_iterator where, size_t count, ...)
{
  list_iterator res = NULL;
  /* Using va_list to implement any count of arguments to insert. */
  va_list args;
  /* Count is number of elements. */
  va_start (args, count);

  /* Inserting all elements one by one. */
  for (size_t i = 0; i < count; i++)
    {
      dptr cur = va_arg (args, dptr);
      struct lnode *tmp = list_insert (l, where, cur);

      /* Changing inserting place to the next position. */
      where = tmp->next;
      /* Writing result list_iterator. */
      if (i == 0)
        res = tmp;
    }

  /* Ending work with va_list. */
  va_end (args);

  return res;
}

void
list_pop_back (list *l, void (*destr) (dptr data))
{
  if (!l->back)
    return;

  /* Saving ref to old back element. */
  struct lnode *tmp = l->back;

  /* Changing back element */
  l->back = l->back->prev;

  /* Deleting next reference of new l->back.
  If new l->back == NULL, so l->front should be
  NULL too. */
  if (l->back)
    l->back->next = NULL;
  else
    l->front = NULL;
  l->size--;
  /* Deleting old front element. */
  __do_node_destroy (tmp, destr);
}

void
list_pop_front (list *l, void (*destr) (dptr data))
{
  if (!l->front)
    return;

  /* Saving ref to old front element. */
  struct lnode *tmp = l->front;

  /* Changing front element */
  l->front = l->front->next;

  /* Deleting prev reference of new l->front.
  If new l->front == NULL, so l->back should be
  NULL too. */
  if (l->front)
    l->front->prev = NULL;
  else
    l->back = NULL;
  l->size--;
  /* Deleting old front element. */
  __do_node_destroy (tmp, destr);
}

void
list_push_back (list *l, constdptr data)
{
  /* Saving old back element. */
  struct lnode *tmp = l->back;
  /* Creating new last element. */
  l->back = __do_node_create (data, NULL, l->back);

  /* If l->front was exist => tmp != NULL, so making ref to the next
      Esle new element is front element too. */
  if (l->front)
    tmp->next = l->back;
  else
    l->front = l->back;

  l->size++;
}

void
list_push_front (list *l, constdptr data)
{
  /* Saving old front element. */
  struct lnode *tmp = l->front;
  /* Creating new first element. */
  l->front = __do_node_create (data, l->front, NULL);

  /* If l->back was exist => tmp != NULL, so making ref to the prev
      Esle new element is back element too. */
  if (l->back)
    tmp->prev = l->front;
  else
    l->back = l->front;

  l->size++;
}

void
list_remove (list *l, dptr data,
             bool (*cmp) (constdptr first, constdptr second),
             void (*destr) (dptr data))
{
  struct lnode *cur = l->front;

  /* Deleting all nodes if <cmp> returns true. */
  while (cur)
    {
      struct lnode *cur_next = cur->next;
      if (cmp (data, cur->data))
        list_erase (l, cur, destr);
      cur = cur_next;
    }
}

void
list_remove_if (list *l, bool (*predicate) (constdptr data),
                void (*destr) (dptr data))
{
  struct lnode *cur = l->front;

  /* Deleting all nodes if <predicate> returns true. */
  while (cur)
    {
      struct lnode *cur_next = cur->next;
      if (predicate (cur->data))
        list_erase (l, cur, destr);
      cur = cur_next;
    }
}

void list_reverse (list *l);

inline __attribute__ ((always_inline)) size_t
list_size (const list *l)
{
  return l->size;
}

void list_sort (list *l, int (*cmp) (constdptr first, constdptr second));

void list_unique (list *l,
                  bool (*predicate) (constdptr first, constdptr second));