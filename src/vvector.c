#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "common.h"
#include "vvector.h"
#include "utils.h"

void vvector_init0(vvector *v)
{
    vvector_init1(v, VECTOR_INIT_CAPACITY);
}

void vvector_init1(vvector *v, unsigned int initial_capacity)
{
    v->array = (void**)malloc(initial_capacity * sizeof(void*));
    v->size = 0;
    v->capacity = initial_capacity;
}

#ifndef NDEBUG 
O_INLINE void *vvector_get(vvector *v, unsigned int n)
{
    assert(n < v->size);
    return v->array[n];
}

O_INLINE void vvector_set(vvector *v, unsigned int n, void *x)
{
    assert(n < v->size);
    v->array[n] = x;
}

O_INLINE void vvector_rmv(vvector *v, unsigned int z)
{
    v->size = (v->size >= z) ? v->size - z : 0;
}

O_INLINE void vvector_sub1(vvector *v)
{
    if (v->size > 0)
    {
        v->size--;
    }
}

O_INLINE void vvector_rmvall(vvector *v)
{
    v->size = 0;
}
#endif

O_INLINE void vvector_add(vvector *v, void *x)
{
    // If the internal array is full, double its size;
    if (v->size == v->capacity)
    {
        vvector_grow1(v);
    }
    // Add the new nent at the end
    v->array[v->size] = x;
    v->size++;
}

O_INLINE void **vvector_get_array(vvector *v)
{
    const int size = v->size;
    void **new_array = (void**)malloc(size * sizeof(void*)); // Only allocate memory for the active elements

    // Copy the elements to the new array
    for (int i = 0; i < size; ++i)
    {
        new_array[i] = v->array[i];
    }
    return new_array;
}

O_INLINE void vvector_grow0(vvector *v, unsigned int new_capacity)
{
    v->array = (void*)realloc(v->array, new_capacity * sizeof(void*));
}

O_INLINE void vvector_grow1(vvector *v)
{
    if (v->capacity == 0)
    {
        vvector_grow0(v, VECTOR_INIT_CAPACITY);
    }
    else
    {
        vvector_grow0(v, v->capacity * VECTOR_GROW_RATE);
    }
}

void vvector_print(vvector *v, FILE *out)
{
    if (out == NULL)
    {
        for (int i = 0; i < v->size; ++i)
        {
            printf("%p ", v->array[i]);
        }
    }
    else
    {
        for (int i = 0; i < v->size; ++i)
        {
            fprintf(out, "%p ", v->array[i]);
        }
    }
}

O_INLINE void vvector_free(vvector *v)
{
    free(v->array); // Free the memory of the vector
    v->array = NULL;
}
