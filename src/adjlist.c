#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <float.h>
#include "common.h"
#include "adjlist.h"
#include "utils.h"

void adjlist_init(adjlist *a, int vertices)
{
    a->num_v = vertices;
    a->list = (edge**)calloc(vertices, sizeof(edge*));
}

O_INLINE int adjlist_edges(const adjlist *a)
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

O_INLINE edge *create_edge(int head, double weight, edge *next)
{
    edge *e = (edge*)malloc(sizeof(edge));
    
    e->head = head;
    e->w = weight;
    e->next = next;

    return e;
}

O_INLINE int adjlist_proper_edges(const adjlist *a)
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

O_INLINE int adjlist_loops(const adjlist *a)
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

O_INLINE int adjlist_outdegree(const adjlist *a, int u)
{
    int sum = 0;
    for (edge *e = a->list[u]; e != NULL; e = e->next) 
    {
        ++sum;
    }
    return sum;
}

O_INLINE int adjlist_indegree(const adjlist *a, int u)
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

O_INLINE int adjlist_is_balanced(const adjlist *a)
{
    const int num_v = a->num_v;
    for (int i = 0; i < num_v; ++i)
    {
        if (adjlist_indegree(a, i) != adjlist_outdegree(a, i))
        {
            return FALSE;
        }
    }
    return TRUE;
}

O_INLINE void adjlist_add_edge(adjlist *a, int u, int v, double weight)
{
    a->list[u] = create_edge(v, weight, a->list[u]);
}

O_INLINE void adjlist_add_sym_edges(adjlist *a, int u, int v, double weight)
{
    a->list[u] = create_edge(v, weight, a->list[u]);
    a->list[v] = create_edge(u, weight, a->list[v]);
}

O_INLINE int adjlist_rmv_edge(adjlist *a, int u, int v)
{
    if (a->list[u] == NULL)
    {
        return FALSE;
    }
    else if (a->list[u]->head == v)
    {
        edge *temp = a->list[u];
        a->list[u] = a->list[u]->next;
        temp->next = NULL;
        edge_free(temp);
        return TRUE;
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
            return TRUE;
        }
        e = e->next;
    }
    return FALSE;
}

O_INLINE int adjlist_rmv_sym_edges(adjlist *a, int u, int v)
{
    return (adjlist_rmv_edge(a, u, v) && adjlist_rmv_edge(a, v, u));
}

O_INLINE int adjlist_has_edge(adjlist *a, int u, int v)
{
    for (edge *e = a->list[u]; e != NULL; e = e->next) 
    {
        if (e->head == v) 
        {
            return TRUE;
        }
    }
    return FALSE;
}

int adjlist_strongly_connected(const adjlist *a)
{
    const int num_v = a->num_v;
    int *group = (int*)malloc(num_v * sizeof(int));

    for (int u = 0; u < num_v; ++u) 
    {
        for (int v = 0; v < num_v; ++v) 
        {
            group[v] = FALSE;
        }

        group[u] = TRUE;
        adjlist_test_cc(a, group, u); // Call recursive function

        for (int v = 0; v < num_v; ++v) 
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
    int *visited = (int*)malloc(num_v * sizeof(int));
    
    int current; // The vertex
    for (int u = 0; u < num_v; ++u)
    {
        for (int v = 0; v < num_v; ++v)
        {
            visited[v] = FALSE;
        }

        gdm[u][u] = 0; // By convention
        current = u;
        int has_next = TRUE;

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
            visited[current] = TRUE;

            has_next = FALSE;
            double tmp = max;
            for (int v = 0; v < num_v; v++)
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

double *adjlist_cls(const adjlist *a)
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

void adjlist_graphml(const adjlist *a, FILE *out, const char *id)
{
    const int num_v = a->num_v;
    fprintf(out, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(out, "<graphml xmlns=\"http://graphml.graphdrawing.org/xmlns\"\n");
    fprintf(out, "xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n");
    fprintf(out, "xsi:schemaLocation=\"http://graphml.graphdrawing.org/xmlns http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd\">\n");

    if (id != NULL)
    {
        fprintf(out, "  <graph id=\"%s\" edgedefault=\"directed\">\n", id);
    }
    else
    {
        fprintf(out, "  <graph id=\"G\" edgedefault=\"directed\">\n");
    }
    int i;
    for (i = 0; i < num_v; ++i)
    {
        fprintf(out, "    <node id=\"v%d\"/>\n", i);
    }
    for (i = 0; i < num_v; ++i)
    {
        edge *e;
        for (e = a->list[i]; e != NULL; e = e->next)
        {
            fprintf(out, "    <edge source=\"v%d\" target=\"v%d\"/>\n", i, e->head);
        }
    }
    fprintf(out, "  </graph>\n");
    fprintf(out, "</graphml>\n");
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

O_INLINE void edge_free(edge *e)
{
    if (e->next != NULL)
    {
        edge_free(e->next);
    }
    free(e);
}

O_INLINE void adjlist_free(adjlist *a)
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

O_INLINE void adjlist_test_cc(const adjlist *a, int *group, int u)
{
    for (edge *e = a->list[u]; e != NULL; e = e->next) 
    {
        const int head = e->head;
        if (head != u && group[head] == FALSE)
        {
            group[head] = TRUE;
            adjlist_test_cc(a, group, head);
        }
    }
}
