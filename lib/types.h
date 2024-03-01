/**
 * @file types.h For describing different common types
 * to follo DRY principle. 
 */

#ifndef _DATA_STRUCTS_LIB_TYPES_H
#define _DATA_STRUCTS_LIB_TYPES_H

/**
 * @struct Implements node for double ordered data structs (like list, queue).
 */
struct do_node {  // do_node (D-double, O-ordered, node)
  /**
   * @brief User data to store in queue.
   */
  void *data;

  /**
   * @brief Pointer to the next node in queue.
   */
  struct do_node *next;

  /**
   * @brief Pointer to the previous node in queue.
   */
  struct do_node *prev;
};

#endif