#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#include "species.h"

Species *Species_init0(int subpopulations, int time_of_birth, int n_genotypes)
{
	Species *temp = (Species*)malloc(sizeof(Species));
	
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

Species *Species_init1(int subpopulations, int fill, int time_of_birth, int n_genotypes)
{
	Species *temp = (Species*)malloc(sizeof(Species));
	
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

ORIGIN_INLINE bool Species_is_extant(const Species *s)
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

ORIGIN_INLINE bool Species_is_extinct(const Species *s)
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

ORIGIN_INLINE int Species_total(const Species *s)
{
	int sum = 0;
	
	for (int i = 0; i < s->subpops; ++i)
	{
		sum += s->n[i];
	}
	return sum;
}

void Species_printf(const Species *s)
{
	printf("  birth: %d\n", s->birth);
	
	printf("  populations: ");
	for (int i = 0; i < s->subpops; ++i)
	{
		printf("%5d ", s->n[i]);
	}
	printf("\n");
	
	for (int i = 0; i < s->n_genotypes; ++i)
	{
		printf("  genotype %2d: ", i);
		for (int j = 0; j < s->subpops; ++j)
		{
			printf("%5d ", s->genotypes[j][i]);
		}
		printf("\n");
	}
	printf("\n");
}

void Species_free(Species *s)
{
	free(s->n);

	for (int i = 0; i < s->n_genotypes; ++i)
	{
		free(s->genotypes[i]);
	}
	if (s->genotypes != NULL)
	{
		free(s->genotypes);
	}
	free(s);
}
