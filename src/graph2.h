#ifndef GRAPH2_H_
#define GRAPH2_H_

#include <stdbool.h>
#include "hon.h"

// For C++ compilers:
#ifdef __cplusplus
extern "C" {
#endif

/** A graph represented by an adjacency list (made of dynamic arrays). */
typedef struct edge_
{
	edge_ *next; /**< Pointer to the next edge in the list. */
	
	int head; /**< Head of the edge (the ID of the vertex pointed). */
	
	double w; /**< Weight. */
} edge;

/** A graph represented by an adjacency list (made of dynamic arrays). */
typedef struct 
{
	int num_v; /**< Number of vertices. */  
	
	int *num_e;  /**< Number of edges per vertex. */
	
	edge **adjlist; /**< The adjacency list. */
} 
graph2;

/** Initialize a graph with a fixed number of vertices. */
void graph2_init(graph *g, int vertices);

/** Number of edges in the entire graph. */
int graph2_edges(const graph *g);

/** Number of proper edges in the entire graph. */
int graph2_proper_edges(const graph *g);

/** Number of loops in the entire graph. */
int graph2_loops(const graph *g);

/** Number of outgoing edges for vertex \f$v\f$. \f$O(1)\f$.*/
int graph2_outdegree(const graph *g, int u);

/** Number of ingoing edges for vertex \f$v\f$. \f$O(|V||E|)\f$.*/
int graph2_indegree(const graph *g, int u);

/** Return true if the graph is balanced (i.e.: for each vertex \f$v\f$, indegree(v) == outdegree(v)). \f$O(|V||E|)\f$. */
bool graph2_is_balanced(const graph *g);

/** Add an edge between vertices 'u' and 'v' with weight. O(1), worst-case O(|N|). */
void graph2_add_edge(graph *g, int u, int v, double weight);

/** Add an edge between vertices 'u' and 'v' and vice-versa. */
void graph2_add_sym_edges(graph *g, int u, int v, double weight);

/** Remove the edge between vertices 'u' and 'v'. */
bool graph2_rmv_edge(graph *g, int u, int v);

/** Remove the edges between 'u' and 'v' and vice-versa. Return false if only 1 or 0 edges were removed. */
bool graph2_rmv_sym_edges(graph *g, int u, int v);

/** Return true if the graph has an edge between 'u' and 'v'. O(|E|). */
bool graph2_has_edge(graph *g, int u, int v);

/** Return true if the graph is strongly connected. */
bool graph2_strongly_connected(const graph *g);

/** Dijkstra's algorithm for shortest path. */
void graph2_dijkstra(const graph *g, int v);

/** Bellman-Ford's algorithm for shortest path. */
void graph2_bellman_ford(const graph *g, int v);

/** Get the geodesic distances between all pairs of vertices using Johnson's algorithm. O(V^2 log V + VE). */
double **graph2_get_gdm(const graph *g);

/** Return an array with the closeness centrality for all vertices. */
double *graph2_cls_centrality(const graph *g);

/** Return a scaled array with the closeness centrality for all vertices. */
double *graph2_cls_centrality_scaled(const graph *g);

/** Print the adjacency list. Use NULL for the file pointer to print to the console. */
void graph2_print(const graph *g, FILE *out);

/** Print the adjacency list & the weights. Use NULL for the file pointer to print to the console. */
void graph2_print_w(const graph *g, FILE *out);

/** Print in matrix form. Use NULL for the file pointer to print to the console. */
void graph2_print_mat(const graph *g, FILE *out);

/** Print the weights in matrix form. Use NULL for the file pointer to print to the console. */
void graph2_print_w_mat(const graph *g, FILE *out);

/** Free the memory of the struct. */
void graph2_free(graph *g);

///////////////////////////////////////////////////////////////
// 'Private' functions. You shouldn't need those.

/** Recursive function used to test connectivity. */
void graph2_test_cc(const graph *g, bool *group, int u);
#ifdef __cplusplus
}
#endif

#endif
