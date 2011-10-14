/*! \file
 *
 * \brief A simple generic implementation of a stack using arrays.
 *
 * A stack of void pointers. This implementation uses an array of void pointer
 * which is extended as needed. The current data can be accessed with the
 * index variable (e.g.; stack->data[index]).
 *
 * The structure supports only two operation: push and pop, Push is used to
 * add data to the stack and pop is used to get them out. Each time pop is
 * called, it will return the last void pointer inserted in the stack and
 * remove this pointer from the stack. To get all the data out of a stack named
 * 's' you could simply use:
 *
 * while (!Stack_is_empty(s)) { void *p = Stack_pop(s); }
 */ 

#ifndef STACK_H_
#define STACK_H_

// For C++ compilers:
#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Generic stack implemented as an array of void pointers.
 */
typedef struct
{
    int index; /**< Current index. */

    unsigned int capacity; /**< Capacity of the stack. */

    void **data; /**< Array of data. */
}
Stack;

/**
 * \brief Initialize a stack object.
 *
 * This function will allocate memory to the internal array and set the index
 * and capacity.
 * 
 * \param s                   The object to initialize.
 * \param initial_capacity    The initial capacity of the internal array.
 */
void Stack_init(Stack *s, unsigned int initial_capacity);

/**
 * \brief Push to the stack.
 *
 * Push a void pointer to the stack. The stack will automatically grow if
 * it needs to.
 * 
 * \param s       The stack object.
 * \param item    The intem to push to the stack
 */
void Stack_push(Stack *s, void *item);

#ifndef NDEBUG
/**
 * \brief Pop stack.
 *
 * Pop a void pointer from the stack. The pointer is removed from the stack
 * and returned by this function. 
 * 
 * \param s   The stack object.
 * \return    The object at the top of the stack. Returns NULL if the stack
 *            is empty.
 */
void *Stack_pop(Stack *s);

/**
 * \brief Return true if the stack is empty.
 *
 * Check if the stack is empty and return true if it is. It's that simple.
 * 
 * \param s   The stack object.
 * \return    1 (TRUE) if the stack is empty, 0 (FALSE) otherwise.
 */
int Stack_is_empty(const Stack *s);
#else
#define Stack_pop(s)        ((s->index>-1)?s->data[s->index--]:NULL)
#define Stack_is_empty(s)   (s->index==-1)
#endif

/**
 * \brief Double the internal capacity.
 *
 * A function used by 'Stack_push' when the internal capacity isn't enough to
 * accomodate new pointers.
 * 
 * \param s   The stack object.
 * \return    1 (TRUE) if the stack is empty, 0 (FALSE) otherwise..
 */
void Stack_grow(Stack *s);

/**
 * \brief Free the array of void pointers.
 *
 * This function will only free the memory of array of pointer and nothing else,
 * especially not the data pointed to by the pointer.
 * 
 * \param s   The stack object.
 */
void Stack_free(Stack *s);

#ifdef __cplusplus
}
#endif

#endif
