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

species *species_init0(int subpopulations, int time_of_birth, int n_genotypes)
{
    species *temp = (species*)malloc(sizeof(species));

    temp->subpops = subpopulations;
    temp->n_genotypes = n_genotypes;
    temp->birth = time_of_birth;  

    temp->n = (int*)malloc(subpopulations * sizeof(int));

    if (n_genotypes > 0)
    {
        temp->genotypes = (int**)malloc(subpopulations * sizeof(int*));
        for (int i = 0; i < n_genotypes; ++i)
        {
            temp->genotypes[i] = (int*)malloc(n_genotypes * sizeof(int));
        }
    }
    else
    {
        temp->genotypes = NULL;
    }

    return temp;
}

species *species_init1(int subpopulations, int fill, int time_of_birth, int n_genotypes)
{
    species *temp = (species*)malloc(sizeof(species));

    temp->subpops = subpopulations;
    temp->n_genotypes = n_genotypes;
    temp->birth = time_of_birth;  

    temp->n = (int*)malloc(subpopulations * sizeof(int));
    for (int i = 0; i < subpopulations; ++i)
    {
        temp->n[i] = fill;
    }

    if (n_genotypes > 0)
    {
        temp->genotypes = (int**)malloc(subpopulations * sizeof(int*));
        for (int i = 0; i < subpopulations; ++i)
        {
            temp->genotypes[i] = (int*)malloc(n_genotypes * sizeof(int));
            temp->genotypes[i][0] = fill;
            for (int j = 1; j < n_genotypes; ++j)
            {
                temp->genotypes[i][j] = 0;
            }
        }
    }
    else
    {
        temp->genotypes = NULL;
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

void species_print(const species *s, FILE *out)
{
    fprintf(out, "  birth: %d\n", s->birth);
    
    fprintf(out, "  populations: ");
    for (int i = 0; i < s->subpops; ++i)
    {
        fprintf(out, "%5d ", s->n[i]);
    }
    fprintf(out, "\n");
    
    for (int i = 0; i < s->n_genotypes; ++i)
    {
        fprintf(out, "  genotype %2d: ", i);
        for (int j = 0; j < s->subpops; ++j)
        {
            fprintf(out, "%5d ", s->genotypes[j][i]);
        }
        fprintf(out, "\n");
    }
    fprintf(out, "\n");
}

void species_free(species *s)
{
    if (s->genotypes != NULL)
    {
        for (int i = 0; i < s->subpops; ++i)
        {
            free(s->genotypes[i]);
        }
        free(s->genotypes);
    }
    free(s->n);
    free(s);
}
