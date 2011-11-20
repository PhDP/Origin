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

ORIGIN_INLINE SpeciesList *SpeciesList_init()
{
    SpeciesList *temp = (SpeciesList*)malloc(sizeof(SpeciesList));

    temp->size = 0;
    temp->head = NULL;
    temp->tail = NULL;

    return temp;
}

// Always add the species at the end;
ORIGIN_INLINE void SpeciesList_add(SpeciesList *list, Species *s)
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

ORIGIN_INLINE bool SpeciesList_rmv_next(SpeciesList *list, SLNode *node)
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
    Species_free(old_node->species);
    free(old_node);

    list->size--;
    return true;
}

ORIGIN_INLINE int SpeciesList_rmv_extinct(SpeciesList *list)
{
    if (list->size == 0)
    {
        return 0;
    }
    int extinctions = 0; // Number of extinctions
    SLNode *node = list->head;

    while (Species_is_extant(node->species) == false)
    {
        SpeciesList_rmv_next(list, NULL);
        node = list->head;
    }
    while (node->next != NULL)
    {
        if (Species_is_extant(node->next->species) == false)
        {
            SpeciesList_rmv_next(list, node);
            ++extinctions;
        }
        else
        {
            node = node->next;
        }
    }
    return extinctions;
}

ORIGIN_INLINE int SpeciesList_rmv_extinct2(SpeciesList *list, ivector *lifespan, int date)
{
    if (list->size == 0)
    {
        return 0;
    }
    int extinctions = 0; // Number of extinctions
    SLNode *node = list->head;

    while (Species_is_extant(node->species) == false)
    {
        ivector_add(lifespan, date - node->next->species->birth);
        SpeciesList_rmv_next(list, NULL);
        ++extinctions;
        node = list->head;
    }
    while (node->next != NULL)
    {
        if (Species_is_extant(node->next->species) == false)
        {
            ivector_add(lifespan, date - node->next->species->birth);
            SpeciesList_rmv_next(list, node);
            ++extinctions;
        }
        else
        {
            node = node->next;
        }
    }
    return extinctions;
}

ORIGIN_INLINE SLNode *SpeciesList_get(SpeciesList *list, int n)
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

ORIGIN_INLINE void SpeciesList_print_pop(SpeciesList *list, FILE *out)
{
    SLNode *node = list->head;
    const int subpopulations = node->species->subpops;

    if (out != NULL)
    {
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
            fprintf(out, " = %5d ", Species_total(node->species));
            fprintf(out, "\n");
            node = node->next;
        }
    }
    else
    {
        while (node != NULL)
        {
            for (int i = 0; i < subpopulations; ++i)
            {
                printf("%d ( ", node->species->n[i]);
                for (int j = 0; j < node->species->n_genotypes; ++j)
                {
                    printf("%d ", node->species->genotypes[i][j]);
                }
                printf(")");
            }
            printf(" = %5d ", Species_total(node->species));
            printf("\n");
            node = node->next;
        }
    }
}

ORIGIN_INLINE void SpeciesList_free(SpeciesList *list)
{
    while (SpeciesList_rmv_next(list, NULL));
    free(list);
}
