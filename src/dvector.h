#ifndef DVECTOR_H_
#define DVECTOR_H_

// For C++ compilers:
#ifdef __cplusplus
extern "C" {
#endif

/** A dynamic array of double. */
typedef struct
{
    /** Internal array. */
    double *array;

    /** Number of elements in the array. */
    int size;

    /** Max number of elements given the current size of 'a'. */
    int capacity;
}
dvector;

/** Return a pointer to an empty vector. */
void dvector_init0(dvector *v);

/** Return a pointer to a dynamic array of a given size. */
void dvector_init1(dvector *v, int initial_capacity);

#ifndef NDEBUG
/** Return the nth value of a vector. */
double dvector_get(dvector *v, int n);

/** Set the nth value to 'x'. */
void dvector_set(dvector *v, int n, double x);
#else
#define dvector_get(v,n)      ((v)->array[n])
#define dvector_set(v,n,x)    ((v)->array[n]=x)
#endif

/** Add 'x' at the end of the array, call 'dvector_grow1' if necessary. */
void dvector_add(dvector *v, int x);

/** Subtract 'x' elements from the array. */
void dvector_sub(dvector *v, int x);

/** Subtract an element from the array. */
void dvector_sub1(dvector *v);

/** Return a deep copy of the array (without the extra storage space). */
double *dvector_get_array(dvector *v);

/** Increase the internal storage for the array. */
void dvector_grow0(dvector *v, int new_capacity);

/** Double the internal storage for the array. */
void dvector_grow1(dvector *v);

/** Use quicksort to sort the array in ascending order. */
void dvector_sort_asc(dvector *v);

/** Use quicksort to sort the array in descending order. */
void dvector_sort_des(dvector *v);

/** Free the memory. */
void dvector_free(dvector *v);

/** Print the array. Set the argument to NULL to print to the console. */
void dvector_print(dvector *v, FILE *out);

/** Tests and examples for this file. */
void dvector_examples();

#ifdef __cplusplus
}
#endif

#endif
