// gcc -std=c99 -lm -o tests tests.c dvector.c ivector.c utils.c stats.c well1024.c

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "dvector.h"
#include "ivector.h"
#include "well1024.h"
#include "stats.h"

int main(int argc, char* argv[])
{
	well1024 rng;
	well1024_init(&rng, 42);
	
	dvector_examples();

	printf("\n\n");

	ivector_examples();

	const int length = 100;
	double *x = (double*)malloc(length * sizeof(double));
	for (int i = 0; i < length; ++i)
	{
		const double r = well1024_next_double(&rng);
		x[i] = r * r * r * r * r * r * 100000;
	}
	for (int i = 0; i < length; ++i)
	{
		printf("%.4f ", x[i]);
	}
	printf("\n");

	printf("Naive sum = %.8f\n", dnaivesum(x, length));
	printf("Sort sum = %.8f\n", dsortsum(x, length));
	printf("Naive mean = %.8f\n", dnaivemean(x, length));
	printf("Mean = %.8f\n", dmean(x, length));
	printf("Variance = %.8f\n", dvar(x, length));
	printf("Kutorsis = %.8f\n", dkutorsis(x, length));
	
	return EXIT_SUCCESS; // Yeppie !
}
