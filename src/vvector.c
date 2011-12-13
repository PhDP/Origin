#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "common.h"
#include "vvector.h"

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
void *vvector_get(vvector *v, int n)
{
    assert(n < v->size);
    return v->array[n];
}

void vvector_set(vvector *v, int n, void *x)
{
    assert(n < v->size);
    v->array[n] = x;
}
#endif

ORIGIN_INLINE void vvector_add(vvector *v, void *x)
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

ORIGIN_INLINE void vvector_sub(vvector *v, int x)
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

ORIGIN_INLINE void vvector_sub1(vvector *v)
{
    if (v->size > 0)
    {
        v->size--;
    }
}

ORIGIN_INLINE void **vvector_get_array(vvector *v)
{
    const int size = v->size;
    void **new_array = (void**)malloc(size * sizeof(void*)); // Only allocate memory for the active elements

    // Copy the elements to the new array
    int i = 0;
    for (; i < size; ++i)
    {
        new_array[i] = v->array[i];
    }
    return new_array;
}

ORIGIN_INLINE void vvector_grow0(vvector *v, unsigned int new_capacity)
{
    v->array = (void**)realloc(v->array, new_capacity * sizeof(void*));
}

ORIGIN_INLINE void vvector_grow1(vvector *v)
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

ORIGIN_INLINE void vvector_free(vvector *v)
{
    free(v->array);
}
