#include "queue.h"


////////////////////////////////////////////////////
/*      Public API functions of the queue         */
////////////////////////////////////////////////////

queue *
queue_create (void (*destr) (dptr data))
{
  queue *q = (queue *)malloc (sizeof (queue));

  q->front = NULL;
  q->back = NULL;
  q->size = 0;
  q->destr = destr;

  return q;
}

inline void
queue_push (queue *q, constdptr data)
{
  q->front = __do_node_create (data, q->front, NULL);

  /* If Queue wasn't empty => adding reference from former front to the
      new front */
  if (q->front->next != NULL)
    q->front->next->prev = q->front;
  /* If back was NULL, so new element is front and back */
  if (q->back == NULL)
    q->back = q->front;
  q->size++;
}

void
queue_pop (queue *q)
{
  /* Saving back to free it, but not lose back's references */
  struct qnode *tmp = q->back;

  /* changing queue's back  */
  q->back = tmp->prev;

  /* If new back elem is exist, changing its next reference, else => queue is
       empty, so front is NULL */
  if (tmp->prev)
    tmp->prev->next = NULL;
  else
    q->front = NULL;
  q->size--;

  __do_node_destroy (tmp, q->destr);
}

inline __attribute__ ((always_inline)) dptr
queue_front (const queue *q)
{
  return do_node_get (q->front);
}

inline __attribute__ ((always_inline)) dptr
queue_back (const queue *q)
{
  return do_node_get (q->back);
}

inline __attribute__ ((always_inline)) size_t
queue_size (const queue *q)
{
  return q->size;
}

inline __attribute__ ((always_inline)) bool
queue_empty (const queue *q)
{
  return q->size == 0;
}

void
queue_destroy (queue *q)
{
  struct qnode *tmp = q->front;

  /* Destroying queue from front one by one.
    tmp is to save references of deleting element. */
  while (tmp)
    {
      struct qnode *tmp_next = tmp->next;
      __do_node_destroy (tmp, q->destr);
      tmp = tmp_next;
    }

  free (q);
}