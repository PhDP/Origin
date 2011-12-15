#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <time.h>
#include "common.h"
#include "utils.h"

char *get_opt_s(const char *arg)
{
    const int length = strlen(arg);
    int n = 0;
    while (n < length && arg[n] != '=')
    {
        ++n;
    }
    if (arg[n] != '=')
    {
        return NULL;
    }

    const int ss_length = length - n; // - 1 ('=') + 1 ('\0')
    char *substring = (char*)malloc(ss_length);

    for (int i = 0; i < ss_length - 1; ++i)
    {
        substring[i] = arg[i + n + 1];
    }
    substring[ss_length - 1] = '\0';

    return substring;
}

int get_opt_i(const char *arg)
{
    char *str = get_opt_s(arg);
    const int number = atoi(str);
    free(str);
    return number;
}

double get_opt_d(const char *arg)
{
    char *str = get_opt_s(arg);
    const double number = atof(str);
    free(str);
    return number;
}

bool read_opt_i(const char *option, const char *argv[], int n, int *param)
{
    const int length = strlen(option);
    
    for (int i = 0; i < n; ++i)
    {
        int j = 0;
        const int inplen = strlen(argv[i]);
        while (j < length)
        {
            if (inplen < j + 1 || argv[i][j + 1] != option[j])
            {
                break;
            }
            else
            {
                ++j;
            }
        }
        if (j == length && argv[i][length + 1] == '=')
        {
            *param = get_opt_i(argv[i]);
            return true;
        }
    }
    return false;
}

bool read_opt_d(const char *option, const char *argv[], int n, double *param)
{
    const int length = strlen(option);
    
    for (int i = 0; i < n; ++i)
    {
        int j = 0;
        const int inplen = strlen(argv[i]);
        while (j < length)
        {
            if (inplen < j + 1 || argv[i][j + 1] != option[j])
            {
                break;
            }
            else
            {
                ++j;
            }
        }
        if (j == length && argv[i][length + 1] == '=')
        {
            *param = get_opt_d(argv[i]);
            return true;
        }
    }
    return false;
}

bool read_opt_s(const char *option, const char *argv[], int n, char *param)
{
    const int length = strlen(option);
    
    for (int i = 1; i < n; ++i)
    {
        int j = 0;
        const int inplen = strlen(argv[i]);
        while (j < length)
        {
            if (inplen < j + 1 || argv[i][j + 1] != option[j])
            {
                break;
            }
            else
            {
                ++j;
            }
        }
        if (j == length && argv[i][length + 1] == '=')
        {
            sprintf(param, "%s", get_opt_s(argv[i]));
            return true;
        }
    }
    return false;
}

char *sec_to_string(long seconds)
{
    char *str = (char*)malloc(21);

    const long d = seconds / (60 * 60 * 24);
    const long h = seconds / (60 * 60) - (d * 24);
    const long m = seconds / 60 - (h * 60) - (d * 24 * 60);
    const long s = seconds % 60;

    if (d > 0)
    {
        sprintf(str, "%ld d %ld h %ld m %ld s", d, h, m, s);
    }
    else if (h > 0)
    {
        sprintf(str, "%ld h %ld m %ld s", h, m, s);
    }
    else if (m > 0)
    {
        sprintf(str, "%ld m %ld s", m, s);
    }
    else
    {
        sprintf(str, "%ld s", s);
    }
    return str;
}

char *int_with_space(int integer)
{
    char *str0 = (char*)malloc(11); // String without spaces
    sprintf(str0, "%d", integer);

    const int length0 = strlen(str0); // Size of the string without spaces
    const int length1 = length0 + (length0 - 1) / 3; // Size of the new string

    char *str1 = (char*)malloc(length1 + 1);
    str1[length1] = '\0';

    int next_space = (length0 % 3) == 0 ? 3 : (length0 % 3);

    int i0 = 0; // Index for the old string
    for (int i1 = 0; i1 < length1; ++i1)
    {
        if (i1 == next_space)
        {
            str1[i1] = UTILS_SEPARATOR;
            next_space += 4;
        }
        else
        {
            str1[i1] = str0[i0++];
        }
    }
    free(str0);
    return str1;
}

char *long_with_space(long integer)
{
    char *str0 = (char*)malloc(21); // String without spaces
    sprintf(str0, "%ld", integer);

    const int length0 = strlen(str0); // Size of the string without spaces
    const int length1 = length0 + (length0 - 1) / 3; // Size of the new string

    char *str1 = (char*)malloc(length1 + 1);
    str1[length1] = '\0';

    int next_space = (length0 % 3) == 0 ? 3 : (length0 % 3);

    int i0 = 0; // Index for the old string
    for (int i1 = 0; i1 < length1; ++i1)
    {
        if (i1 == next_space)
        {
            str1[i1] = UTILS_SEPARATOR;
            next_space += 4;
        }
        else
        {
            str1[i1] = str0[i0++];
        }
    }
    free(str0);
    return str1;
}

void convert_to_lower_case(char *str)
{
    const int length = strlen(str);

    for (int i = 0; i < length; ++i)
    {
        if (str[i] >= 0x41 && str[i] <= 0x5A)
        {
            str[i] += 0x20;
        }
    }
}

void convert_to_upper_case(char *str)
{
    const int length = strlen(str);

    for (int i = 0; i < length; ++i)
    {
        if (str[i] >= 0x61 && str[i] <= 0x7A)
        {
            str[i] -= 0x20;
        }
    }
}

char *get_lower_case(const char *str)
{
    const int length = strlen(str);
    char *new_str = (char*)malloc(length + 1);

    for (int i = 0; i < length; ++i)
    {
        if (str[i] >= 0x41 && str[i] <= 0x5A)
        {
            new_str[i] = str[i] + 0x20;
        }
        else
        {
            new_str[i] = str[i];
        }
    }
    new_str[length] = '\0';
    return new_str;
}

char *get_upper_case(const char *str)
{
    const int length = strlen(str);
    char *new_str = (char*)malloc(length + 1);

    for (int i = 0; i < length; ++i)
    {
        if (str[i] >= 0x61 && str[i] <= 0x7A)
        {
            new_str[i] = str[i] - 0x20;
        }
        else
        {
            new_str[i] = str[i];
        }
    }
    new_str[length] = '\0';
    return new_str;
}


////////////////////////////////////////////////////////////////////
// Operations on matrices and arrays

void **mat_alloc(int nrows, int ncols, size_t size)
{
    void **matrix = (void**)malloc(nrows * sizeof(void*));

    for (int i = 0; i < nrows; ++i)
    {
        matrix[i] = malloc(ncols * size);
    }
    return matrix;
}

void mat_free(void **mat, int nrows)
{
    for (int i = 0; i < nrows; ++i)
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
    for (int i = 0; i < length; ++i)
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
    for (int i = 0; i < length; ++i)
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
    for (int i = 0; i < length; ++i)
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
    for (int i = 0; i < length; ++i)
    {
        x[i] = (x[i] - min) / (max - min) * 100;
    }
}

void scale_a_b(double *x, int length, double a, double b)
{
    const double delta = b - a;
    scale_0_1(x, length);

    for (int i = 0; i < length; ++i)
    {
        x[i] = x[i] * delta + a;
    }
}

int trim_small(int **x, int elements, int smallest)
{
    int i = 0;
    int j = 0;
    while (j < elements)
    {
        if ((*x)[j] >= smallest)
        {
            (*x)[i] = (*x)[j];
            ++i;
        }
        ++j;
    }	
    const int removed = j - i;
    
    *x = (int*)realloc((void*)(*x), (elements - removed) * sizeof(int));
    
    return removed;
}

int trim_large(int **x, int elements, int largest)
{
    int i = 0;
    int j = 0;
    while (j < elements)
    {
        if ((*x)[j] <= largest)
        {
            (*x)[i] = (*x)[j];
            ++i;
        }
        ++j;
    }	
    const int removed = j - i;
    
    *x = (int*)realloc((void*)(*x), (elements - removed) * sizeof(int));
    
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

double hypot(double a, double b)
{
    if (fabs(a) > fabs(b))
    {
        const double r = b / a;
        return fabs(a) * sqrt(1 + r * r);
    }
    else if (b != 0.0)
    {
        const double r = a / b;
        return fabs(b) * sqrt(1 + r * r);
    }
    else
    {
        return 0.0;
    }
}

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

ORIGIN_INLINE double dnaivesum(const double *x, int length)
{
    double sum = 0.0;

    for (int i = 0; i < length; ++i)
    {
        sum += x[i];
    }
    return sum;
}

ORIGIN_INLINE double dsortsum(const double *x, int length)
{
    // Copy the array & sort it with quicksort.
    double *sorted = (double*)malloc(length * sizeof(double));
    memcpy((void*)sorted, (void*)x, length * sizeof(double));
    qsort((void*)sorted, length, sizeof(double), compare_double_asc);

    const double sum = dnaivesum(sorted, length); // The actual answer
    free(sorted); // Free memory

    return sum;
}

// So simple with integers...
ORIGIN_INLINE int isum(const int *x, int length)
{
    int sum = 0;

    for (int i = 0; i < length; ++i)
    {
        sum += x[i];
    }
    return sum;
}

ORIGIN_INLINE long lsum(const long *x, int length)
{
    long sum = 0;

    for (int i = 0; i < length; ++i)
    {
        sum += x[i];
    }
    return sum;
}

double dnaivemean(const double *x, int length)
{
    return dnaivesum(x, length) / length;
}

double dmean(const double *x, int length)
{
    return dsortsum(x, length) / length;
}

double imean(const int *x, int length)
{
    return ((double)isum(x, length)) / length;
}

double lmean(const long *x, int length)
{
    return ((double)lsum(x, length)) / length;
}

void dvarmean(const double *x, int length, double *mean, double *var)
{
    double m = 0.0;
    double m2 = 0.0;
    double delta;

    for (int i = 0; i < length; ++i)
    {
        delta = x[i] - m;
        m += delta / (i + 1);
        m2 += delta * (x[i] - m);
    }

    (*mean) = m;
    (*var) =  m2 / (length - 1);
}

double dvar(const double *x, int length)
{
    double m = 0.0;
    double m2 = 0.0;
    double delta;

    for (int i = 0; i < length; ++i)
    {
        delta = x[i] - m;
        m += delta / (i + 1);
        m2 += delta * (x[i] - m);
    }

    return m2 / (length - 1);
}

double dkutorsis(const double *x, int length)
{
    double m1 = 0.0, m2 = 0.0, m3 = 0.0, m4 = 0.0;
    double i1, term1, delta, delta_n, delta_n2;

    for (int i = 0; i < length; ++i)
    {
        i1 = (double)(i + 1);
        delta = x[i] - m1;
        delta_n = delta / i1;
        delta_n2 = delta_n * delta_n;
        term1 = delta * delta_n * i;
        m1 += delta_n;
        m4 += term1 * delta_n2 * (i1 * i1 - 3 * i1 + 3) + 6 * delta_n2 * m2 - 4 * delta_n * m3;
        m3 += term1 * delta_n * (i1 - 2) - 3 * delta_n * m2;
        m2 += term1;
    }
    return (length * m4) / (m2 * m2) - 3;
}

double dmedian(const double *x, int length)
{
    if (length == 0)
    {
        return 0;
    }
    else if (length == 1)
    {
        return x[0];
    }
    double *sorted = (double*)malloc(length * sizeof(double));
    memcpy((void*)sorted, (void*)x, length * sizeof(double));
    qsort((void*)sorted, length, sizeof(double), compare_double_asc);

    const int m = length / 2;
    const double answer = (length % 2 == 1) ? sorted[m] : (sorted[m - 1] + sorted[m]) / 2.0;

    free(sorted);	
    return answer;
}

// Better algorithm ?
double imedian(const int *x, int length)
{
    if (length == 0)
    {
        return 0;
    }
    else if (length == 1)
    {
        return x[0];
    }
    int *sorted = (int*)malloc(length * sizeof(int));
    memcpy((void*)sorted, (void*)x, length * sizeof(int));
    qsort((void*)sorted, length, sizeof(int), compare_int_asc);

    const int m = length / 2;
    const double answer = (length % 2 == 1) ? sorted[m] : (sorted[m - 1] + sorted[m]) / 2.0;

    free(sorted);	
    return answer;
}
