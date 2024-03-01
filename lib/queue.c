#include "queue.h"

/**
 * @brief private function to initialize qnode.
 *
 * @param data Pointer to data.
 * @param next Pointer to the next qnode.
 * @param prev Pointer to the previous qnode.
 * @return struct qnode* New created qnone.
 */
static struct qnode *qnode_create(void *data, struct qnode *next,
                                  struct qnode *prev) {
  struct qnode *nd = (struct qnode *)malloc(sizeof(struct qnode));

  nd->next = next;
  nd->data = data;
  nd->prev = prev;

  return nd;
}

/**
 * @brief private function to destroy qnode. Not checking if
 * node is nullptr.
 *
 * @param node Node to destroy
 */
static inline void qnode_destroy(struct qnode *node) { free(node); }

/**
 * @brief Implementation of queue's API functions.
 */

queue *queue_create() {
  queue *q = (queue *)malloc(sizeof(queue));

  q->front = NULL;
  q->back = NULL;
  q->size = 0;

  return q;
}

inline void queue_push(queue *q, void *data) {
  q->front = qnode_create(data, q->front, NULL);

  /* If Queue wasn't empty => adding reference from former front to the
      new front */
  if (q->front->next != NULL) q->front->next->prev = q->front;
  /* If back was NULL, so new element is front and back */
  if (q->back == NULL) q->back = q->front;
  q->size++;
}

void queue_pop(queue *q) {
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

  qnode_destroy(tmp);
}

inline void *queue_front(const queue *q) { return q->front->data; }

void *queue_back(const queue *q) { return q->back->data; }

inline size_t queue_size(const queue *q) { return q->size; }

inline bool queue_empty(const queue *q) { return q->size == 0; }

void queue_destroy(queue *q) {
  struct qnode *tmp = q->front;

  /* Destroying queue from front one by one.
    tmp is to save references of deleting element. */
  while (tmp) {
    struct qnode *tmp_next = tmp->next;
    qnode_destroy(tmp);
    tmp = tmp_next;
  }

  free(q);
}