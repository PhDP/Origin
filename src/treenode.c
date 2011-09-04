#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "common.h"
#include "treenode.h"

treenode *treenode_init(treenode *p, char *name, void *data)
{
	treenode *t = (treenode*)malloc(sizeof(treenode));

	t->name = name;
	t->p = p;
	t->l = NULL;
	t->r = NULL;
	t->data = NULL;

	return t;
}

inline void treenode_set_children(treenode *t, treenode *l, treenode *r)
{
	t->l = l;
	t->r = r;
}

int treenode_numedges(treenode *t)
{
	return (t->l == NULL) ? 0 : 2 + treenode_numedges(t->l) + treenode_numedges(t->r);
}

int treenode_numleaves(treenode *t)
{
  return 1 + treenode_numedges(t) / 2;
}

int treenode_toroot(treenode *t)
{
	return (t->p == NULL) ? 0 : 1 + treenode_toroot(t->p);
}

bool treenode_sbinary(treenode *t)
{
	if (t->l == NULL && t->r == NULL)
	{
		return true;
	}
	else if (t->l != NULL && t->r != NULL)
	{
		return (treenode_sbinary(t->l) && treenode_sbinary(t->r));
	}
	else
	{
		return false;
	}
}

inline bool treenode_leaf(treenode *t)
{
	return (t->l == NULL);
}

inline bool treenode_root(treenode *t)
{
	return (t->p == NULL);
}

inline bool treenode_internal(treenode *t)
{
	return (t->p != NULL && t->l != NULL);
}

char *treenode_simple_newick(treenode *t)
{
	char *str;
	if (treenode_leaf(t))
	{
		str = (char*)malloc(strlen(t->name) + 2);
		if (t->p == NULL)
		{
			sprintf(str, "%s;", t->name);
		}
		else
		{
			sprintf(str, "%s", t->name);
		}
	}
	else
	{
		char *lnewick = treenode_simple_newick(t->l);
		char *rnewick = treenode_simple_newick(t->r);
		const int lrlength = strlen(lnewick) + strlen(rnewick);
		str = (char*)malloc(lrlength + strlen(t->name) + 6);
		if (t->p == NULL)
		{
			sprintf(str, "(%s,%s):%s;", lnewick, rnewick, t->name);
		}
		else
		{
			sprintf(str, "(%s,%s):%s", lnewick, rnewick, t->name);
		}
		free(lnewick);
		free(rnewick);
	}
	return str;
}

void treenode_free(treenode *t)
{
	if (t->l != NULL)
	{
		treenode_free(t->l);
	}
	if (t->r != NULL)
	{
		treenode_free(t->r);
	}
	free(t->name);
	t->data = NULL;
	free(t);
}
