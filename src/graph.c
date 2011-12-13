#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
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

    int i = 0;
    for (; i < vertices; ++i) 
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
    int v = 0;
    for (; v < num_v; ++v) 
    {
        sum += g->num_e[v];
    }
    return sum;
}

ORIGIN_INLINE int graph_proper_edges(const graph *g)
{
    const int num_v = g->num_v;
    int sum = 0;
    int v = 0;
    for (; v < num_v; ++v) 
    {
        int e = 0;
        for (; e < g->num_e[v]; ++e)
        {
            if (g->adj_list[v][e] != v)
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
    int v = 0;
    for (; v < num_v; ++v) 
    {
        int e = 0;
        for (; e < g->num_e[v]; ++e)
        {
            if (g->adj_list[v][e] == v)
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
    int v = 0;
    for (; v < num_v; ++v) 
    {
        int e = 0;
        for (; e < g->num_e[v]; ++e)
        {
            if (g->adj_list[v][e] == u)
            {
                ++sum;
            }
        }
    }
    return sum;
}

ORIGIN_INLINE int graph_is_balanced(const graph *g)
{
    const int num_v = g->num_v;
    int u = 0;
    for (; u < num_v; ++u)
    {
        if (graph_indegree(g, u) != graph_outdegree(g, u))
        {
            return FALSE;
        }
    }
    return TRUE;
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

int graph_rmv_edge(graph *g, int u, int v)
{
    const int num_e = g->num_e[u];
    int e = 0;
    for (; e < num_e; ++e) 
    {
        if (g->adj_list[u][e] == v) 
        {
            g->num_e[u]--;
            int f = e;
            for (; f < num_e - 1; ++f) 
            {
                g->adj_list[u][f] = g->adj_list[u][f+1];
                g->w_list[u][f] = g->w_list[u][f+1];
            }
            return TRUE;
        }
    }
    return FALSE;
}

int graph_rmv_sym_edges(graph *g, int u, int v)
{
    return (graph_rmv_edge(g, u, v) && graph_rmv_edge(g, v, u));
}

int graph_has_edge(graph *g, int u, int v)
{
    const int num_e = g->num_e[u];
    int e = 0;
    for (; e < num_e; ++e) 
    {
        if (g->adj_list[u][e] == v) 
        {
            return TRUE;
        }
    }
    return FALSE;
}

int graph_strongly_connected(const graph *g)
{
    const int num_v = g->num_v;
    int *group = (int*)malloc(num_v * sizeof(int));

    int u = 0;
    for (; u < num_v; ++u) 
    {
        int v = 0;
        for (; v < num_v; ++v) 
        {
            group[v] = FALSE;
        }

        group[u] = TRUE;
        graph_test_cc(g, group, u); // Call recursive function

        for (v = 0; v < num_v; ++v) 
        {
            if (group[v] == FALSE) 
            {
                free(group);
                return FALSE;
            }
        }
    }
    free(group);
    return TRUE;
}

double **graph_get_gdm(const graph *g)
{
    const double max = DBL_MAX;
    const int num_v = g->num_v;
    double** gdm = (double**)malloc(num_v * sizeof(double*));
    int i = 0;
    for (; i < num_v; ++i)
    {
        gdm[i] = (double*)malloc(num_v * sizeof(double));
    }
    for (i = 0; i < num_v; ++i)
    {
        int j = 0;
        for (; j < num_v; ++j)
        {
            gdm[i][j] = max;
        }
    }
    int* visited = (int*)malloc(num_v * sizeof(int));

    int current; // The vertex
    int u = 0;
    for (; u < num_v; ++u)
    {
        int v = 0;
        for (; v < num_v; ++v)
        {
            visited[v] = FALSE;
        }

        gdm[u][u] = 0; // By convention
        current = u;
        int has_next = TRUE;

        while (has_next)
        {
            const int edges = g->num_e[current];
            int e = 0;
            for (; e < edges; ++e)
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
            visited[current] = TRUE;

            has_next = FALSE;
            double tmp = max;
            for (v = 0; v < num_v; ++v)
            {
                if (visited[v] == FALSE && gdm[u][v] < tmp)
                {
                    current = v;
                    tmp = gdm[u][v];
                    has_next = TRUE;
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

    int i = 0;
    for (; i < num_v; ++i)
    {
        double sum = 0.0;
        int j = 0;
        for (; j < num_v; ++j)
        {
            sum += gdm[i][j];
        }
        cls_centrality[i] = (num_v - 1) / sum;
    }
    // Free the memory of the geodesic distance matrix:
    for (i = 0; i < num_v; ++i)
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

    int i = 0;
    for (; i < num_v; ++i)
    {
        double sum = 0.0;
        int j = 0;
        for (; j < num_v; ++j)
        {
            if (i != j)
            {
                sum += 1 / gdm[i][j];
            }
        }
        har_cls_centrality[i] = sum / (num_v - 1);
    }
    // Free the memory of the geodesic distance matrix:
    for (i = 0; i < num_v; ++i)
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

void graph_graphml(const graph *g, FILE *out, unsigned int id)
{
    const int num_v = g->num_v;
    fprintf(out, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(out, "<graphml xmlns=\"http://graphml.graphdrawing.org/xmlns\"");
    fprintf(out, " xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"");
    fprintf(out, " xsi:schemaLocation=\"http://graphml.graphdrawing.org/xmlns http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd\">\n");

    fprintf(out, "  <graph id=\"%u\" edgedefault=\"directed\">\n", id);
    int i, e;
    for (i = 0; i < num_v; ++i)
    {
        fprintf(out, "    <node id=\"v%d\"/>\n", i);
    }
    for (i = 0; i < num_v; ++i)
    {
        for (e = 0; e < g->num_e[i]; ++e) 
        {
            fprintf(out, "    <edge source=\"v%d\" target=\"v%d\"/>\n", i, g->adj_list[i][e]);
        }
    }
    fprintf(out, "  </graph>\n");
    fprintf(out, "</graphml>\n");
}

void graph_print(const graph *g, FILE *out)
{
    int i = 0;
    for (; i < g->num_v; ++i) 
    {
        fprintf(out, "%5d -> ", i);
        int e = 0;
        for (; e < g->num_e[i]; ++e) 
        {
            fprintf(out, "%d ", g->adj_list[i][e]);
        }
        fprintf(out, "\n");
    }
}

void graph_print_w(const graph *g, FILE *out)
{
    const int num_v = g->num_v;
    int i = 0;
    for (; i < num_v; ++i) 
    {
        fprintf(out, "%5d -> ", i);
        int e = 0;
        for (; e < g->num_e[i]; ++e) 
        {
            fprintf(out, "%d(%8.2f) ", g->adj_list[i][e], g->w_list[i][e]);
        }
        fprintf(out, "\n");
    }
}

void graph_print_mat(const graph *g, FILE *out) 
{
    const int num_v = g->num_v;
    int row[num_v];
    int i = 0;
    for (; i < num_v; ++i) 
    {
        row[i] = 0;
    }

    for (i = 0; i < num_v; ++i) 
    {
        const int num_e = g->num_e[i];
        // Set the edges to 1
        int e = 0;
        for (; e < num_e; ++e) 
        {
            row[g->adj_list[i][e]] = 1;
        }
        // Print the row
        int j = 0;
        for (; j < num_v; ++j) 
        {
            fprintf(out, "%d ", row[j]);
        }
        // Set all edges back to 0
        for (e = 0; e < num_e; ++e) 
        {
            row[g->adj_list[i][e]] = 0;
        }
        fprintf(out, "\n");
    }
}

void graph_free(graph *g)
{
    const int num_v = g->num_v;
    int i = 0;
    for (; i < num_v; ++i) 
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

void graph_test_cc(const graph *g, int *group, int u)
{
    const int num_e = g->num_e[u];
    int e = 0;
    for (; e < num_e; ++e) 
    {
        const int head = g->adj_list[u][e];
        if (head != u && group[head] == FALSE)
        {
            group[head] = TRUE;
            graph_test_cc(g, group, head);
        }
    }
}

void graph_grow_lists(graph *g, int u)
{
    g->capacity[u] <<= 1;
    g->adj_list[u] = (int*)realloc(g->adj_list[u], g->capacity[u] * sizeof(int));
    g->w_list[u] = (double*)realloc(g->w_list[u], g->capacity[u] * sizeof(double));
}
