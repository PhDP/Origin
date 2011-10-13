/*! \file
 *
 * \brief A growable array of double.
 */ 

#ifndef DVECTOR_H_
#define DVECTOR_H_

// For C++ compilers:
#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief A dynamic array of double.
 */
typedef struct
{
    double *array; /**< Internal array. */

    int size; /**< Number of elements in the array. */

    int capacity; /**< Max number of elements given the current size of 'a'. */
}
dvector;

/**
 * \brief Initialize a vector with the default initial capacity.
 * 
 * \param v  The object to initialize.
 */
void dvector_init0(dvector *v);

/**
 * \brief Initialize a vector of a given initial capacity.
 * 
 * \param v  The object to initialize.
 */
void dvector_init1(dvector *v, int initial_capacity);

#ifndef NDEBUG
/**
 * \brief Get the nth element of an array.
 *
 * The basic function is safe, it will use assert to make sure you're not
 * accessing an element out of the array. If NDEBUG is define at compile-time,
 * this function will be replaced by an unsafe, but faster, macro.
 * 
 * \param v  The dvector object.
 * \param n  Index of the element to return.
 * \return   The nth value in the array.
 */
double dvector_get(dvector *v, int n);

/**
 * \brief Set the nth element of the array.
 *
 * The basic function is safe, it will use assert to make sure you're not
 * accessing an element out of the array. If NDEBUG is define at compile-time,
 * this function will be replaced by an unsafe, but faster, macro.
 * 
 * \param v  The dvector object.
 * \param n  Index of the element to change.
 * \param x  The new value.
 */
void dvector_set(dvector *v, int n, double x);

/**
 * \brief Remove 'z' elements from the array.
 *
 * The function will remove the 'z' last elements of the array. In practice
 * this function do not free or reallocate memory, it simply decrease the
 * 'size' variable.
 * 
 * \param v  The dvector object.
 * \param z  The number of elements to remove at the end of the array.
 */
void dvector_rmv(dvector *v, int z);

/**
 * \brief Remove the last element of the array.
 *
 * The function will remove the last element of the array. In practice
 * this function do not free or reallocate memory, it simply decrease the
 * 'size' variable by one.
 * 
 * \param v  The dvector object.
 */
void dvector_rmv1(dvector *v);

/**
 * \brief Remove all elements.
 *
 * The function will remove all elements of the array. In practice
 * this function do not free or reallocate memory, it simply set the 'size'
 * variable to 0.
 * 
 * \param v  The dvector object.
 */
void dvector_rmvall(dvector *v);
#else
#define dvector_get(v,n)      ((v)->array[n])
#define dvector_set(v,n,x)    ((v)->array[n]=x)
#define dvector_rmv(v,z)      (v->size=(v->size>0)?v->size-z:0)
#define dvector_rmv1(v)       dvector_rmv(v,1)
#define dvector_rmvall(v)     (v->size=0)
#endif

/**
 * \brief Add an element at the end of the array.
 *
 * This function adds an element at the end of the array. It will automatically
 * call dvector_grow1 if there isn't enough space.
 * 
 * \param v  The dvector object.
 * \param x  The value added at the end of the array.
 */
void dvector_add(dvector *v, int x);

/**
 * \brief Return a deep copy of the array.
 *
 * This function generates an array of double of size v->size (i.e.: without
 * the extra storage).
 * 
 * \param v  The dvector object.
 * \return   A deep copy of the internal array without the extra storage.
 */
double *dvector_get_array(dvector *v);

/**
 * \brief Increase the internal storage capacity of the array.
 * 
 * \param v              The dvector object.
 * \param new_capacity   The new storage capacity of the object.
 */
void dvector_grow0(dvector *v, int new_capacity);

/**
 * \brief Double the internal storage capacity of the array.
 * 
 * \param v              The dvector object.
 */
void dvector_grow1(dvector *v);

/** Use quicksort to sort the array in ascending order. */

/**
 * \brief Sort the array in ascending order.
 *
 * This function sort the array using the standard library's quicksort
 * algorithm.
 * 
 * \param v  The dvector object.
 */
void dvector_sort_asc(dvector *v);

/**
 * \brief Sort the array in descending order.
 *
 * This function sort the array using the standard library's quicksort
 * algorithm.
 * 
 * \param v  The dvector object.
 */
void dvector_sort_des(dvector *v);

/**
 * \brief Free the memory of the array.
 * 
 * \param v  The dvector object.
 */
void dvector_free(dvector *v);

/**
 * \brief Print the array. Set out to NULL to print to the console.
 * 
 * \param v  The dvector object.
 */
void dvector_print(dvector *v, FILE *out);

/**
 * \brief Tests and examples for this object.
 */
void dvector_examples();

#ifdef __cplusplus
}
#endif

#endif
