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

/** Return a pointer to an empty vector. */
void ivector_init0(ivector *v);

/** Return a pointer to a dynamic array of a given size. */
void ivector_init1(ivector *v, int initial_capacity);

/** Create an ivector object from an existing array of int. */
void ivector_init2(ivector *v, int *x, int size, int initial_capacity);

#ifndef NDEBUG
/** Get the nth value of an ivector. */
int ivector_get(ivector *v, int n);

/** Set the nth value to 'x'. */
void ivector_set(ivector *v, int n, int x);
#else
#define ivector_get(v,n)      ((v)->array[n])
#define ivector_set(v,n,x)    ((v)->array[n]=x)
#endif

/** Add 'x' at the end of the array, call 'ivector_grow1' if needed. */
void ivector_add(ivector *v, int x);

/** Add 'x' at the end of the array, call 'ivector_grow1' if needed. */
void ivector_add_array(ivector *v, int *a, int size);

/** Subtract 'x' elements from the array. */
void ivector_sub(ivector *v, int x);

/** Subtract an element from the array. */
void ivector_sub1(ivector *v);

/** Subtract all elements from the array. */
void ivector_sub_all(ivector *v);

/** Return a deep copy of the array (without the extra storage space). */
int *ivector_get_array(ivector *v);

/** Use quicksort to sort the array in ascending order. */
void ivector_sort_asc(ivector *v);

/** Use quicksort to sort the array in descending order. */
void ivector_sort_des(ivector *v);

/** Increase the internal storage for the array. */
void ivector_grow0(ivector *v, int new_capacity);

/** Double the internal storage for the array. */
void ivector_grow1(ivector *v);

/** Remove from the array all the elements smaller than "smallest". The function will reallocate memory. Return the number of elements removed. */
int ivector_trim_small(ivector *v, int smallest);

/** Remove from the array all the elements larger than "largest". The function will reallocate memory. Return the number of elements removed. */
int ivector_trim_large(ivector *v, int largest);

/** Print the array. Set the argument to NULL to print to the console. */
void ivector_print(ivector *v, FILE *out);

/** Free the memory. */
void ivector_free(ivector *v);

/** Tests and examples for this file. */
void ivector_examples();

#ifdef __cplusplus
}
#endif

#endif
