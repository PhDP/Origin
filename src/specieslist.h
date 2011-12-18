#ifndef species_list_H
#define species_list_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "ivector.h"
#include "species.h"

/** A node of the singly-linked list. */
typedef struct slnode_
{
    species *sp; /** The species. */

    struct slnode_ *next; /** Pointer to the next node. */
}
slnode;

/** A linked list of species objects. */
typedef struct
{
    /** Number of species in the list. */
    int size;

    /** First element of the list. */
    slnode *head;

    /** Last element of the list. */
    slnode *tail;
}
species_list;

/** Initialize the list. */
species_list *species_list_init();

/** Insert a new species at the end of the list. */
void species_list_add(species_list *list, species *s);

/** Remove the node next to the supplied node. If 'NULL', remove the head of the list. Return 'true' if a node was removed. */
bool species_list_rmv_next(species_list *list, slnode *node);

/** Remove extinct species from the list and return the number of extinctions. */
int species_list_rmv_extinct(species_list *list);

/** Remove extinct species from the list, add the lifespan of the extinct species to the vector, and return the number of extinctions. */
int species_list_rmv_extinct2(species_list *list, ivector *lifespan, int date);

/** Return a pointer to the 'nth' node. */
slnode *species_list_get(species_list *list, int n);

/** Print the name of the populations with they population vector. */
void species_list_print_pop(species_list *list, FILE *out);

/** Free the memory of the list. */
void species_list_free(species_list *list);

#endif
