/**
 * @file queue.h Implementation of Queue data structure
 */

#ifndef _DATA_STRUCT_QUEUE_H
#define _DATA_STRUCT_QUEUE_H

#include <stdbool.h>  // bool
#include <stddef.h>   // size_t
#include <stdlib.h>   // malloc, free

/**
 * @struct Implements Queue data struct.
 *
 */
typedef struct queue {
  /**
   * @brief variable to store size of the queue.
   */
  size_t size;

  /**
   * @brief Pointer to the front of queue.
   */
  struct qnode *front;

  /**
   * @brief Pointer to the back of queue.
   */
  struct qnode *back;
} queue;

/**
 * @brief Public API functions of the queue.
 *
 */

/**
 * @brief Function to create new queue. Allocates the memore. Should be
 * destroyed at the end.
 * @return Pointer to new queue.
 */
queue *queue_create();

/**
 * @brief Function to push new element to the queue's front.
 *
 * @param q Queue where new element will be placed
 * @param data Data to push into the queue.
 */
void queue_push(queue *q, void *data);

/**
 * @brief Function to pop last element from the queue
 *
 * @param q Queue to pop element.
 */
void queue_pop(queue *q);

/**
 * @brief Function to get front element.
 *
 * @param q Queue to get front element from.
 * @return void* Element from the queue's front.
 */
void *queue_front(const queue *q);

/**
 * @brief Function to get back element.
 *
 * @param q Queue to get back element from.
 * @return void* Element from the queue's back.
 */
void *queue_back(const queue *q);

/**
 * @brief Function to get size of queue (number of elements)
 *
 * @param q Queue to get size from.
 * @return size_t Actual size of queue.
 */
size_t queue_size(const queue *q);

/**
 * @brief Function to check if queue is empty
 *
 * @param q Queue to check the queue
 * @return true If queue is empty.
 * @return false If queue is not empty.
 */
bool queue_empty(const queue *q);

/**
 * @brief Function to destroy queue. Frees the memory.
 * Not checking that q == nullptr.
 * @param q Pointer of the queue to destroy.
 */
void queue_destroy(queue *q);

#endif