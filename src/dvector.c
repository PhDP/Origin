#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "common.h"
#include "dvector.h"
#include "utils.h"

void dvector_init0(dvector *v)
{
    dvector_init1(v, VECTOR_INIT_CAPACITY);
}

void dvector_init1(dvector *v, unsigned int initial_capacity)
{
    v->array = (double*)malloc(initial_capacity * sizeof(double));
    v->size = 0;
    v->capacity = initial_capacity;
}

#ifndef NDEBUG 
O_INLINE double dvector_get(dvector *v, unsigned int n)
{
    assert(n < v->size);
    return v->array[n];
}

O_INLINE void dvector_set(dvector *v, unsigned int n, double x)
{
    assert(n < v->size);
    v->array[n] = x;
}

O_INLINE void dvector_rmv(dvector *v, unsigned int z)
{
    v->size = (v->size >= z) ? v->size - z : 0;
}

O_INLINE void dvector_rmv1(dvector *v)
{
    if (v->size > 0)
    {
        v->size--;
    }
}

O_INLINE void dvector_rmvall(dvector *v)
{
    v->size = 0;
}
#endif

O_INLINE void dvector_add(dvector *v, int x)
{
    // If the internal array is full, double its size;
    if (v->size == v->capacity)
    {
        dvector_grow1(v);
    }
    // Add the new nent at the end
    v->array[v->size] = x;
    v->size++;
}

O_INLINE double *dvector_get_array(dvector *v)
{
    const int size = v->size;
    double *new_array = (double*)malloc(size * sizeof(double)); // Only allocate memory for the active elements

    // Copy the elements to the new array
    for (int i = 0; i < size; ++i)
    {
        new_array[i] = v->array[i];
    }
    return new_array;
}

// TODO: USE REALLOC
O_INLINE void dvector_grow0(dvector *v, unsigned int new_capacity)
{
    v->array = (void*)realloc(v->array, new_capacity * sizeof(double));
}

O_INLINE void dvector_grow1(dvector *v)
{
    if (v->capacity == 0)
    {
        dvector_grow0(v, VECTOR_INIT_CAPACITY);
    }
    else
    {
        dvector_grow0(v, v->capacity * VECTOR_GROW_RATE);
    }
}

O_INLINE void dvector_sort_asc(dvector *v)
{
    qsort((void*)v->array, v->size, sizeof(double), compare_double_asc);
}

O_INLINE void dvector_sort_des(dvector *v)
{
    qsort((void*)v->array, v->size, sizeof(double), compare_double_des);
}

O_INLINE void dvector_free(dvector *v)
{
    free(v->array); // Free the memory of the vector
    v->array = NULL;
}

O_INLINE void dvector_print(dvector *v, FILE *out)
{
    const int size = v->size;
    if (out == NULL)
    {
        for (int i = 0; i < size; ++i)
        {
            printf("%.2f ", v->array[i]);
        }
    }
    else
    {
        for (int i = 0; i < size; ++i)
        {
            fprintf(out, "%.2f ", v->array[i]);
        }
    }
}
