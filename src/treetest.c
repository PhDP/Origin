// Generate random geometric graphs until a connected one is found.
//
// gcc -O3 -o treetest treetest.c

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "treenode.h"

int main(int argc, const char *argv[])
{

    treenode *root = treenode_init(NULL, "A", NULL);

    char *newick = treenode_simple_newick(root);
    printf("%s\n", newick);
    free(newick);

    treenode *b = treenode_init(root, "B", NULL);
    treenode *c = treenode_init(root, "C", NULL);
    treenode_set_children(root, b, c);

    newick = treenode_simple_newick(root);
    printf("%s\n", newick);
    free(newick);

    treenode *e = treenode_init(root, "E", NULL);
    treenode *d = treenode_init(root, "D", NULL);
    treenode_set_children(b, e, d);

    newick = treenode_simple_newick(root);
    printf("%s\n", newick);
    free(newick);

    return EXIT_SUCCESS; // yeppie !
}
