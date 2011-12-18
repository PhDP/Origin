#ifndef SPECIESLIST_H
#define SPECIESLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "ivector.h"
#include "species.h"

// For C++ compilers:
#ifdef __cplusplus
extern "C" {
#endif

/** A node of the singly-linked list. */
typedef struct SLNode_
{
    /** The species. */
    species *species;

    /** Pointer to the next node. */
    struct SLNode_ *next;
}
SLNode;

/** A linked list of species objects. */
typedef struct
{
    /** Number of species in the list. */
    int size;

    /** First element of the list. */
    SLNode *head;

    /** Last element of the list. */
    SLNode *tail;
}
speciesList;

/** Initialize the list. */
speciesList *speciesList_init();

/** Insert a new species at the end of the list. */
void speciesList_add(speciesList *list, species *s);

/** Remove the node next to the supplied node. If 'NULL', remove the head of the list. Return 'true' if a node was removed. */
bool speciesList_rmv_next(speciesList *list, SLNode *node);

/** Remove extinct species from the list and return the number of extinctions. */
int speciesList_rmv_extinct(speciesList *list);

/** Remove extinct species from the list, add the lifespan of the extinct species to the vector, and return the number of extinctions. */
int speciesList_rmv_extinct2(speciesList *list, ivector *lifespan, int date);

/** Return a pointer to the 'nth' node. */
SLNode *speciesList_get(speciesList *list, int n);

/** Print the name of the populations with they population vector. */
void speciesList_print_pop(speciesList *list, FILE *out);

/** Free the memory of the list. */
void speciesList_free(speciesList *list);

#ifdef __cplusplus
}
#endif

#endif

