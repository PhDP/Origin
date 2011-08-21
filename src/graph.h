#ifndef GRAPH_H_
#define GRAPH_H_

#include <stdbool.h>
#include "seshat.h"

// For C++ compilers:
#ifdef __cplusplus
extern "C" {
#endif

/** A graph represented by an adjacency list. */
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

	bool weighted;
} 
graph;

/** Initialize a graph with a fixed number of vertices. */
void graph_init(graph *g, int vertices, bool weighted);

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
bool graph_is_balanced(const graph *g);

/** Add an edge between vertices 'u' and 'v'. O(1), worst-case O(|N|). */
void graph_add_edge(graph *g, int u, int v);

/** Add an edge between vertices 'u' and 'v' with weight. O(1), worst-case O(|N|). */
void graph_add_w_edge(graph *g, int u, int v, double weight);

/** Add an edge between vertices 'u' and 'v' and vice-versa. */
void graph_add_sym_edges(graph *g, int u, int v, double weight);

/** Remove the edge between vertices 'u' and 'v'. */
bool graph_rmv_edge(graph *g, int u, int v);

/** Remove the edges between 'u' and 'v' and vice-versa. Return false if only 1 or 0 edges were removed. */
bool graph_rmv_sym_edges(graph *g, int u, int v);

/** Return true if the graph has an edge between 'u' and 'v'. O(|E|). */
bool graph_has_edge(graph *g, int u, int v);

/** Return true if the graph is strongly connected. */
bool graph_strongly_connected(const graph *g);

/** Dijkstra's algorithm for shortest path. */
void graph_dijkstra(const graph *g, int v);

/** Bellman-Ford's algorithm for shortest path. */
void graph_bellman_ford(const graph *g, int v);

/** Get the geodesic distances between all pairs of vertices using Johnson's algorithm. O(V^2 log V + VE). */
double **graph_get_gdm(const graph *g);

/** Return an array with the closeness centrality for all vertices. */
double *graph_cls_centrality(const graph *g);

/** Return a scaled array with the closeness centrality for all vertices. */
double *graph_cls_centrality_scaled(const graph *g);

/** Print the adjacency list. Use NULL for the file pointer to print to the console. */
void graph_print(const graph *g, FILE *out);

/** Print the adjacency list & the weights. Use NULL for the file pointer to print to the console. */
void graph_print_w(const graph *g, FILE *out);

/** Print in matrix form. Use NULL for the file pointer to print to the console. */
void graph_print_mat(const graph *g, FILE *out);

/** Print the weights in matrix form. Use NULL for the file pointer to print to the console. */
void graph_print_w_mat(const graph *g, FILE *out);

/** Free the memory of the struct. */
void graph_free(graph *g);

///////////////////////////////////////////////////////////////
// 'Private' functions. You shouldn't need those.

/** Recursive function used to test connectivity. */
void graph_test_cc(const graph *g, bool *group, int u);

/** Increse the storage of the lists for vertex 'u'. O(|E|). */
void graph_grow_lists(graph *g, int u);

#ifdef __cplusplus
}
#endif

#endif
