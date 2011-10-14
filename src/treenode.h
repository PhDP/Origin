/*! \file
 *
 * \brief A generic strictly binary tree.
 *
 */ 

#ifndef tnode_H_
#define tnode_H_

#include <stdbool.h>
#include "common.h"

// For C++ compilers:
#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief A strictly binary tree.
 */
typedef struct tnode_
{
    char *name; /**< Name of the node. */

    struct tnode_ *p; /**< Pointer to the parent. */

    struct tnode_ *l; /**< Pointer to the 'left' child. */

    struct tnode_ *r; /**< Pointer to the 'right' child. */

    void *data; /**< Data inside the node. */
}
tnode;

/** Initialize a tnode object. */
tnode *tnode_init(tnode *p, char *name, void *data);

/** Set the children of the node. */
void tnode_set_children(tnode *t, tnode *l, tnode *r); // TODO: Replace by a define (and test!)

/** Number of edges in the subtree. */
int tnode_numedges(tnode *t);

/** Number of leaves in the subtree. */
int tnode_numleaves(tnode *t);

/** Number of nodes between this node and the root */
int tnode_toroot(tnode *t);

/** Check if the subtree is really a strictly binary tree. */
int tnode_sbinary(tnode *t);

/** Return 'true' if the node is a leaf. */
int tnode_leaf(tnode *t);

/** Return 'true' if the node is a root. */
int tnode_root(tnode *t);

/** Return 'true' if the node is an internal node. */
int tnode_internal(tnode *t);

/** Return the simple newick tree. */
char *tnode_simple_newick(tnode *t);

/** Recursively free the memory of the node. The tree node doesn't own the data at the end of the void pointer so the user has to free this memory manually (or reimplement this function). */
void tnode_free(tnode *t);

#ifdef __cplusplus
}
#endif

#endif
