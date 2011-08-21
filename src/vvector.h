#ifndef VVECTOR_H_
#define VVECTOR_H_

// For C++ compilers:
#ifdef __cplusplus
extern "C" {
#endif

/** A dynamic array of double. */
typedef struct
{
	/** Internal array. */
	void **array;

	/** Number of elements in the array. */
	int size;

	/** Max number of elements given the current size of 'a'. */
	int capacity;
}
vvector;

/** Return a pointer to an empty vector. */
void vvector_init0(vvector *v);

/** Return a pointer to a dynamic array of a given size. */
void vvector_init1(vvector *v, int initial_capacity);

#ifndef NDEBUG
/** Return the nth value of a vector. */
double vvector_get(vvector *v, int n);

/** Set the nth value to 'x'. */
void vvector_set(vvector *v, int n, void *x);
#else
#define vvector_get(v,n)      (v->array[n])
#define vvector_set(v,n,x)    (v->array[n]=x)
#endif

/** Add 'x' at the end of the array, call 'hon_vector_grow1' if necessary. */
void vvector_add(vvector *v, void *x);

/** Subtract 'x' elements from the array. */
void vvector_sub(vvector *v, int x);

/** Subtract an element from the array. */
void vvector_sub1(vvector *v);

/** Return a deep copy of the array (without the extra storage space). */
void **vvector_get_array(vvector *v);

/** Increase the internal storage for the array. */
void vvector_grow0(vvector *v, int new_capacity);

/** Double the internal storage for the array. */
void vvector_grow1(vvector *v);

/** Free the memory. */
void vvector_free(vvector *v);

#ifdef __cplusplus
}
#endif

#endif

