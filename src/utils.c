#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "common.h"
#include "utils.h"

////////////////////////////////////////////////////////////////////
// Operations on matrices and arrays

void **mat_alloc(int nrows, int ncols, size_t size)
{
    void **matrix = (void**)malloc(nrows * sizeof(void*));

    int i;
    for (i = 0; i < nrows; ++i)
    {
        matrix[i] = malloc(ncols * size);
    }
    return matrix;
}

void mat_free(void **mat, int nrows)
{
    int i;
    for (i = 0; i < nrows; ++i)
    {
        free(mat[i]);
    }
    free(mat);
}

void dmin_max(double *x, int length, double *min, double *max)
{
    *min = x[0];
    *max = x[0];
    // Find the min and max values in the array:
    int i;
    for (i = 0; i < length; ++i)
    {
        if (*max < x[i])
        {
            *max = x[i];
        }
        else if (*min > x[i])
        {
            *min = x[i];
        }
    }
}

void imin_max(int *x, int length, int *min, int *max)
{
    *min = x[0];
    *max = x[0];
    // Find the min and max values in the array:
    int i;
    for (i = 0; i < length; ++i)
    {
        if (*max < x[i])
        {
            *max = x[i];
        }
        else if (*min > x[i])
        {
            *min = x[i];
        }
    }
}

void scale_0_1(double *x, int length)
{
    double min;
    double max;	
    dmin_max(x, length, &min, &max);

    // Scaling
    int i;
    for (i = 0; i < length; ++i)
    {
        x[i] = (x[i] - min) / (max - min);
    }
}

void scale_0_100(double *x, int length)
{
    double min;
    double max;	
    dmin_max(x, length, &min, &max);

    // Scaling
    int i;
    for (i = 0; i < length; ++i)
    {
        x[i] = (x[i] - min) / (max - min) * 100;
    }
}

void scale_a_b(double *x, int length, double a, double b)
{
    const double delta = b - a;
    scale_0_1(x, length);

    int i;
    for (i = 0; i < length; ++i)
    {
        x[i] = x[i] * delta + a;
    }
}

int trim_small(int **x, int length, int smallest)
{
    int i = 0;
    int j = 0;
    while (j < length)
    {
        if ((*x)[j] >= smallest)
        {
            (*x)[i] = (*x)[j];
            ++i;
        }
        ++j;
    }	
    const int removed = j - i;
    
    *x = (int*)realloc((void*)(*x), (length - removed) * sizeof(int));
    
    return removed;
}

int trim_large(int **x, int length, int largest)
{
    int i = 0;
    int j = 0;
    while (j < length)
    {
        if ((*x)[j] <= largest)
        {
            (*x)[i] = (*x)[j];
            ++i;
        }
        ++j;
    }	
    const int removed = j - i;
    
    *x = (int*)realloc((void*)(*x), (length - removed) * sizeof(int));
    
    return removed;
}

unsigned int devrandom_get_uint()
{
    FILE *f = fopen("/dev/random", "r");

    unsigned int x = 0; // The number to return
    size_t r;
    
    do
    {
        r = fread(&x, sizeof(unsigned int), 1, f);
    }
    while (x == 0);
    
    assert(r == 1);

    fclose(f);
    return x;
}

unsigned int devurandom_get_uint()
{
    FILE *f = fopen("/dev/urandom", "r");

    unsigned int x = 0; // The number to return
    size_t r;
    do
    {
        r = fread(&x, sizeof(unsigned int), 1, f);
    }
    while (x == 0);

    assert(r == 1);

    fclose(f);
    return x;
}

int compare_float_asc(const void *x, const void *y)
{
    if (*(float*)x < *(float*)y)
    {
        return -1;
    }
    else if (*(float*)x > *(float*)y)
    {
        return 1;
    }
    return 0;
}

int compare_double_asc(const void *x, const void *y)
{
    if (*(double*)x < *(double*)y)
    {
        return -1;
    }
    else if (*(double*)x > *(double*)y)
    {
        return 1;
    }
    return 0;
}

int compare_int_asc(const void *x, const void *y)
{
    if (*(int*)x < *(int*)y)
    {
        return -1;
    }
    else if (*(int*)x > *(int*)y)
    {
        return 1;
    }
    return 0;
}

int compare_long_asc(const void *x, const void *y)
{
    if (*(long*)x < *(long*)y)
    {
        return -1;
    }
    else if (*(long*)x > *(long*)y)
    {
        return 1;
    }
    return 0;
}

int compare_float_des(const void *x, const void *y)
{
    if (*(float*)x > *(float*)y)
    {
        return -1;
    }
    else if (*(float*)x < *(float*)y)
    {
        return 1;
    }
    return 0;
}

int compare_double_des(const void *x, const void *y)
{
    if (*(double*)x > *(double*)y)
    {
        return -1;
    }
    else if (*(double*)x < *(double*)y)
    {
        return 1;
    }
    return 0;
}

int compare_int_des(const void *x, const void *y)
{
    if (*(int*)x > *(int*)y)
    {
        return -1;
    }
    else if (*(int*)x < *(int*)y)
    {
        return 1;
    }
    return 0;
}

int compare_long_des(const void *x, const void *y)
{
    if (*(long*)x > *(long*)y)
    {
        return -1;
    }
    else if (*(long*)x < *(long*)y)
    {
        return 1;
    }
    return 0;
}
