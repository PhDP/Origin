#ifndef UTILS_H_
#define UTILS_H_

#include <stdbool.h>

// For C++ compilers:
#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////
// Operations on matrices and arrays

/**
* Allocates the memory for a rectangular matrix. e.g.:
* <br>
* <br>int **x = (int**)mat_alloc(800, 100, sizeof(int)); // a 800 by 100 matrix of int.
* <br>char **y = (char**)mat_alloc(50, 50, 1); // A 50 by 50 matrix of char.
* <br>double **z = (double**)mat_alloc(1000, 1000, sizeof(double)); // A 1000 by 1000 matrix of double.
*/
void **mat_alloc(int nrows, int ncols, size_t size);

/**
* Free the memory of a matrix, e.g.:
* <br>
* <br>double **x = (double**)mat_alloc(1000, 500, sizeof(double));
* <br>// ...
* <br>mat_free((void***)(&x), 1000);
*/
void mat_free(void **mat, int nrows);

/** Find the min and the max values in an array of double. */
void dmin_max(double *x, int length, double *min, double *max);

/** Find the min and the max values in an array of int. */
void imin_max(int *x, int length, int *min, int *max);

/** Scale all the values in the [0, 1] range. */
void scale_0_1(double *x, int length);

/** Scale all the values in the [0, 100] range. */
void scale_0_100(double *x, int length);

/** Scale all the values in the [a, b] range. */
void scale_a_b(double *x, int length, double a, double b);

/** Remove from the array all the elements smaller than "smallest". The function will reallocate memory & return the number of elements removed. */
int trim_small(int **x, int elements, int smallest);

/** Remove from the array all the elements larger than "largest". The function will reallocate memory & return the number of elements removed. */
int trim_large(int **x, int elements, int largest);

////////////////////////////////////////////////////////////////////
// Other functions

/** Get a non-zero unsigned integer from dev/random. */
unsigned int devrandom_get_uint();

/** Get a non-zero unsigned integer from dev/urandom. */
unsigned int devurandom_get_uint();

/** Compare two 'float' for the qsort function (ascending order). */
int compare_float_asc(const void *x, const void *y);

/** Compare two 'double' for the qsort function (ascending order). */
int compare_double_asc(const void *x, const void *y);

/** Compare two 'int' for the qsort function (ascending order). */
int compare_int_asc(const void *x, const void *y);

/** Compare two 'long' for the qsort function (ascending order). */
int compare_long_asc_asc(const void *x, const void *y);

/** Compare two 'float' for the qsort function (descending order). */
int compare_float_des(const void *x, const void *y);

/** Compare two 'double' for the qsort function (descending order). */
int compare_double_des(const void *x, const void *y);

/** Compare two 'int' for the qsort function (descending order). */
int compare_int_des(const void *x, const void *y);

/** Compare two 'long' for the qsort function (descending order). */
int compare_long_des(const void *x, const void *y);

#ifdef __cplusplus
}
#endif

#endif
