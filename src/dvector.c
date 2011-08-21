#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "hon.h"
#include "dvector.h"
#include "utils.h"

void dvector_init0(dvector *v)
{
	dvector_init1(v, VECTOR_INIT_CAPACITY);
}

void dvector_init1(dvector *v, int initial_capacity)
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

inline void dvector_add(dvector *v, int x)
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

inline void dvector_sub(dvector *v, int x)
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

inline void dvector_sub1(dvector *v)
{
	if (v->size > 0)
	{
		v->size--;
	}
}

inline double *dvector_get_array(dvector *v)
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

inline void dvector_grow0(dvector *v, int new_capacity)
{
	// The new array
	double *new_array = (double*)malloc(new_capacity* sizeof(double));

	// Copy the elements from the old to the new array
	const int size = v->size;
	for (int i = 0; i < size; ++i)
	{
		new_array[i] = v->array[i];
	}
	v->capacity = new_capacity; // Change the capacity
	double *swap = v->array; // Used to swap the pointers
	v->array = new_array; // Set the dynamic a's pointer to the new a
	free(swap); // Free the memory of the old a
}

inline void dvector_grow1(dvector *v)
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

inline void dvector_sort_asc(dvector *v)
{
	qsort((void*)v->array, v->size, sizeof(double), compare_double_asc);
}

inline void dvector_sort_des(dvector *v)
{
	qsort((void*)v->array, v->size, sizeof(double), compare_double_des);
}

inline void dvector_free(dvector *v)
{
	free(v->array); // Free the memory of the vector
	v->array = NULL;
}

inline void dvector_print(dvector *v, FILE *out)
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

void dvector_examples()
{
	dvector v1;
	dvector v2;
	
	dvector_init0(&v1);
	dvector_init1(&v2, 3);
	
	for (int i = 0; i < 10; ++i)
	{
		dvector_add(&v1, (double)i);
		dvector_add(&v2, (double)i);
	}

	printf("v1 (n = %d, capacity = %d): ", v1.size, v1.capacity);
	dvector_print(&v1, NULL);  
	printf("\n");
	printf("v2 (n = %d, capacity = %d): ", v2.size, v2.capacity);
	dvector_print(&v2, NULL);  
	printf("\n");

	for (int i = 10; i < 15; ++i)
	{
		dvector_add(&v1, (double)i);
	}
	
	printf("v1 (n = %d, capacity = %d): ", v1.size, v1.capacity);
	dvector_print(&v1, NULL);  
	printf("\n");
	printf("v2 (n = %d, capacity = %d): ", v2.size, v2.capacity);
	dvector_print(&v2, NULL);  
	printf("\n");
	
	dvector_sub1(&v1);
	dvector_sub(&v2, 8);
	
	printf("v1 (n = %d, capacity = %d): ", v1.size, v1.capacity);
	dvector_print(&v1, NULL);  
	printf("\n");
	printf("v2 (n = %d, capacity = %d): ", v2.size, v2.capacity);
	dvector_print(&v2, NULL);  
	printf("\n");
	
	dvector_free(&v1);  
	dvector_free(&v2);
}
