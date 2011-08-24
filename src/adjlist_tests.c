// Generate random geometric graphs until a connected one is found.
//
// gcc -O3 -std=c99 -lm -lgsl -lgslcblas -o adjlisttest adjlist_tests.c adjlist.c utils.c maths.c

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <assert.h>
#include "adjlist.h"
#include "maths.h"
#include "utils.h"

int main(int argc, const char *argv[])
{
	// GSL's Taus generator:
	gsl_rng *rng = gsl_rng_alloc(gsl_rng_taus2);
	// Initialize the GSL generator with /dev/urandom:
	const unsigned int seed = devurandom_get_uint();
	gsl_rng_set(rng, seed);

	const int vertices = 10; // Number of vertices in the graph
	const double r = 0.20; // Min. radius
	int trials = 0; // Number of attempts before a connected graph is found
	double *x = (double*)malloc(vertices * sizeof(double)); // x-coordinates
	double *y = (double*)malloc(vertices * sizeof(double)); // x-coordinates

	adjlist a; // The graph.
	bool is_connected = false;

	while (is_connected == false)
	{
		++trials; // count the number of attemps
		adjlist_init(&a, vertices); // Init the graph.

		// The position of the vertices in two-dimentional space
		for (int i = 0; i < vertices; ++i)
		{
			x[i] = gsl_rng_uniform(rng);
			y[i] = gsl_rng_uniform(rng);
		}
		double d;
		for (int i = 0; i < vertices; ++i) 
		{
			for (int j = 0; j < vertices; ++j) 
			{
				const double x_ = x[i] - x[j];
				const double y_ = y[i] - y[j];
				d = hypot(x_, y_);
				if (d < r) 
				{
					adjlist_add_edge(&a, i, j, r - d);
				}
			}
		}
		++trials;
		// Free memory for the next graph
		
		is_connected = adjlist_strongly_connected(&a);
		if (is_connected == false)
		{
			adjlist_free(&a);
		}
	}

	adjlist_print(&a, NULL);
	printf("\n");
	adjlist_print_w(&a, NULL);
	printf("\n");
	adjlist_print_mat(&a, NULL);
	printf("\n");
	adjlist_print_w_mat(&a, NULL);
	printf("\n");
	printf("Trials: %d\n", trials);
	
	return EXIT_SUCCESS; // yeppie !
}
