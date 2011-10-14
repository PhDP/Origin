/*! \file
 *
 * \brief A growable array of int.
 */ 

#ifndef IVECTOR_H_
#define IVECTOR_H_

// For C++ compilers:
#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief A dynamic array of int.
 */
typedef struct
{
    int *array; /**< Internal array. */

    int size; /**< Number of elements in the array. */

    int capacity; /**< Max number of elements given the current size of 'a'. */
}
ivector;

/**
 * \brief Initialize a vector with the default initial capacity.
 * 
 * \param v  The object to initialize.
 */
void ivector_init0(ivector *v);

/**
 * \brief Initialize a vector of a given initial capacity.
 * 
 * \param v                  The object to initialize.
 * \param initial_capacity   The memory allocated to the internal array.
 */
void ivector_init1(ivector *v, int initial_capacity);

/**
 * \brief Create an ivector object from an existing array of int. 
 * 
 * \param v                  The object to initialize.
 * \param x                  Array of int to copy.
 * \param size               Number of elements in 'x'.
 * \param initial_capacity   The memory allocated to the internal array, the initial capacity must be equal or greater than 'size'.
 */
void ivector_init2(ivector *v, int *x, int size, int initial_capacity);

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
int ivector_get(ivector *v, int n);

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
void ivector_set(ivector *v, int n, int x);

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
void ivector_rmv(ivector *v, int z);

/**
 * \brief Remove the last element of the array.
 *
 * The function will remove the last element of the array. In practice
 * this function do not free or reallocate memory, it simply decrease the
 * 'size' variable by one.
 * 
 * \param v  The vector object.
 */
void ivector_rmv1(ivector *v);

/**
 * \brief Remove all elements.
 *
 * The function will remove all elements of the array. In practice
 * this function do not free or reallocate memory, it simply set the 'size'
 * variable to 0.
 * 
 * \param v  The vector object.
 */
void ivector_rmvall(ivector *v);
#else
#define ivector_get(v,n)      ((v)->array[n])
#define ivector_set(v,n,x)    ((v)->array[n]=x)
#define ivector_rmv(v,z)      (v->size=(v->size>=z)?v->size-z:0)
#define ivector_rmv1(v)       ivector_rmv(v,1)
#define ivector_rmvall(v)     (v->size=0)
#endif

/**
 * \brief Add an element at the end of the array.
 *
 * This function adds an element at the end of the array. It will automatically
 * call ivector_grow1 if there isn't enough space.
 * 
 * \param v  The ivector object.
 * \param x  The value added at the end of the array.
 */
void ivector_add(ivector *v, int x);

/**
 * \brief Add the elements from an array at the end of the ivector.
 *
 * This function adds an array at the end of the ivector. It will automatically
 * call ivector_grow1 if there isn't enough space.
 * 
 * \param v      The vector object.
 * \param a      The array to add at the end of the ivector.
 * \param size   Size of 'a'.
 */
void ivector_add_array(ivector *v, int *a, int size);

/**
 * \brief Return a deep copy of the array.
 *
 * This function generates an array of int of size v->size (i.e.: without
 * the extra storage).
 * 
 * \param v  The vector object.
 * \return   A deep copy of the internal array without the extra storage.
 */
int *ivector_get_array(ivector *v);

/**
 * \brief Increase the internal storage capacity of the vector.
 * 
 * \param v              The vector object.
 * \param new_capacity   The new storage capacity of the object.
 */
void ivector_grow0(ivector *v, int new_capacity);

/**
 * \brief Double the internal storage capacity of the vector.
 * 
 * \param v              The vector object.
 */
void ivector_grow1(ivector *v);

/**
 * \brief Sort the array in ascending order.
 *
 * This function sort the array using the standard library's quicksort
 * algorithm.
 * 
 * \param v  The ivector object.
 */
void ivector_sort_asc(ivector *v);

/**
 * \brief Sort the array in descending order.
 *
 * This function sort the array using the standard library's quicksort
 * algorithm.
 * 
 * \param v  The ivector object.
 */
void ivector_sort_des(ivector *v);

/**
 * \brief Trim small elements from the array.
 *
 * Remove from the array all the elements lsmaller than "smallest". The function
 * will reallocate memory. Return the number of elements removed.
 *
 * \param v          The ivector object.
 * \param smallest   The smallest element to remain in the vector.
 * \return           The number of elements removed.
 */
unsigned int ivector_trim_small(ivector *v, int smallest);

/**
 * \brief Trim large elements from the array.
 *
 * Remove from the array all the elements larger than "largest". The function
 * will reallocate memory. Return the number of elements removed.
 *
 * \param v          The ivector object.
 * \param largest    The largest element to remain in the vector.
 * \return           The number of elements removed.
 */
unsigned int ivector_trim_large(ivector *v, int largest);

/**
 * \brief Print the array. Set out to NULL to print to the console.
 * 
 * \param v  The ivector object.
 */
void ivector_print(ivector *v, FILE *out);

/**
 * \brief Free the memory of the array.
 * 
 * \param v  The ivector object.
 */
void ivector_free(ivector *v);

/**
 * \brief Tests and examples for this object.
 */
void ivector_examples();

#ifdef __cplusplus
}
#endif

#endif
