/*! \file
 *
 * \brief A set of useful functions. Things to do stuff, to be precise :P
 */ 

#ifndef UTILS_H_
#define UTILS_H_

// For C++ compilers:
#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////
// Operations on matrices and arrays

/**
 * \brief Allocates the memory for a rectangular matrix.
 * 
 * Allocates the memory for a rectangular matrix, for example:
 * <br>
 * <br>int **x = (int**)mat_alloc(800, 100, sizeof(int)); // a 800 by 100 matrix of int.
 * <br>char **y = (char**)mat_alloc(50, 50, 1); // A 50 by 50 matrix of char.
 * <br>double **z = (double**)mat_alloc(1000, 1000, sizeof(double)); // A 1000 by 1000 matrix of double.
 *
 * \param   nrows  The number of rows in the matrix.
 * \param   ncols  The number of columns in the matrix.
 * \param   size   Size of a single element of the type used in the matrix. e.g.:
 *                 sizeof(int) for a matrix of int.
 * \return         Pointer to the matrix.
 */
void **mat_alloc(int nrows, int ncols, size_t size);

/**
 * \brief Free the memory of a matrix
 *
 * Free the memory of a matrix, e.g.:
 * <br>
 * <br>double **x = (double**)mat_alloc(1000, 500, sizeof(double));
 * <br>// ...
 * <br>mat_free((void***)(&x), 1000);
 *
 * \param   mat    The matrix to free.
 * \param   nrows  The number of rows in the matrix.
 */
void mat_free(void **mat, int nrows);

/**
 * \brief Find the min and the max values in an array of double.
 *
 * \param   x         The array.
 * \param   length    Length of the array.
 * \param   min       Where to store the smallest value.
 * \param   max       Where to store the highest value.
 */
void dmin_max(double *x, int length, double *min, double *max);

/**
 * \brief Find the min and the max values in an array of int.
 *
 * \param   x         The array.
 * \param   length    Length of the array.
 * \param   min       Where to store the smallest value.
 * \param   max       Where to store the highest value.
 */
void imin_max(int *x, int length, int *min, int *max);

/**
 * \brief Scale all the values in the [0, 1] range.
 *
 * \param   x         The array.
 * \param   length    Length of the array.
 */
void scale_0_1(double *x, int length);

/**
 * \brief Scale all the values in the [0, 100] range.
 *
 * \param   x         The array.
 * \param   length    Length of the array.
 */
void scale_0_100(double *x, int length);

/**
 * Scale all the values in the [a, b] range.
 * 
 * \param   x         The array.
 * \param   length    Length of the array.
 */
void scale_a_b(double *x, int length, double a, double b);

/**
 * \brief Remove small elements of an array.
 * 
 * Remove from the array all the elements smaller than "smallest". The function
 * will reallocate memory & return the number of elements removed.
 *
 * \param   x         The array.
 * \param   length    Length of the array.
 * \param   smallest  Everything that is smaller than this will be removed.
 * \return            The number of elements removed.
 */
int trim_small(int **x, int length, int smallest);

/**
 * \brief Remove large elements of an array.
 * 
 * Remove from the array all the elements larger than "largest". The function
 * will reallocate memory & return the number of elements removed.
 *
 * \param   x         The array.
 * \param   length    Length of the array.
 * \param   largest   Everything that is larger than this will be removed.
 * \return            The number of elements removed.
 */
int trim_large(int **x, int length, int largest);

////////////////////////////////////////////////////////////////////
// Other functions

/**
 * \brief Get a non-zero unsigned integer from dev/random.
 *
 * This function is mostly useful to seed random number generators. It should
 * work on UNIX or UNIX-like operating systems (Linux, Solaris, AIX, BSD, UP-UX,
 * MacOSX).
 *
 * \return        An unsigned int from /dev/random.
 */
unsigned int devrandom_get_uint();

/**
 * \brief Get a non-zero unsigned integer from dev/urandom.
 *
 * This function is mostly useful to seed random number generators. It should
 * work on UNIX or UNIX-like operating systems (Linux, Solaris, AIX, BSD, UP-UX,
 * MacOSX).
 *
 * \return        An unsigned int from /dev/urandom.
 */
unsigned int devurandom_get_uint();

/**
 * \brief Compare two 'float' for the qsort function (ascending order).
 *
 * \param x       First value for the comparison.
 * \param y       Second value for the comparison.
 * \return        -1 if x < y, 1 if x > y, 0 if x == y.
 */
int compare_float_asc(const void *x, const void *y);

/**
 * \brief Compare two 'double' for the qsort function (ascending order).
 *
 * \param x       First value for the comparison.
 * \param y       Second value for the comparison.
 * \return        -1 if x < y, 1 if x > y, 0 if x == y.
 */
int compare_double_asc(const void *x, const void *y);

/**
 * \brief Compare two 'int' for the qsort function (ascending order).
 *
 * \param x       First value for the comparison.
 * \param y       Second value for the comparison.
 * \return        -1 if x < y, 1 if x > y, 0 if x == y.
 */
int compare_int_asc(const void *x, const void *y);

/**
 * \brief Compare two 'long' for the qsort function (ascending order).
 *
 * \param x       First value for the comparison.
 * \param y       Second value for the comparison.
 * \return        -1 if x < y, 1 if x > y, 0 if x == y.
 */
int compare_long_asc(const void *x, const void *y);

/**
 * \brief Compare two 'float' for the qsort function (ascending order).
 *
 * \param x       First value for the comparison.
 * \param y       Second value for the comparison.
 * \return        -1 if x > y, 1 if x < y, 0 if x == y.
 */
int compare_float_des(const void *x, const void *y);

/**
 * \brief Compare two 'double' for the qsort function (ascending order).
 *
 * \param x       First value for the comparison.
 * \param y       Second value for the comparison.
 * \return        -1 if x > y, 1 if x < y, 0 if x == y.
 */
int compare_double_des(const void *x, const void *y);

/**
 * \brief Compare two 'int' for the qsort function (ascending order).
 *
 * \param x       First value for the comparison.
 * \param y       Second value for the comparison.
 * \return        -1 if x > y, 1 if x < y, 0 if x == y.
 */
int compare_int_des(const void *x, const void *y);

/**
 * \brief Compare two 'long' for the qsort function (ascending order).
 *
 * \param x       First value for the comparison.
 * \param y       Second value for the comparison.
 * \return        -1 if x > y, 1 if x < y, 0 if x == y.
 */
int compare_long_des(const void *x, const void *y);

#ifdef __cplusplus
}
#endif

#endif
