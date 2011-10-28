#ifndef SPECIES_H_
#define SPECIES_H_

// For C++ compilers:
#ifdef __cplusplus
extern "C" {
#endif

/**
 * An array of ints for individuals in different subpopulations.
 */
typedef struct
{
    int subpops; /**< Number of subpopulations. */

    int *n; /**< Array of individuals per subpopulations. */

    int n_genotypes; /**< Number of distinct genotypes. */

    int **genotypes; /**< Number of individual of each genotype per subpopulations. */

    int birth; /**< Date of birth. */
}
Species;

/** Initialize a structured population with a given number of subpopulations. */
Species *Species_init0(int subpopulations, int time_of_birth, int n_genotypes);

/** Initialize a structured population with a given number of subpopulations and fill. */
Species *Species_init1(int subpopulations, int fill, int time_of_birth, int n_genotypes);

/** Return true if the population has still individuals. */
int Species_is_extant(const Species *pop);

/** Return true if the population is extinct. */
int Species_is_extinct(const Species *pop);

/** Return the total population. */
int Species_total(const Species *pop);

/** Print basic info on the species. */
void Species_printf(const Species *s);

/** Free the memory. */
void Species_free(Species *pop);

#ifdef __cplusplus
}
#endif

#endif

