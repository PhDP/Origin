#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#include "common.h"
#include "specieslist.h"
#include "ivector.h"
#include "species.h"

ORIGIN_INLINE speciesList *speciesList_init()
{
    speciesList *temp = (speciesList*)malloc(sizeof(speciesList));

    temp->size = 0;
    temp->head = NULL;
    temp->tail = NULL;

    return temp;
}

// Always add the species at the end;
ORIGIN_INLINE void speciesList_add(speciesList *list, species *s)
{
    // Create the SLNode object to contain the species
    SLNode *new_node = (SLNode*)malloc(sizeof(SLNode));
    new_node->species = s;
    new_node->next = NULL;

    // No species in the list;
    if (list->size == 0)
    {
        list->head = new_node;
        list->tail = new_node;
    }
    else
    {
        list->tail->next = new_node;
        list->tail = new_node;
    }
    list->size++;
}

ORIGIN_INLINE bool speciesList_rmv_next(speciesList *list, SLNode *node)
{
    SLNode *old_node;

    if (list->size == 0)
    {
        return false;
    }
    // Remove the head;
    if (node == NULL)
    {
        old_node = list->head;
        list->head = list->head->next;
    }
    else
    {
        if (node->next == NULL)
        {
            return false;
        }

        old_node = node->next;
        node->next = node->next->next;

        if (node->next == NULL)
        {
            list->tail = node;
        }
    }
    species_free(old_node->species);
    free(old_node);

    list->size--;
    return true;
}

ORIGIN_INLINE int speciesList_rmv_extinct(speciesList *list)
{
    if (list->size == 0)
    {
        return 0;
    }
    int extinctions = 0; // Number of extinctions
    SLNode *node = list->head;

    while (species_is_extant(node->species) == false)
    {
        speciesList_rmv_next(list, NULL);
        node = list->head;
    }
    while (node->next != NULL)
    {
        if (species_is_extant(node->next->species) == false)
        {
            speciesList_rmv_next(list, node);
            ++extinctions;
        }
        else
        {
            node = node->next;
        }
    }
    return extinctions;
}

ORIGIN_INLINE int speciesList_rmv_extinct2(speciesList *list, ivector *lifespan, int date)
{
    if (list->size == 0)
    {
        return 0;
    }
    int extinctions = 0; // Number of extinctions
    SLNode *node = list->head;

    while (species_is_extant(node->species) == false)
    {
        ivector_add(lifespan, date - node->next->species->birth);
        speciesList_rmv_next(list, NULL);
        ++extinctions;
        node = list->head;
    }
    while (node->next != NULL)
    {
        if (species_is_extant(node->next->species) == false)
        {
            ivector_add(lifespan, date - node->next->species->birth);
            speciesList_rmv_next(list, node);
            ++extinctions;
        }
        else
        {
            node = node->next;
        }
    }
    return extinctions;
}

ORIGIN_INLINE SLNode *speciesList_get(speciesList *list, int n)
{
    if (n < 0 || n >= list->size)
    {
        return NULL;
    }
    if (n == 0)
    {
        return list->head;
    }
    if (n == list->size - 1)
    {
        return list->tail;
    }

    SLNode *node = list->head;

    for (int i = 0; i < n; ++i)
    {
        node = node->next;
    }
    return node;
}

ORIGIN_INLINE void speciesList_print_pop(speciesList *list, FILE *out)
{
    SLNode *node = list->head;
    const int subpopulations = node->species->subpops;

    while (node != NULL)
    {
        for (int i = 0; i < subpopulations; ++i)
        {
            fprintf(out, "%d ( ", node->species->n[i]);
            for (int j = 0; j < node->species->n_genotypes; ++j)
            {
                fprintf(out, "%d ", node->species->genotypes[i][j]);
            }
            fprintf(out, ")");
        }
        fprintf(out, " = %5d ", species_total(node->species));
        fprintf(out, "\n");
        node = node->next;
    }
}

ORIGIN_INLINE void speciesList_free(speciesList *list)
{
    while (speciesList_rmv_next(list, NULL));
    free(list);
}
