/**
 * @file types.h For describing different common types
 * to follow DRY principle.
 */

#ifndef _EXTENDED_C_LIB_LIB_TYPES_H
#define _EXTENDED_C_LIB_LIB_TYPES_H

/**
 * @brief Alias for void *.
 */
typedef void *dptr;

/**
 * @brief Alias for const void *.
 */
typedef const void *constdptr;

/**
 * @struct do_node
 * @brief Implements node for double ordered data structs (like list, queue).
 */
struct do_node
{ // do_node (D-double, O-ordered, node)
  /**
   * @brief User data to store.
   */
  dptr data;

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
 * @brief Public function to access the dptr from the do_node.
 * Returns NULL, if nd == NULL.
 */
dptr do_node_get (const struct do_node *nd);

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
struct do_node *__do_node_create (constdptr data, struct do_node *next,
                                  struct do_node *prev);

/**
 * @brief Function to destroy do_node. Not checking if
 * node is nullptr.
 *
 * @param node Node to destroy
 * @param destr Funciton to destroy data correctly,
 * Should be NULL, if do not should be freed.
 */
void __do_node_destroy (struct do_node *node, void (*destr) (dptr data));

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
  dptr data;

  /**
   * @brief Pointer to the next node.
   */
  struct o_node *next;
};

/**
 * @brief Public function to access the dptr from the do_node.
 * Returns NULL, if nd == NULL.
 */
dptr o_node_get (const struct o_node *nd);

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
 * @return  struct o_node* New created o_none.
 */
struct o_node *__o_node_create (constdptr data, struct o_node *next);

/**
 * @brief Function to destroy o_node. Not checking if
 * node is nullptr.
 *
 * @param node Node to destroy
 * @param destr Funciton to destroy data correctly,
 * Should be NULL, if do not should be freed.
 */
void __o_node_destroy (struct o_node *node, void (*destr) (dptr data));


/**
 * @struct pair
 * @brief Implements pair-node that contains to values.
 */
struct pair
{ 
  /**
   * @brief Implements first value (Key for Hashmap).
   */
  dptr key;

  /**
   * @brief Implements second value (Value for Hashmap).
   */
  dptr value;
};

/**
 * @brief Api to work with pair.
 */

/**
 * @brief Function to initialize pair.
 *
 * @param key First value (key).
 * @param value Second value (Value).
 * @return  struct pair * New created pair.
 */
struct pair *pair_create (constdptr key, constdptr val);

/**
 * @brief Function to destroy pair. Not checking if
 * node is nullptr.
 *
 * @param node Node to destroy
 * @param destr Funciton to destroy pair correctly,
 * Should be NULL, if do not should be freed.
 */
void pair_destroy (struct pair *pair, void (*destr) (struct pair *pair));

#endif