#ifndef HON_SPECIESLIST_H
#define HON_SPECIESLIST_H

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
  Species *species;
  
  /** Pointer to the next node. */
  struct SLNode_ *next;
}
SLNode;

/** A linked list of Species objects. */
typedef struct
{
  /** Number of species in the list. */
  int size;
  
  /** First element of the list. */
  SLNode *head;
  
  /** Last element of the list. */
  SLNode *tail;
}
SpeciesList;

/** Initialize the list. */
SpeciesList *SpeciesList_init();

/** Insert a new species at the end of the list. */
void SpeciesList_add(SpeciesList *list, Species *s);

/** Remove the node next to the supplied node. If 'NULL', remove the head of the list. Return 'true' if a node was removed. */
bool SpeciesList_rmv_next(SpeciesList *list, SLNode *node);

/** Remove extinct species from the list and return the number of extinctions. */
int SpeciesList_rmv_extinct(SpeciesList *list);

/** Remove extinct species from the list, add the lifespan of the extinct species to the vector, and return the number of extinctions. */
int SpeciesList_rmv_extinct2(SpeciesList *list, ivector *lifespan, int date);

/** Return a pointer to the 'nth' node. */
SLNode *SpeciesList_get(SpeciesList *list, int n);

/** Print the name of the populations with they population vector. Print to the console if out == NULL. */
void SpeciesList_print_pop(SpeciesList *list, FILE *out);

/** Free the memory of the list. */
void SpeciesList_free(SpeciesList *list);

#ifdef __cplusplus
}
#endif

#endif

