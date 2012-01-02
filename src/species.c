#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#include "common.h"
#include "species.h"

species *species_init(int subpopulations, int time_of_birth, int n_genotypes)
{
    species *temp = (species*)malloc(sizeof(species));

    temp->subpops = subpopulations;
    temp->n_genotypes = n_genotypes;
    temp->birth = time_of_birth;

    temp->n = (int*)malloc(subpopulations * sizeof(int));
    for (int i = 0; i < subpopulations; ++i)
    {
        temp->n[i] = 0;
    }
    temp->genotypes = (int**)malloc(n_genotypes * sizeof(int*));
    for (int i = 0; i < n_genotypes; ++i)
    {
        temp->genotypes[i] = (int*)malloc(subpopulations * sizeof(int));
        for (int j = 0; j < subpopulations; ++j)
        {
            temp->genotypes[i][j] = 0;
        }
    }
    return temp;
}

ORIGIN_INLINE bool species_is_extant(const species *s)
{
    for (int i = 0; i < s->subpops; ++i)
    {
        if (s->n[i] > 0)
        {
            return true;
        }
    }
    return false;
}

ORIGIN_INLINE bool species_is_extinct(const species *s)
{
    for (int i = 0; i < s->subpops; ++i)
    {
        if (s->n[i] > 0)
        {
            return false; 
        }
    }
    return true;
}

ORIGIN_INLINE int species_total(const species *s)
{
    int sum = 0;

    for (int i = 0; i < s->subpops; ++i)
    {
        sum += s->n[i];
    }
    return sum;
}

void species_free(species *s)
{
    for (int i = 0; i < s->n_genotypes; ++i)
    {
        free(s->genotypes[i]);
    }
    free(s->genotypes);
    free(s->n);
    free(s);
}
