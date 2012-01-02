#ifndef SPECIES_H
#define SPECIES_H

#include <stdbool.h>

/** An array of ints for individuals in different subpopulations. */
typedef struct
{
    /** Number of subpopulations. */
    int subpops;

    /** Array of individuals per subpopulations. */
    int *n;
    
    /** Number of distinct genotypes. */
    int n_genotypes;

    /** Number of individual of each genotype per subpopulations. */
    int **genotypes;
        
    /** Date of birth. */
    int birth;
}
species;

/** Initialize a structured population with a given number of subpopulations and fill. */
species *species_init(int subpopulations, int time_of_birth, int n_genotypes);

/** Return true if the population has still individuals. */
bool species_is_extant(const species *pop);

/** Return true if the population is extinct. */
bool species_is_extinct(const species *pop);

/** Return the total population. */
int species_total(const species *pop);

/** Free the memory. */
void species_free(species *pop);

#endif
