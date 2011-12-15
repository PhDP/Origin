#ifndef GRAPH_H_
#define GRAPH_H_

#include "common.h"
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

// For C++ compilers:
#ifdef __cplusplus
extern "C" {
#endif

/** A graph represented by an adjacency list (made of dynamic arrays). */
typedef struct 
{
    /** Number of vertices. */
    int num_v; 

    /** Number of edges per vertex. */
    int *num_e;

    /** Space allocated to each vertex. */
    int *capacity;

    /** Adjacency list. */
    int **adj_list;

    /** Weights. */
    double **w_list;
}
graph;

/** Initialize a graph with a fixed number of vertices. */
void graph_init(graph *g, int vertices);

/** Number of edges in the entire graph. */
int graph_edges(const graph *g);

/** Number of proper edges in the entire graph. */
int graph_proper_edges(const graph *g);

/** Number of loops in the entire graph. */
int graph_loops(const graph *g);

/** Number of outgoing edges for vertex \f$v\f$. \f$O(1)\f$.*/
int graph_outdegree(const graph *g, int u);

/** Number of ingoing edges for vertex \f$v\f$. \f$O(|V||E|)\f$.*/
int graph_indegree(const graph *g, int u);

/** Return true if the graph is balanced (i.e.: for each vertex \f$v\f$, indegree(v) == outdegree(v)). \f$O(|V||E|)\f$. */
int graph_is_balanced(const graph *g);

/** Add an edge between vertices 'u' and 'v' with weight. O(1), worst-case O(|N|). */
void graph_add_edge(graph *g, int u, int v, double weight);

/** Add an edge between vertices 'u' and 'v' and vice-versa. */
void graph_add_sym_edges(graph *g, int u, int v, double weight);

/** Remove the edge between vertices 'u' and 'v'. */
int graph_rmv_edge(graph *g, int u, int v);

/** Remove the edges between 'u' and 'v' and vice-versa. Return false if only 1 or 0 edges were removed. */
int graph_rmv_sym_edges(graph *g, int u, int v);

/** Return true if the graph has an edge between 'u' and 'v'. O(|E|). */
int graph_has_edge(graph *g, int u, int v);

/** Return true if the graph is strongly connected. */
int graph_strongly_connected(const graph *g);

/** Print the graph in GraphML format. */
void graph_graphml(const graph *g, FILE *out, unsigned int id);

/** Print the adjacency list. */
void graph_print(const graph *g, FILE *out);

/** Free the memory of the struct. */
void graph_free(graph *g);

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


///////////////////////////////////////////////////////////////
// 'Private' functions. You shouldn't need those.

/** Recursive function used to test connectivity. */
void graph_test_cc(const graph *g, int *group, int u);

/** Increse the storage of the lists for vertex 'u'. O(|E|). */
void graph_grow_lists(graph *g, int u);

#ifdef __cplusplus
}
#endif

#endif
