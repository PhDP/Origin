#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <float.h>
#include "hon.h"
#include "graph2.h"
#include "utils.h"

void graph2_init(graph2 *g, int vertices)
{
	g->num_v = vertices;
	g->num_e = (int*)calloc(vertices, sizeof(int));
	g->adjlist = (edge**)calloc(vertices, sizeof(edge*));
}

bool graph2_has_edge(graph2 *g, int u, int v)
{
	for (edge *e = g->adjlist[u]; e != NULL; e = e->next) 
	{
		if (e->head == v) 
		{
			return true;
		}
	}
	return false;
}
