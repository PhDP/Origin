/*! \file
 *
 * \brief A generic vector.
 */ 

#ifndef VVECTOR_H_
#define VVECTOR_H_

// For C++ compilers:
#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief A dynamic array of void pointers.
 */
typedef struct
{
    void **array; /**< Internal array. */

    unsigned int size; /**< Number of elements in the array. */

    unsigned int capacity; /**< Max number of elements given the current size of 'a'. */
}
vvector;

/**
 * \brief Initialize a vector with the default initial capacity.
 * 
 * \param v  The object to initialize.
 */
void vvector_init0(vvector *v);

/**
 * \brief Initialize a vector of a given initial capacity.
 * 
 * \param v                  The object to initialize.
 * \param initial_capacity   The memory allocated to the internal array.
 */
void vvector_init1(vvector *v, unsigned int initial_capacity);

#ifndef NDEBUG
/**
 * \brief Get the nth element of an array.
 *
 * The basic function is safe, it will use assert to make sure you're not
 * accessing an element out of the array. If NDEBUG is define at compile-time,
 * this function will be replaced by an unsafe, but faster, macro.
 * 
 * \param v  The vector object.
 * \param n  Index of the element to return.
 * \return   The nth value in the array.
 */
void *vvector_get(vvector *v, unsigned int n);


/**
 * \brief Set the nth element of the array.
 *
 * The basic function is safe, it will use assert to make sure you're not
 * accessing an element out of the array. If NDEBUG is define at compile-time,
 * this function will be replaced by an unsafe, but faster, macro.
 * 
 * \param v  The vector object.
 * \param n  Index of the element to change.
 * \param x  The new value.
 */
void vvector_set(vvector *v, unsigned int n, void *x);

/**
 * \brief Remove 'z' elements from the array.
 *
 * The function will remove the 'z' last elements of the array. In practice
 * this function do not free or reallocate memory, it simply decrease the
 * 'size' variable.
 * 
 * \param v  The vector object.
 * \param z  The number of elements to remove at the end of the array.
 */
void vvector_rmv(vvector *v, unsigned int z);

/**
 * \brief Remove the last element of the array.
 *
 * The function will remove the last element of the array. In practice
 * this function do not free or reallocate memory, it simply decrease the
 * 'size' variable by one.
 * 
 * \param v  The vector object.
 */
void vvector_rmv1(vvector *v);

/**
 * \brief Remove all elements.
 *
 * The function will remove all elements of the array. In practice
 * this function do not free or reallocate memory, it simply set the 'size'
 * variable to 0.
 * 
 * \param v  The vector object.
 */
void vvector_rmvall(vvector *v);

#else
#define vvector_get(v,n)      ((v)->array[n])
#define vvector_set(v,n,x)    ((v)->array[n]=x)
#define vvector_rmv(v,z)      (v->size=(v->size>=z)?v->size-z:0)
#define vvector_rmv1(v)       vvector_rmv(v,1)
#define vvector_rmvall(v)     (v->size=0)
#endif

/**
 * \brief Add an element at the end of the array.
 *
 * This function adds an element at the end of the array. It will automatically
 * call vvector_grow1 if there isn't enough space.
 * 
 * \param v  The vector object.
 * \param x  The value added at the end of the array.
 */
void vvector_add(vvector *v, void *x);

/**
 * \brief Return a deep copy of the array.
 *
 * This function generates an array of void* of size v->size (i.e.: without
 * the extra storage).
 * 
 * \param v  The vector object.
 * \return   A deep copy of the internal array without the extra storage.
 */
void **vvector_get_array(vvector *v);

/**
 * \brief Increase the internal storage capacity of the vector.
 * 
 * \param v              The vector object.
 * \param new_capacity   The new storage capacity of the object.
 */
void vvector_grow0(vvector *v, unsigned int new_capacity);

/**
 * \brief Double the internal storage capacity of the vector.
 * 
 * \param v              The vector object.
 */
void vvector_grow1(vvector *v);

/**
 * \brief Print the array. Set out to NULL to print to the console.
 * 
 * \param v  The vector object.
 */
void vvector_print(vvector *v, FILE *out);

/**
 * \brief Free the memory of the array.
 * 
 * \param v  The vector object.
 */
void vvector_free(vvector *v);

#ifdef __cplusplus
}
#endif

#endif
