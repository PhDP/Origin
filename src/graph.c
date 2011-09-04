#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <float.h>
#include "common.h"
#include "graph.h"
#include "utils.h"

void graph_init(graph *g, int vertices)
{
	g->num_v = vertices;
	g->num_e = (int*)malloc(vertices * sizeof(int));
	g->capacity = (int*)malloc(vertices * sizeof(int));
	g->adj_list = (int**)malloc(vertices * sizeof(int*));
	g->w_list = (double**)malloc(vertices * sizeof(double*));

	for (int i = 0; i < vertices; ++i) 
	{
		g->num_e[i] = 0;
		g->capacity[i] = GRAPH_INIT_CAPACITY;
		g->adj_list[i] = (int*)malloc(GRAPH_INIT_CAPACITY * sizeof(int));
		g->w_list[i] = (double*)malloc(GRAPH_INIT_CAPACITY * sizeof(double));
	}
}

ORIGIN_INLINE int graph_edges(const graph *g)
{
	const int num_v = g->num_v;
	int sum = 0;
	for(int v = 0; v < num_v; ++v) 
	{
		sum += g->num_e[v];
	}
	return sum;
}

ORIGIN_INLINE int graph_proper_edges(const graph *g)
{
	const int num_v = g->num_v;
	int sum = 0;
	for(int v = 0; v < num_v; ++v) 
	{
		for(int e = 0; e < g->num_e[v]; ++e)
		{
			if(g->adj_list[v][e] != v)
			{
				++sum;
			}
		}
	}
	return sum;
}

ORIGIN_INLINE int graph_loops(const graph *g)
{
	const int num_v = g->num_v;
	int sum = 0;
	for(int v = 0; v < num_v; ++v) 
	{
		for(int e = 0; e < g->num_e[v]; ++e)
		{
			if(g->adj_list[v][e] == v)
			{
				++sum;
			}
		}
	}
	return sum;
}

ORIGIN_INLINE int graph_outdegree(const graph *g, int u)
{
	return g->num_e[u];
}

ORIGIN_INLINE int graph_indegree(const graph *g, int u)
{
	const int num_v = g->num_v;
	int sum = 0;
	for(int v = 0; v < num_v; ++v) 
	{
		for(int e = 0; e < g->num_e[v]; ++e)
		{
			if(g->adj_list[v][e] == u)
			{
				++sum;
			}
		}
	}
	return sum;
}

ORIGIN_INLINE bool graph_is_balanced(const graph *g)
{
	const int num_v = g->num_v;
	for (int u = 0; u < num_v; ++u)
	{
		if(graph_indegree(g, u) != graph_outdegree(g, u))
		{
			return false;
		}
	}
	return true;
}

ORIGIN_INLINE void graph_add_edge(graph *g, int u, int v, double weight)
{
	if (g->num_e[u] == g->capacity[u]) 
	{
		graph_grow_lists(g, u);
	}
	g->adj_list[u][g->num_e[u]] = v;
	g->w_list[u][g->num_e[u]] = weight;
	g->num_e[u]++;
}

void graph_add_sym_edges(graph *g, int u, int v, double weight) 
{
	graph_add_edge(g, u, v, weight);
	graph_add_edge(g, v, u, weight);
}

bool graph_rmv_edge(graph *g, int u, int v)
{
	const int num_e = g->num_e[u];
	for (int e = 0; e < num_e; ++e) 
	{
		if (g->adj_list[u][e] == v) 
		{
			g->num_e[u]--;
			for (int f = e; f < num_e - 1; ++f) 
			{
				g->adj_list[u][f] = g->adj_list[u][f+1];
				g->w_list[u][f] = g->w_list[u][f+1];
			}
			return true;
		}
	}
	return false;
}

bool graph_rmv_sym_edges(graph *g, int u, int v)
{
	return (graph_rmv_edge(g, u, v) && graph_rmv_edge(g, v, u));
}

bool graph_has_edge(graph *g, int u, int v)
{
	const int num_e = g->num_e[u];
	for (int e = 0; e < num_e; ++e) 
	{
		if (g->adj_list[u][e] == v) 
		{
			return true;
		}
	}
	return false;
}

bool graph_strongly_connected(const graph *g)
{
	const int num_v = g->num_v;
	bool *group = (bool*)malloc(num_v * sizeof(bool));

	for (int u = 0; u < num_v; ++u) 
	{
		for (int v = 0; v < num_v; ++v) 
		{
			group[v] = false;
		}

		group[u] = true;
		graph_test_cc(g, group, u); // Call recursive function

		for (int v = 0; v < num_v; ++v) 
		{
			if (group[v] == false) 
			{
				free(group);
				return false;
			}
		}
	}
	free(group);
	return true;
}

double **graph_get_gdm(const graph *g)
{
	const double max = DBL_MAX;
	const int num_v = g->num_v;
	double** gdm = (double**)malloc(num_v * sizeof(double*));
	for (int i = 0; i < num_v; ++i)
	{
		gdm[i] = (double*)malloc(num_v * sizeof(double));
	}
	for (int i = 0; i < num_v; ++i)
	{
		for (int j = 0; j < num_v; ++j)
		{
			gdm[i][j] = max;
		}
	}
	bool* visited = (bool*)malloc(num_v * sizeof(bool));
	
	int current; // The vertex
	for (int u = 0; u < num_v; ++u)
	{
		for (int v = 0; v < num_v; ++v)
		{
			visited[v] = false;
		}

		gdm[u][u] = 0; // By convention
		current = u;
		bool has_next = true;

		while (has_next)
		{
			const int edges = g->num_e[current];
			for (int e = 0; e < edges; ++e)
			{
				if (g->adj_list[current][e] != current)
				{
					const double w = gdm[u][current] + g->w_list[current][e];
					if (gdm[u][g->adj_list[current][e]] > w)
					{
						gdm[u][g->adj_list[current][e]] = w;
					}
				}
			}
			visited[current] = true;

			has_next = false;
			double tmp = max;
			for (int v = 0; v < num_v; v++)
			{
				if (visited[v] == false && gdm[u][v] < tmp)
				{
					current = v;
					tmp = gdm[u][v];
					has_next = true;
				}
			}
		}
	}
	free(visited);
	return gdm;
}

double *graph_cls_centrality(const graph *g)
{
	const int num_v = g->num_v;
	double **gdm = graph_get_gdm(g);
	double *cls_centrality = (double*)malloc(num_v * sizeof(double));
	
	for (int i = 0; i < num_v; ++i)
	{
		double sum = 0.0;
		for (int j = 0; j < num_v; ++j)
		{
			sum += gdm[i][j];
		}
		cls_centrality[i] = (num_v - 1) / sum;
	}
	// Free the memory of the geodesic distance matrix:
	for (int i = 0; i < num_v; ++i)
	{
		free(gdm[i]);
	}
	free(gdm);
	
	return cls_centrality;
}

double *graph_cls_centrality_scaled(const graph *g)
{
	double *cls_centrality_scaled = graph_cls_centrality(g);
	scale_0_1(cls_centrality_scaled, g->num_v);
	return cls_centrality_scaled;
}

double *graph_har_cls_centrality(const graph *g)
{
	const int num_v = g->num_v;
	double **gdm = graph_get_gdm(g);
	double *har_cls_centrality = (double*)malloc(num_v * sizeof(double));
	
	for (int i = 0; i < num_v; ++i)
	{
		double sum = 0.0;
		for (int j = 0; j < num_v; ++j)
		{
			if (i != j)
			{
				sum += 1 / gdm[i][j];
			}
		}
		har_cls_centrality[i] = sum / (num_v - 1);
	}
	
	// Free the memory of the geodesic distance matrix:
	for (int i = 0; i < num_v; ++i)
	{
		free(gdm[i]);
	}
	free(gdm);
	
	return har_cls_centrality;
}

double *graph_har_cls_centrality_scaled(const graph *g)
{
	double *har_cls_centrality_scaled = graph_har_cls_centrality(g);
	scale_0_1(har_cls_centrality_scaled, g->num_v);
	return har_cls_centrality_scaled;
}

void graph_print(const graph *g, FILE *out)
{
	if (out == NULL) 
	{
		for (int i = 0; i < g->num_v; ++i) 
		{
			printf("%5d -> ", i);
			for (int e = 0; e < g->num_e[i]; ++e) 
			{
				printf("%d ", g->adj_list[i][e]);
			}
			printf("\n");
		}
	} 
	else 
	{
		for (int i = 0; i < g->num_v; ++i) 
		{
			printf("%5d -> ", i);
			for (int e = 0; e < g->num_e[i]; ++e) 
			{
				printf("%d ", g->adj_list[i][e]);
			}
			printf("\n");
		}
	}
}

void graph_print_w(const graph *g, FILE *out)
{
	const int num_v = g->num_v;
	if (out == NULL) 
	{
		for (int i = 0; i < num_v; ++i) 
		{
			printf("%5d -> ", i);
			for (int e = 0; e < g->num_e[i]; ++e) 
			{
				printf("%d(%8.2f) ", g->adj_list[i][e], g->w_list[i][e]);
			}
			printf("\n");
		}
	} 
	else 
	{
		for (int i = 0; i < num_v; ++i) 
		{
			fprintf(out, "%5d -> ", i);
			for (int e = 0; e < g->num_e[i]; ++e) 
			{
				fprintf(out, "%d(%8.2f) ", g->adj_list[i][e], g->w_list[i][e]);
			}
			fprintf(out, "\n");
		}
	}
}

void graph_print_mat(const graph *g, FILE *out) 
{
	const int num_v = g->num_v;
	int row[num_v];
	for (int i = 0; i < num_v; ++i) 
	{
		row[i] = 0;
	}

	for (int i = 0; i < num_v; ++i) 
	{
		const int num_e = g->num_e[i];
		// Set the edges to 1
		for (int e = 0; e < num_e; ++e) 
		{
			row[g->adj_list[i][e]] = 1;
		}
		// Print the row
		if (out == NULL) 
		{
			for (int j = 0; j < num_v; ++j) 
			{
				printf("%d ", row[j]);
			}
		} 
		else 
		{
			for (int j = 0; j < num_v; ++j) 
			{
				fprintf(out, "%d ", row[j]);
			}
		}
		// Set all edges back to 0
		for (int e = 0; e < num_e; ++e) 
		{
			row[g->adj_list[i][e]] = 0;
		}
		if (out == NULL) 
		{
			printf("\n");
		}
		else
		{
			fprintf(out, "\n");
		}
	}
}

void graph_print_w_mat(const graph *g, FILE *out)
{
	const int num_v = g->num_v;
	double row[num_v];
	for (int i = 0; i < num_v; ++i) 
	{
		row[i] = 0.0;
	}
	for (int i = 0; i < num_v; ++i) 
	{
		const int num_e = g->num_e[i];
		// Set the edges to 1
		for (int e = 0; e < num_e; ++e) 
		{
			row[g->adj_list[i][e]] = g->w_list[i][e];
		}
		// Print the row
		if (out == NULL) 
		{
			for (int j = 0; j < num_v; ++j) 
			{
				printf("%.4f ", row[j]);
			}
		} 
		else 
		{
			for (int j = 0; j < num_v; ++j) 
			{
				fprintf(out, "%.4f ", row[j]);
			}
		}
		// Set all edges back to 0
		for (int e = 0; e < num_e; ++e) 
		{
			row[g->adj_list[i][e]] = 0.0;
		}
		if (out == NULL) 
		{
			printf("\n");
		} 
		else 
		{
			fprintf(out, "\n");
		}
	}
}

void graph_free(graph *g)
{
	const int num_v = g->num_v;
	for (int i = 0; i < num_v; ++i) 
	{
		free(g->adj_list[i]);
		free(g->w_list[i]);
	}
	free(g->adj_list);
	g->adj_list = NULL;
	free(g->w_list);
	g->w_list = NULL;
	free(g->num_e);
	g->num_e = NULL;
	free(g->capacity);
	g->capacity = NULL;
}

///////////////////////////////////////////////////////////////
// 'Private' functions

void graph_test_cc(const graph *g, bool *group, int u)
{
	const int num_e = g->num_e[u];
	for (int e = 0; e < num_e; ++e) 
	{
		const int head = g->adj_list[u][e];
		if (head != u && group[head] == false)
		{
			group[head] = true;
			graph_test_cc(g, group, head);
		}
	}
}

// Grow the edge list of some vertex v.
void graph_grow_lists(graph *g, int u)
{
	g->capacity[u] <<= 1;

	int *tmp_adj = (int*)malloc(g->capacity[u] * sizeof(int));
	double *tmp_w = (double*)malloc(g->capacity[u] * sizeof(double));

	const int num_e = g->num_e[u];
	for (int e = 0; e < num_e; ++e) 
	{
		tmp_adj[e] = g->adj_list[u][e];
		tmp_w[e] = g->w_list[u][e];
	}
	int *swap_adj = g->adj_list[u];
	double *swap_w = g->w_list[u];

	g->adj_list[u] = tmp_adj;
	g->w_list[u] = tmp_w;

	free(swap_adj);
	free(swap_w);
}
