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
double dvector_get(dvector *v, int n)
{
    assert(n < v->size);
    return v->array[n];
}

void dvector_set(dvector *v, int n, double x)
{
    assert(n < v->size);
    v->array[n] = x;
}
#endif

ORIGIN_INLINE void dvector_add(dvector *v, int x)
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

ORIGIN_INLINE void dvector_sub(dvector *v, int x)
{
    if (v->size >= x)
    {
        v->size -= x;
    }
    else
    {
        v->size = 0;
    }
}

ORIGIN_INLINE void dvector_sub1(dvector *v)
{
    if (v->size > 0)
    {
        v->size--;
    }
}

ORIGIN_INLINE double *dvector_get_array(dvector *v)
{
    const int size = v->size;
    double *new_array = (double*)malloc(size * sizeof(double)); // Only allocate memory for the active elements

    // Copy the elements to the new array
    int i = 0;
    for (; i < size; ++i)
    {
        new_array[i] = v->array[i];
    }
    return new_array;
}

ORIGIN_INLINE void dvector_grow0(dvector *v, unsigned int new_capacity)
{
    v->array = (double*)realloc(v->array, new_capacity * sizeof(double));
}

ORIGIN_INLINE void dvector_grow1(dvector *v)
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

ORIGIN_INLINE void dvector_sort_asc(dvector *v)
{
    qsort((void*)v->array, v->size, sizeof(double), compare_double_asc);
}

ORIGIN_INLINE void dvector_sort_des(dvector *v)
{
    qsort((void*)v->array, v->size, sizeof(double), compare_double_des);
}

ORIGIN_INLINE void dvector_print(dvector *v, FILE *out)
{
    const int size = v->size;
    int i = 0;
    for (; i < size; ++i)
    {
        fprintf(out, "%.2f ", v->array[i]);
    }
}

ORIGIN_INLINE void dvector_free(dvector *v)
{
    free(v->array);
}

void dvector_examples()
{
    dvector v1;
    dvector v2;

    dvector_init0(&v1);
    dvector_init1(&v2, 3);

    int i = 0;
    for (; i < 10; ++i)
    {
        dvector_add(&v1, (double)i);
        dvector_add(&v2, (double)i);
    }
    printf("v1 (n = %d, capacity = %d): ", v1.size, v1.capacity);
    dvector_print(&v1, stdout);
    printf("\n");
    printf("v2 (n = %d, capacity = %d): ", v2.size, v2.capacity);
    dvector_print(&v2, stdout);
    printf("\n");

    for (i = 10; i < 15; ++i)
    {
        dvector_add(&v1, (double)i);
    }
    printf("v1 (n = %d, capacity = %d): ", v1.size, v1.capacity);
    dvector_print(&v1, stdout);  
    printf("\n");
    printf("v2 (n = %d, capacity = %d): ", v2.size, v2.capacity);
    dvector_print(&v2, stdout);  
    printf("\n");

    dvector_sub1(&v1);
    dvector_sub(&v2, 8);

    printf("v1 (n = %d, capacity = %d): ", v1.size, v1.capacity);
    dvector_print(&v1, stdout);
    printf("\n");
    printf("v2 (n = %d, capacity = %d): ", v2.size, v2.capacity);
    dvector_print(&v2, stdout);
    printf("\n");

    dvector_free(&v1);  
    dvector_free(&v2);
}
