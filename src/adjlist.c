#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <float.h>
#include "common.h"
#include "adjlist.h"
#include "utils.h"

void adjlist_init(adjlist *a, int vertices)
{
	a->num_v = vertices;
	a->list = (edge**)calloc(vertices, sizeof(edge*));
}

ORIGIN_INLINE int adjlist_edges(const adjlist *a)
{
	int sum = 0;
	const int num_v = a->num_v;
	for (int i = 0; i < num_v; ++i)
	{
		for (edge *e = a->list[i]; e != NULL; e = e->next) 
		{
			++sum;
		}
	}
	return sum;
}

ORIGIN_INLINE edge *create_edge(int head, double weight, edge *next)
{
	edge *e = (edge*)malloc(sizeof(edge));
	
	e->head = head;
	e->w = weight;
	e->next = next;

	return e;
}

ORIGIN_INLINE int adjlist_proper_edges(const adjlist *a)
{
	int sum = 0;
	const int num_v = a->num_v;
	for (int i = 0; i < num_v; ++i)
	{
		for (edge *e = a->list[i]; e != NULL; e = e->next) 
		{
			sum += (e->head != i);
		}
	}
	return sum;
}

ORIGIN_INLINE int adjlist_loops(const adjlist *a)
{
	int sum = 0;
	const int num_v = a->num_v;
	for (int i = 0; i < num_v; ++i)
	{
		for (edge *e = a->list[i]; e != NULL; e = e->next) 
		{
			sum += (e->head == i);
		}
	}
	return sum;
}

ORIGIN_INLINE int adjlist_outdegree(const adjlist *a, int u)
{
	int sum = 0;
	for (edge *e = a->list[u]; e != NULL; e = e->next) 
	{
		++sum;
	}
	return sum;
}

ORIGIN_INLINE int adjlist_indegree(const adjlist *a, int u)
{
	int sum = 0;
	const int num_v = a->num_v;
	for (int i = 0; i < num_v; ++i)
	{
		for (edge *e = a->list[i]; e != NULL; e = e->next) 
		{
			sum += (e->head == u);
		}
	}
	return sum;
}

ORIGIN_INLINE bool adjlist_is_balanced(const adjlist *a)
{
	const int num_v = a->num_v;
	for (int i = 0; i < num_v; ++i)
	{
		if (adjlist_indegree(a, i) != adjlist_outdegree(a, i))
		{
			return false;
		}
	}
	return true;
}

ORIGIN_INLINE void adjlist_add_edge(adjlist *a, int u, int v, double weight)
{
	a->list[u] = create_edge(v, weight, a->list[u]);
}

ORIGIN_INLINE void adjlist_add_sym_edges(adjlist *a, int u, int v, double weight)
{
	a->list[u] = create_edge(v, weight, a->list[u]);
	a->list[v] = create_edge(u, weight, a->list[v]);
}

ORIGIN_INLINE bool adjlist_rmv_edge(adjlist *a, int u, int v)
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

	edge *e = a->list[u];
	while (e->next != NULL)
	{
		if (e->next->head == v)
		{
			edge *temp = e->next;
			e->next = e->next->next;
			temp->next = NULL;
			edge_free(temp);
			return true;
		}
		e = e->next;
	}
	return false;
}

ORIGIN_INLINE bool adjlist_rmv_sym_edges(adjlist *a, int u, int v)
{
	return (adjlist_rmv_edge(a, u, v) && adjlist_rmv_edge(a, v, u));
}

ORIGIN_INLINE bool adjlist_has_edge(adjlist *a, int u, int v)
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

bool adjlist_strongly_connected(const adjlist *a)
{
	const int num_v = a->num_v;
	bool *group = (bool*)malloc(num_v * sizeof(bool));

	for (int u = 0; u < num_v; ++u) 
	{
		for (int v = 0; v < num_v; ++v) 
		{
			group[v] = false;
		}

		group[u] = true;
		adjlist_test_cc(a, group, u); // Call recursive function

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

double **adjlist_get_gdm(const adjlist *a)
{
	const double max = DBL_MAX;
	const int num_v = a->num_v;
	double **gdm = (double**)malloc(num_v * sizeof(double*));
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
	bool *visited = (bool*)malloc(num_v * sizeof(bool));
	
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
			for (edge *e = a->list[u]; e != NULL; e = e->next)
			{
				const int head = e->head;
				if (head != current)
				{
					const double w = gdm[u][current] + e->w;
					if (gdm[u][head] > w)
					{
						gdm[u][head] = w;
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

double *adjlist_cls_centrality(const adjlist *a)
{
	const int num_v = a->num_v;
	double **gdm = adjlist_get_gdm(a);
	double *cls_centrality = (double*)malloc(num_v * sizeof(double));
	
	for (int i = 0; i < num_v; ++i)
	{
		double sum = 0.0;
		for (int j = 0; j < num_v; ++j)
		{
			sum += gdm[i][j];
		}
		cls_centrality[i] = sum / (num_v - 1);
	}
	
	// Free the memory of the geodesic distance matrix:
	for (int i = 0; i < num_v; ++i)
	{
		free(gdm[i]);
	}
	free(gdm);
	
	return cls_centrality;
}

double *adjlist_cls_centrality_scaled(const adjlist *a)
{
	double *cls_centrality_scaled = adjlist_cls_centrality(a);
	scale_0_1(cls_centrality_scaled, a->num_v);
	return cls_centrality_scaled;
}

void adjlist_print(const adjlist *a, FILE *out)
{
	const int num_v = a->num_v;
	if (out == NULL) 
	{
		for (int i = 0; i < num_v; ++i) 
		{
			printf("%5d -> ", i);
			for (edge *e = a->list[i]; e != NULL; e = e->next)
			{
				printf("%d ", e->head);
			}
			printf("\n");
		}
	} 
	else 
	{
		for (int i = 0; i < num_v; ++i) 
		{
			fprintf(out, "%5d -> ", i);
			for (edge *e = a->list[i]; e != NULL; e = e->next)
			{
				fprintf(out, "%d ", e->head);
			}
			fprintf(out, "\n");
		}
	}
}

void adjlist_print_w(const adjlist *a, FILE *out)
{
	const int num_v = a->num_v;
	if (out == NULL) 
	{
		for (int i = 0; i < num_v; ++i) 
		{
			printf("%5d -> ", i);
			for (edge *e = a->list[i]; e != NULL; e = e->next)
			{
				printf("%d(%.2f) ", e->head, e->w);
			}
			printf("\n");
		}
	} 
	else 
	{
		for (int i = 0; i < num_v; ++i) 
		{
			fprintf(out, "%5d -> ", i);
			for (edge *e = a->list[i]; e != NULL; e = e->next)
			{
				fprintf(out, "%d(%8.2f) ", e->head, e->w);
			}
			fprintf(out, "\n");
		}
	}
}

void adjlist_print_mat(const adjlist *a, FILE *out)
{
	const int num_v = a->num_v;
	int row[num_v];
	for (int i = 0; i < num_v; ++i) 
	{
		row[i] = 0;
	}
	for (int i = 0; i < num_v; ++i) 
	{
		for (edge *e = a->list[i]; e != NULL; e = e->next)
		{
			row[e->head] += 1;
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
		for (edge *e = a->list[i]; e != NULL; e = e->next)
		{
			row[e->head] -= 1;
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

void adjlist_print_w_mat(const adjlist *a, FILE *out)
{
	const int num_v = a->num_v;
	double row[num_v];
	for (int i = 0; i < num_v; ++i) 
	{
		row[i] = 0.0;
	}
	for (int i = 0; i < num_v; ++i) 
	{
		for (edge *e = a->list[i]; e != NULL; e = e->next)
		{
			row[e->head] = e->w;
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
		for (edge *e = a->list[i]; e != NULL; e = e->next)
		{
			row[e->head] = 0.0;
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

ORIGIN_INLINE void edge_free(edge *e)
{
	if (e->next != NULL)
	{
		edge_free(e->next);
	}
	free(e);
}

ORIGIN_INLINE void adjlist_free(adjlist *a)
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
	a->list = NULL;
}

///////////////////////////////////
// Private functions             //
///////////////////////////////////

ORIGIN_INLINE void adjlist_test_cc(const adjlist *a, bool *group, int u)
{
	for (edge *e = a->list[u]; e != NULL; e = e->next) 
	{
		const int head = e->head;
		if (head != u && group[head] == false)
		{
			group[head] = true;
			adjlist_test_cc(a, group, head);
		}
	}
}
