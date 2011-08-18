#ifndef graph_GENERATORS_H_
#define graph_GENERATORS_H_

#include <stdbool.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include "graph.h"

// For C++ compilers:
#ifdef __cplusplus
extern "C" {
#endif

/** Get a random geometric graph in [0,1]^2 with radius 'r'. */
void graph_get_rgg(graph *g, int vertices, double r, double *x, double *y, gsl_rng *rng);

/** Initialize a graph with a fixed number of vertices. */
void graph_get_crgg(graph *g, int vertices, double r, double *x, double *y, gsl_rng *rng);

/** Get a random geometric graph in a rectangle with an area of 1 and with radius 'r'. */
void graph_get_rec_rgg(graph *g, int vertices, double width, double r, double *x, double *y, gsl_rng *rng);

/** Initialize a graph with a fixed number of vertices. */
void graph_get_rec_crgg(graph *g, int vertices, double width, double r, double *x, double *y, gsl_rng *rng);

/** Return a complete graph (all vertices linked to each other). */
void graph_get_complete(graph *g, int vertices);

/** Return a circle */
void graph_get_circle(graph *g, int vertices);

/** Return a star. */
void graph_get_star(graph *g, int vertices);

#ifdef __cplusplus
}
#endif

#endif

