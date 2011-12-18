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

/** Initialize a structured population with a given number of subpopulations. */
species *species_init0(int subpopulations, int time_of_birth, int n_genotypes);

/** Initialize a structured population with a given number of subpopulations and fill. */
species *species_init1(int subpopulations, int fill, int time_of_birth, int n_genotypes);

/** Return true if the population has still individuals. */
bool species_is_extant(const species *pop);

/** Return true if the population is extinct. */
bool species_is_extinct(const species *pop);

/** Return the total population. */
int species_total(const species *pop);

/** Print basic info on the species. */
void species_print(const species *s, FILE *out);

/** Free the memory. */
void species_free(species *pop);

#endif
