#ifndef TREENODE_H_
#define TREENODE_H_

#include <stdbool.h>
#include "hon.h"

// For C++ compilers:
#ifdef __cplusplus
extern "C" {
#endif

/** A strictly binary tree. */
typedef struct treenode_
{
	/** Name of the node. */
	char *name;
	
	/** Pointer to the parent. */
	struct treenode_ *p;
	
	/** Pointer to the 'left' child. */
	struct treenode_ *l;
	
	/** Pointer to the 'right' child. */
	struct treenode_ *r;
	
	/** Data inside the node. */
	void *data;
}
treenode;

/** Initialize a treenode object. */
treenode *treenode_init(treenode *p, char *name, void *data);

/** Set the children of the node. */
void treenode_set_children(treenode *t, treenode *l, treenode *r); // TODO: Replace by a define (and test!)

/** Check if the subtree is really a strictly binary tree. */
bool treenode_sbinary(treenode *t);

/** Return 'true' if the node is a leaf. */
bool treenode_leaf(treenode *t);

/** Return 'true' if the node is a root. */
bool treenode_root(treenode *t);

/** Return 'true' if the node is an internal node. */
bool treenode_internal(treenode *t);

/** Return the simple newick tree. */
char *treenode_simple_newick(treenode *t);

/** Recursively free the memory of the node. The tree node doesn't own the data at the end of the void pointer so the user has to free this memory manually (or reimplement this function). */
void treenode_free(treenode *t);

#ifdef __cplusplus
}
#endif

#endif
