/**
 * @file types.h For describing different common types
 * to follow DRY principle.
 */

#ifndef _DATA_STRUCTS_LIB_TYPES_H
#define _DATA_STRUCTS_LIB_TYPES_H

/**
 * @brief Alias for void *.
 */
typedef void *dataptr;

/**
 * @struct do_node
 * @brief Implements node for double ordered data structs (like list, queue).
 */
struct do_node
{ // do_node (D-double, O-ordered, node)
  /**
   * @brief User data to store.
   */
  dataptr data;

  /**
   * @brief Pointer to the next node.
   */
  struct do_node *next;

  /**
   * @brief Pointer to the previous node.
   */
  struct do_node *prev;
};

/**
 * @brief Public function to access the dataptr from the do_node
 */
dataptr do_node_get (const struct do_node *nd);

/**
 * @brief Api to work with do_node.
 * It's recommeded to consider this functions
 * as private, which participate in Implementation
 * of the data structures.
 */

/**
 * @brief Function to initialize do_node.
 *
 * @param data Pointer to data.
 * @param next Pointer to the next do_node.
 * @param prev Pointer to the previous do_node.
 * @return struct qnode* New created do_node.
 */
struct do_node *__do_node_create (dataptr data, struct do_node *next,
                                  struct do_node *prev);

/**
 * @brief Function to destroy do_node. Not checking if
 * node is nullptr.
 *
 * @param node Node to destroy
 */
void __do_node_destroy (struct do_node *node);

/**
 * @struct o_node
 * @brief Implements node for only ordered data structs (like stack,
 * ordered_list).
 */
struct o_node
{ // o_node (O-ordered, node)
  /**
   * @brief User data to store.
   */
  dataptr data;

  /**
   * @brief Pointer to the next node.
   */
  struct o_node *next;
};

/**
 * @brief Public function to access the dataptr from the do_node
 */
dataptr o_node_get (const struct o_node *nd);

/**
 * @brief Api to work with o_node.
 * It's recommeded to consider this functions
 * as private, which participate in Implementation
 * of the data structures.
 */

/**
 * @brief Function to initialize o_node.
 *
 * @param data Pointer to data.
 * @param next Pointer to the next node.
 * @return  struct qnode* New created qnone.
 */
struct o_node *__o_node_create (dataptr data, struct o_node *next);

/**
 * @brief Function to destroy o_node. Not checking if
 * node is nullptr.
 *
 * @param node Node to destroy
 */
void __o_node_destroy (struct o_node *node);

#endif