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

ORIGIN_INLINE species_list *species_list_init()
{
    species_list *temp = (species_list*)malloc(sizeof(species_list));

    temp->size = 0;
    temp->head = NULL;
    temp->tail = NULL;

    return temp;
}

// Always add the species at the end;
ORIGIN_INLINE void species_list_add(species_list *list, species *s)
{
    // Create the slnode object to contain the species
    slnode *new_node = (slnode*)malloc(sizeof(slnode));
    new_node->sp = s;
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

ORIGIN_INLINE bool species_list_rmv_next(species_list *list, slnode *node)
{
    slnode *old_node;

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
    species_free(old_node->sp);
    free(old_node);

    list->size--;
    return true;
}

ORIGIN_INLINE int species_list_rmv_extinct(species_list *list)
{
    if (list->size == 0)
    {
        return 0;
    }
    int extinctions = 0; // Number of extinctions
    slnode *node = list->head;

    while (species_is_extant(node->sp) == false)
    {
        species_list_rmv_next(list, NULL);
        node = list->head;
    }
    while (node->next != NULL)
    {
        if (species_is_extant(node->next->sp) == false)
        {
            species_list_rmv_next(list, node);
            ++extinctions;
        }
        else
        {
            node = node->next;
        }
    }
    return extinctions;
}

ORIGIN_INLINE int species_list_rmv_extinct2(species_list *list, ivector *lifespan, int date)
{
    if (list->size == 0)
    {
        return 0;
    }
    int extinctions = 0; // Number of extinctions
    slnode *node = list->head;

    while (species_is_extant(node->sp) == false)
    {
        ivector_add(lifespan, date - node->next->sp->birth);
        species_list_rmv_next(list, NULL);
        ++extinctions;
        node = list->head;
    }
    while (node->next != NULL)
    {
        if (species_is_extant(node->next->sp) == false)
        {
            ivector_add(lifespan, date - node->next->sp->birth);
            species_list_rmv_next(list, node);
            ++extinctions;
        }
        else
        {
            node = node->next;
        }
    }
    return extinctions;
}

ORIGIN_INLINE slnode *species_list_get(species_list *list, int n)
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

    slnode *node = list->head;

    for (int i = 0; i < n; ++i)
    {
        node = node->next;
    }
    return node;
}

ORIGIN_INLINE void species_list_print_pop(species_list *list, FILE *out)
{
    slnode *node = list->head;
    const int subpopulations = node->sp->subpops;

    while (node != NULL)
    {
        for (int i = 0; i < subpopulations; ++i)
        {
            fprintf(out, "%d ( ", node->sp->n[i]);
            for (int j = 0; j < node->sp->n_genotypes; ++j)
            {
                fprintf(out, "%d ", node->sp->genotypes[i][j]);
            }
            fprintf(out, ")");
        }
        fprintf(out, " = %5d ", species_total(node->sp));
        fprintf(out, "\n");
        node = node->next;
    }
}

ORIGIN_INLINE void species_list_free(species_list *list)
{
    while (species_list_rmv_next(list, NULL));
    free(list);
}
