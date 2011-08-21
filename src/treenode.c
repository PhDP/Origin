#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "hon.h"
#include "tnode.h"

/*

treenode *treenode_init(treenode *p, char *name, void *data)
{
	treenode *temp = (treenode*)malloc(sizeof(treenode));
	
	temp->name = name;
	temp->p = p;
	temp->l = NULL;
	temp->r = NULL;
	temp->data = NULL;
	
	return temp;
}

void treenode_set_children(treenode *t, treenode *l, treenode *r)
{
	t->l = l;
	t->r = r;
}

bool treenode_sbinary(treenode *t)
{
	if (t->l == NULL && t->r == NULL)
	{
		return true;
	}
	else if (t->l != NULL && t->r != NULL)
	{
		return (treenode_sbinary(l) && treenode_sbinary(r));
	}
	else
	{
		return false;
	}
}

bool treenode_leaf(treenode *t)
{
	return (t->l == NULL);
}

bool treenode_root(treenode *t);
{
	return (t->p == NULL);
}

bool treenode_internal(treenode *t);
{
	return (t->p != NULL && t->l != NULL);
}

char *treenode_simple_newick(treenode *t)
{
	sprintf (char *str, const char *format, ...);
	
	if (treenode_leaf(t))
	{
		const int name_length = strlen(t->name);
		char *newick = (char*)malloc(name_length + 20);
	}
	else
	{
		char *l_newick = hontnode_simple_newick(t);
		char *r_newick = hontnode_simple_newick(r);
	}
}

void treenode_free(treenode *t)
{
	treenode_free(t->l);
	treenode_free(t->r);
	free(t->name);
	t->p = NULL;
	t->l = NULL;
	t->r = NULL;
	t->data = NULL;
	free(t);
}

*/
