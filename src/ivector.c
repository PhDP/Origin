#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "common.h"
#include "ivector.h"
#include "utils.h"

void ivector_init0(ivector *v)
{
    ivector_init1(v, VECTOR_INIT_CAPACITY);
}

void ivector_init1(ivector *v, int initial_capacity)
{
    v->array = (int*)malloc(initial_capacity * sizeof(int));
    v->size = 0;
    v->capacity = initial_capacity;
}

void ivector_init2(ivector *v, int *x, int size, int initial_capacity)
{
    assert(size <= initial_capacity);
    v->array = (int*)malloc(initial_capacity * sizeof(int));
    v->size = size;
    v->capacity = initial_capacity;
    
    for (int i = 0; i < size; ++i)
    {
        v->array[i] = x[i];
    }
}

ORIGIN_INLINE void ivector_grow0(ivector *v, int new_capacity)
{
    // The new array
    int *new_array = (int*)malloc(new_capacity * sizeof(int));

    // Copy the elements from the old to the new array
    const int size = v->size;
    for (int i = 0; i < size; ++i)
    {
        new_array[i] = v->array[i];
    }

    v->capacity = new_capacity; // Change the max
    int *swap = v->array; // Used to swap the pointers
    v->array = new_array; // Set the dynamic a's pointer to the new a
    free(swap); // Free the memory of the old a
}

ORIGIN_INLINE void ivector_grow1(ivector *v)
{
    // Double the internal storage
    if (v->capacity == 0)
    {
        ivector_grow0(v, VECTOR_INIT_CAPACITY);
    }
    else
    {
        ivector_grow0(v, v->capacity * VECTOR_GROW_RATE);
    }
}

#ifndef NDEBUG
ORIGIN_INLINE int ivector_get(ivector *v, int n)
{
    assert(n < v->size);
    return v->array[n];
}

ORIGIN_INLINE void ivector_set(ivector *v, int n, int x)
{
    assert(n < v->size);
    v->array[n] = x;
}
#endif

ORIGIN_INLINE void ivector_add(ivector *v, int x)
{
    // If the internal array is full, double its size;
    if (v->size == v->capacity)
    {
        ivector_grow1(v);
    }
    // Add the new nent at the end
    v->array[v->size] = x;
    v->size++;
}

ORIGIN_INLINE void ivector_add_array(ivector *v, int *a, int size)
{
    // If there isn't enough space, double the size until it can contain 'a'
    const int old_size = v->size;
    while (v->capacity < old_size + size)
    {
        ivector_grow1(v);
    }
    for (int i = 0; i < size; ++i)
    {
        v->array[old_size + i] = a[i];
    }	
    v->size += size;
}

ORIGIN_INLINE void ivector_sub(ivector *v, int x)
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

ORIGIN_INLINE void ivector_rmvall(ivector *v)
{
    v->size = 0;
}

ORIGIN_INLINE void ivector_sub1(ivector *v)
{
    if (v->size > 0)
    {
        v->size--;
    }
}

ORIGIN_INLINE int *ivector_get_array(ivector *v)
{
    const int size = v->size;
    int *new_array = (int*)malloc(size * sizeof(int)); // Only allocate memory for the active elements

    // Copy the elements to the new array
    for (int i = 0; i < size; ++i)
    {
        new_array[i] = v->array[i];
    }
    return new_array;
}

ORIGIN_INLINE void ivector_sort_asc(ivector *v)
{
    qsort((void*)v->array, v->size, sizeof(int), compare_int_asc);
}

ORIGIN_INLINE void ivector_sort_des(ivector *v)
{
    qsort((void*)v->array, v->size, sizeof(int), compare_int_des);
}

ORIGIN_INLINE int ivector_trim_small(ivector *v, int smallest)
{
    int i = 0;
    int j = 0;
    while (j < v->size)
    {
        if (v->array[j] >= smallest)
        {
            v->array[i] = v->array[j];
            ++i;
        }
        ++j;
    }	
    const int removed = j - i;
    v->size -= removed;
    
    return removed;
}

ORIGIN_INLINE int ivector_trim_large(ivector *v, int largest)
{
    int i = 0;
    int j = 0;
    while (j < v->size)
    {
        if (v->array[j] <= largest)
        {
            v->array[i] = v->array[j];
            ++i;
        }
        ++j;
    }	
    const int removed = j - i;
    v->size -= removed;
    
    return removed;
}

void ivector_print(ivector *v, FILE *out)
{
    if (out == NULL)
    {
        for (int i = 0; i < v->size; ++i)
        {
            printf("%d ", v->array[i]);
        }
    }
    else
    {
        for (int i = 0; i < v->size; ++i)
        {
            fprintf(out, "%d ", v->array[i]);
        }
    }
}

ORIGIN_INLINE void ivector_free(ivector *v)
{
    free(v->array); // Free the memory of the vector
    v->array = NULL;
}

void ivector_examples()
{
    ivector v;
    ivector_init0(&v);
    
    for (int i = 0; i < 20; ++i)
    {
        ivector_add(&v, i*i - 7*i);
    }

    printf("v (n = %d, capacity = %d): ", v.size, v.capacity);
    ivector_print(&v, NULL);
    printf("\n");

    ivector_sort_des(&v);

    printf("v (n = %d, capacity = %d): ", v.size, v.capacity);
    ivector_print(&v, NULL);
    printf("\n");

    ivector_sort_asc(&v);

    printf("v (n = %d, capacity = %d): ", v.size, v.capacity);
    ivector_print(&v, NULL);
    printf("\n");

    ivector_trim_small(&v, 0);
    ivector_trim_large(&v, 100);

    printf("v (n = %d, capacity = %d): ", v.size, v.capacity);
    ivector_print(&v, NULL);
    printf("\n");

    printf("Element #4: %d\n", ivector_get(&v, 4));
    
    ivector_set(&v, 4, 15);
    ivector_sub(&v, 3);
    
    printf("v (n = %d, capacity = %d): ", v.size, v.capacity);
    ivector_print(&v, NULL);
    printf("\n");

    ivector_free(&v);  
}
