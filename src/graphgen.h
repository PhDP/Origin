#ifndef GRAPHGENERATORS_H_
#define GRAPHGENERATORS_H_

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include "graph.h"

// For C++ compilers:
#ifdef __cplusplus
extern "C" {
#endif

/** 
 * Get a random geometric graph in [0,1]^2 with radius 'r'.
 * 
 * 'x' and 'y' must be initialized and the correct amount of space must 
 * be allocated. The weight of the realized edges is 'r - d', where 'd' 
 * is the geometric distance between the two vertices (in short the 
 * weight is always between 0 and 1.0).
 */
void graph_get_rgg(graph *g, int vertices, double r, double *x, double *y, gsl_rng *rng);

/** 
 * Get a connected random geometric graph in [0,1]^2 with radius 'r'.
 * 
 * 'x' and 'y' must be initialized and the correct amount of space must 
 * be allocated. The weight of the realized edges is 'r - d', where 'd' 
 * is the geometric distance between the two vertices (in short the 
 * weight is always between 0 and 1.0).
 */
void graph_get_crgg(graph *g, int vertices, double r, double *x, double *y, gsl_rng *rng);

/**
 * Get a random geometric graph in a rectangle with an area of 1 and 
 * radius 'r'.
 * 
 * 'x' and 'y' must be initialized and the correct amount of space must 
 * be allocated. The weight of the realized edges is 'r - d', where 'd' 
 * is the geometric distance between the two vertices (in short the 
 * weight is always between 0 and 1.0).
 */
void graph_get_rec_rgg(graph *g, int vertices, double width, double r, double *x, double *y, gsl_rng *rng);

/**
 * Get a connected random geometric graph in a rectangle with an area of
 * 1 and radius 'r'.
 * 
 * 'x' and 'y' must be initialized and the correct amount of space must 
 * be allocated. The weight of the realized edges is 'r - d', where 'd' 
 * is the geometric distance between the two vertices (in short the 
 * weight is always between 0 and 1.0).
 */
void graph_get_rec_crgg(graph *g, int vertices, double width, double r, double *x, double *y, gsl_rng *rng);

/**
 * Return a complete graph (all vertices linked to each other). Realized
 * edges have a default weight of 1.0.
 */
void graph_get_complete(graph *g, int vertices);

/**
 * Return a circle. Realized edges have a default weight of 1.0.
 */
void graph_get_circle(graph *g, int vertices);

/**
 * Return a star. Realized edges have a default weight of 1.0.
 */
void graph_get_star(graph *g, int vertices);

#ifdef __cplusplus
}
#endif

#endif

