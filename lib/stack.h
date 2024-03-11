/**
 * @file stack.h Implementation of Stack data structure
 */

#ifndef _EXTENDED_C_LIB_LIB_STACK_H
#define _EXTENDED_C_LIB_LIB_STACK_H

#include <stdbool.h> // bool
#include <stddef.h>  // size_t
#include <stdlib.h>  // malloc, free

#include "types.h"

#define snode o_node

/**
 * @struct stack
 * @brief Implements Stack data struct.
 * @var size variable to store size of the stack.
 * @var top Pointer to the top of stack.
 */
typedef struct stack
{
  /**
   * @brief Pointer to the top of stack.
   */
  struct snode *top;

  /**
   * @brief Variable to store size of the stack.
   */
  size_t size;

  /**
   * @brief Destructor for data.
   */
  void (*destr) (dptr);
} stack;


////////////////////////////////////////////////////
/*      Public API functions of the stack         */
////////////////////////////////////////////////////


/**
 * @brief Function to create new stack. Allocates the memory. Should be
 * destroyed at the end.
 * @param destr Destructor for data.
 * @return Pointer to new stack.
 */
stack *stack_create (void (*destr) (dptr data));

/**
 * @brief Function to push new element to the stack's top..
 *
 * @param s Stack where new element will be placed.
 * @param data Data to push into the stack.
 */
void stack_push (stack *s, constdptr data);

/**
 * @brief Function to pop top element from the stack.
 * Do not check if stack is empty.
 * @param s Stack to pop element.
 */
void stack_pop (stack *s);

/**
 * @brief Function to get top element from the Stack.
 *
 * @param s Stack to get top element from.
 * @return void* Element from the stack's t.
 */
dptr stack_top (const stack *s);

/**
 * @brief Function to get size of stack (number of elements)
 *
 * @param s Stackto get size from.
 * @return size_t Actual size of stack..
 */
size_t stack_size (const stack *s);

/**
 * @brief Function to check if stack is empty
 *
 * @param s Stack to check for emptiness.
 * @return true If stack is empty.
 * @return false If stack is not empty.
 */
bool stack_empty (const stack *s);

/**
 * @brief Function to destroy stack. Frees the memory.
 * Not checking that s == nullptr.
 * @param s Pointer of the stack to destroy.
 */
void stack_destroy (stack *s);

#endif