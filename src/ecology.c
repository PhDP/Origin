#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "ecology.h"

ORIGIN_INLINE int biodiversity_octaves(const int *a, int array_size, double **octaves)
{
    // Find the largest number in the supplied array:
    int largest = a[0];
    int i = 0;
    for (; i < array_size; ++i)
    {
        if (a[i] > largest)
        {
            largest = a[i];
        }
    }
    // Find how many abundance classes are going to be necessary:
    int oct_num = 1;
    int two_to_n = 1; // 2^n
    while (two_to_n <= largest)
    {
        ++oct_num;
        two_to_n <<= 1; // same as: two_to_n *= 2
    }
    // Allocate memory for the array and fill with 0.0:
    (*octaves) = (double*)malloc(oct_num * sizeof(double));
    for (i = 0; i < oct_num; ++i)
    {
        (*octaves)[i] = 0.0;
    }
    // Fill the abundance classes:
    int abundance_class; //
    for (i = 0; i < array_size; ++i)
    {
        if (a[i] != 0)
        {
            abundance_class = 0;
            two_to_n = 1; // 2^n
            // Find the right abundance class to for this element of the array:
            while (two_to_n < a[i])
            {
                ++abundance_class;
                two_to_n <<= 1;
            }
            // if x[i] is a power of two, split between two classes:
            if ((a[i] & (a[i] - 1)) == 0)
            {
                (*octaves)[abundance_class] += 0.5;
                (*octaves)[abundance_class + 1] += 0.5;
            }
            else
            {
                (*octaves)[abundance_class] += 1.0;
            }
        }
    }
    return oct_num;
}
