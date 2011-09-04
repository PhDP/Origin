#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include "graph.h"
#include "graphgen.h"
#include "maths.h"

void graph_get_rgg(graph *g, int vertices, double r, double *x, double *y, gsl_rng *rng)
{
	graph_init(g, vertices);
	
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
			const double a = x[i] - x[j];
			const double b = y[i] - y[j];
			d = hypot(a, b);
			if (d < r) 
			{
				graph_add_edge(g, i, j, r - d);
			}
		}
	}
}

void graph_get_crgg(graph *g, int vertices, double r, double *x, double *y, gsl_rng *rng)
{
	graph_init(g, vertices);
	graph_get_rgg(g, vertices, r, x, y, rng);

	while (graph_strongly_connected(g) == false)
	{
		graph_free(g);
		graph_get_rgg(g, vertices, r, x, y, rng);
	}
}

void graph_get_rec_rgg(graph *g, int vertices, double width, double r, double *x, double *y, gsl_rng *rng)
{
	graph_init(g, vertices);
	
	const double length = 1.0 / width; // A = l * w so l = 1 / w

	for (int i = 0; i < vertices; ++i) 
	{
		x[i] = gsl_rng_uniform(rng) * length;
		y[i] = gsl_rng_uniform(rng) * width;
	}
	double d;
	for (int i = 0; i < vertices; ++i) 
	{
		for (int j = 0; j < vertices; ++j) 
		{
			d = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
			if (d < r)
			{
				graph_add_edge(g, i, j, r - d);
			}
		}
	}
}

void graph_get_rec_crgg(graph *g, int vertices, double width, double r, double *x, double *y, gsl_rng *rng)
{
	graph_init(g, vertices);
	graph_get_rec_rgg(g, vertices, width, r, x, y, rng);

	while (graph_strongly_connected(g) == false) 
	{
		graph_free(g);
		graph_get_rec_rgg(g, vertices, width, r, x, y, rng);
	}
}

void graph_get_complete(graph *g, int vertices)
{
	graph_init(g, vertices);
	
	for (int i = 0; i < vertices; ++i) 
	{
		for (int j = 0; j < vertices; ++j) 
		{
			graph_add_edge(g, i, j, 1.0);
		}
	}
}

void graph_get_circle(graph *g, int vertices)
{
	graph_init(g, vertices);
	
	graph_add_edge(g, vertices - 1, vertices - 1, 1.0);
	graph_add_sym_edges(g, 0, vertices - 1, 1.0);
	
	for (int u = 0; u < vertices - 1; ++u)
	{
		graph_add_edge(g, u, u, 1.0);
		graph_add_sym_edges(g, u, u + 1, 1.0);
	}
}

void graph_get_star(graph *g, int vertices)
{
	graph_init(g, vertices);
	
	for (int u = 0; u < vertices; ++u)
	{
		graph_add_edge(g, u, u, 1.0);
		graph_add_sym_edges(g, u, 0, 1.0);
	}
}
