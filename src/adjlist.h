#ifndef ADJLIST_H_
#define ADJLIST_H_

#include <stdbool.h>
#include "common.h"

// For C++ compilers:
#ifdef __cplusplus
extern "C" {
#endif

/** A adjlist represented by an adjacency list (made of dynamic arrays). */
typedef struct edge_
{
    struct edge_ *next; /**< Pointer to the next edge in the list. */
    
    int head; /**< Head of the edge (the ID of the vertex pointed). */
    
    double w; /**< Weight. */
} edge;

/** A adjlist represented by an adjacency list (made of dynamic arrays). */
typedef struct 
{
    int num_v; /**< Number of vertices. */  
    
    int *num_e;  /**< Number of edges per vertex. */
    
    edge **list; /**< The adjacency list. */
} 
adjlist;

/** Initialize a adjlist with a fixed number of vertices. */
void adjlist_init(adjlist *a, int vertices);

/** Number of edges in the entire adjlist. */
int adjlist_edges(const adjlist *a);

/** Allocate memory for an edge and return a pointer to it. */
edge *create_edge(int head, double weight, edge *next);

/** Number of proper edges in the entire adjlist. */
int adjlist_proper_edges(const adjlist *a);

/** Number of loops in the entire adjlist. */
int adjlist_loops(const adjlist *a);

/** Number of outgoing edges for vertex \f$v\f$. \f$O(1)\f$.*/
int adjlist_outdegree(const adjlist *a, int u);

/** Number of ingoing edges for vertex \f$v\f$. \f$O(|V||E|)\f$.*/
int adjlist_indegree(const adjlist *a, int u);

/** Return true if the adjlist is balanced (i.e.: for each vertex \f$v\f$, indegree(v) == outdegree(v)). \f$O(|V||E|)\f$. */
bool adjlist_is_balanced(const adjlist *a);

/** Add an edge between vertices 'u' and 'v' with weight. O(1), worst-case O(|N|). */
void adjlist_add_edge(adjlist *a, int u, int v, double weight);

/** Add an edge between vertices 'u' and 'v' and vice-versa. */
void adjlist_add_sym_edges(adjlist *a, int u, int v, double weight);

/** Remove the edge between vertices 'u' and 'v'. */
bool adjlist_rmv_edge(adjlist *a, int u, int v);

/** Remove the edges between 'u' and 'v' and vice-versa. Return false if only 1 or 0 edges were removed. */
bool adjlist_rmv_sym_edges(adjlist *a, int u, int v);

/** Return true if the adjlist has an edge between 'u' and 'v'. O(|E|). */
bool adjlist_has_edge(adjlist *a, int u, int v);

/** Return true if the adjlist is strongly connected. */
bool adjlist_strongly_connected(const adjlist *a);

/** Get the geodesic distances between all pairs of vertices using Johnson's algorithm. O(V^2 log V + VE). */
double **adjlist_get_gdm(const adjlist *a);

/** Return an array with the closeness centrality for all vertices. */
double *adjlist_cls(const adjlist *a);

/** Print the graph in graphml format. */
void adjlist_graphml(const adjlist *a, FILE *out, const char *id);

/** Print the adjacency list. Use NULL for the file pointer to print to the console. */
void adjlist_print(const adjlist *a, FILE *out);

/** Print the adjacency list & the weights. Use NULL for the file pointer to print to the console. */
void adjlist_print_w(const adjlist *a, FILE *out);

/** Print in matrix form. Use NULL for the file pointer to print to the console. */
void adjlist_print_mat(const adjlist *a, FILE *out);

/** Print the weights in matrix form. Use NULL for the file pointer to print to the console. */
void adjlist_print_w_mat(const adjlist *a, FILE *out);

/** Free the memory of the struct and all subsequent edges. */
void edge_free(edge *e);

/** Free the memory of the struct. */
void adjlist_free(adjlist *a);

///////////////////////////////////////////////////////////////
// 'Private' functions. You shouldn't need those.

/** Recursive function used to test connectivity. */
void adjlist_test_cc(const adjlist *a, bool *group, int u);

#ifdef __cplusplus
}
#endif

#endif
