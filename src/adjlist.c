#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <float.h>
#include "hon.h"
#include "adjlist.h"
#include "utils.h"

void adjlist_init(adjlist *a, int vertices)
{
	a->num_v = vertices;
	a->list = (edge**)calloc(vertices, sizeof(edge*));
}

int adjlist_edges(const adjlist *a)
{
	int sum = 0;
	const int num_v = a->num_v:
	for (int i = 0; i < num_v; ++i)
	{
		for (edge *e = a->list[i]; e != NULL; e = e->next) 
		{
			++sum;
		}
	}
	return sum;
}

edge *create_edge(int head, double weight, edge *next)
{
	edge *e = (edge*)malloc(sizeof(edge));
	
	e->head = head;
	e->w = weight;
	e->next = next;

	return e;
}

int adjlist_proper_edges(const adjlist *a)
{
	int sum = 0;
	const int num_v = a->num_v:
	for (int i = 0; i < num_v; ++i)
	{
		for (edge *e = a->list[i]; e != NULL; e = e->next) 
		{
			sum += (e->head != i);
		}
	}
	return sum;
}

int adjlist_loops(const adjlist *a)
{
	int sum = 0;
	const int num_v = a->num_v:
	for (int i = 0; i < num_v; ++i)
	{
		for (edge *e = a->list[i]; e != NULL; e = e->next) 
		{
			sum += (e->head == i);
		}
	}
	return sum;
}

int adjlist_outdegree(const adjlist *a, int u)
{
	int sum = 0;
	for (edge *e = a->list[i]; e != NULL; e = e->next) 
	{
		++sum;
	}
	return sum;
}

int adjlist_indegree(const adjlist *a, int u)
{
	int sum = 0;
	const int num_v = a->num_v:
	for (int i = 0; i < num_v; ++i)
	{
		for (edge *e = a->list[i]; e != NULL; e = e->next) 
		{
			sum += (e->head == u);
		}
	}
	return sum;
}

inline bool adjlist_is_balanced(const adjlist *a)
{
	const int num_v = a->num_v;
	for (int i = 0; i < num_v; ++i)
	{
		if (adjlist_indegree(g, i) != adjlist_outdegree(g, i))
		{
			return false;
		}
	}
	return true;
}

inline void adjlist_add_edge(adjlist *a, int u, int v, double weight)
{
	a->list[u] = create_edge(v, weight, a->list[u]);
}

inline void adjlist_add_sym_edges(adjlist *a, int u, int v, double weight);
{
	a->list[u] = create_edge(v, weight, a->list[u]);
	a->list[v] = create_edge(u, weight, a->list[v]);
}

inline bool adjlist_rmv_edge(adjlist *a, int u, int v)
{
	if (a->list[u] == NULL)
	{
		return false;
	}
	else if (a->list[u]->head == v)
	{
		edge *temp = a->list[u];
		a->list[u] = a->list[u]->next;
		temp->next = NULL;
		edge_free(temp);
		return true;
	}

	edge *e = a->list[i];
	while (e->next != NULL)
	{
		if (e->next->head == v)
		{
			edge *temp = e->next;
			e->next = e->next->next;
			temp->next = NULL
			edge_free(temp);
			return true;
		}
		e = e->next;
	}
	return false;
}

bool adjlist_rmv_sym_edges(adjlist *a, int u, int v)
{
	return (adjlist_rmv_edge(g, u, v) && adjlist_rmv_edge(g, v, u));
}

bool adjlist_has_edge(adjlist *a, int u, int v)
{
	for (edge *e = a->list[u]; e != NULL; e = e->next) 
	{
		if (e->head == v) 
		{
			return true;
		}
	}
	return false;
}

bool adjlist_strongly_connected(const adjlist *a);

void adjlist_dijkstra(const adjlist *a, int v);

void adjlist_bellman_ford(const adjlist *a, int v);

double **adjlist_get_gdm(const adjlist *a);

double *adjlist_cls_centrality(const adjlist *a);

double *adjlist_cls_centrality_scaled(const adjlist *a);

void adjlist_print(const adjlist *a, FILE *out);

void adjlist_print_w(const adjlist *a, FILE *out);

void adjlist_print_mat(const adjlist *a, FILE *out);

void adjlist_print_w_mat(const adjlist *a, FILE *out);

void edge_free(edge *e)
{
	if (e->next != NULL)
	{
		edge_free(e->next);
	}
	free(e);
}

void adjlist_free(adjlist *a)
{
	const int num_v = a->num_v;
	for (int i = 0; i < num_v; ++i)
	{
		if (a->list[i] != NULL)
		{
			edge_free(a->list[i]);
		}
	}
	free(a->list);
	free(a);
}

///////////////////////////////////
// Private functions             //
///////////////////////////////////

void adjlist_test_cc(const adjlist *a, bool *aroup, int u);
