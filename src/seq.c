#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include "hon.h"
#include "gcode.h"
#include "seq.h"
#include "amino.h"

/** Read a fasta file with a single sequence and return a pointer to a Fasta struct */
void read_fasta_file(const char* filename, int n, Fasta_seq *fasta)
{
	FILE* input = fopen(filename, "r");

	fseek(input, 0, SEEK_END); // seek to end of file
	const long file_size = ftell(input); // get the size of the file
	fseek(input, 0, SEEK_SET); // seek back to beginning of file

	// Read the entire file
	char *complete_file = (char*)malloc(file_size);
	size_t fread_size = fread((void*)complete_file, sizeof(char), file_size, fp);
	const int complete_file_size = strlen(complete_file);

	int i = 0;
	while (i < complete_file_size)
	{
		if (complete_file[i] == '>')
		{
			const int i0 = i;
			while (complete_file[i] != '\n')
			{
				++i;
			}
			fasta->seq_info = (char*)malloc(i - i0 + 1);
			strncpy(fasta->seq_info, complete_file + i0, i - i0);

			fasta->seq = (char*)malloc(complete_file_size);
			int j = 0;

			//printf("%d\n", i);

			while (i < complete_file_size)
			{
				if (complete_file[i] != '\n' && complete_file[i] != '\r')
				{
					fasta->seq[j] = complete_file[i];
					++j;
				}
				++i;
			}
			fasta->seq[j] = '\0';
			fasta->length = strlen(fasta->seq);
			break;
		}
	}
	fasta->type = get_type(fasta->seq);
	fclose(fp);
}

inline Sequence_type get_type(const char *seq)
{
	if (dna_pure_seq(seq))
	{
		return DNA;
	}
	if (rna_pure_seq(seq))
	{
		return RNA;
	}
	if (protein_pure_seq(seq))
	{
		return Protein;
	}
	return Other;
}

inline char dna_random_nuc(gsl_rng *rng)
{
	return "ATGC"[(int)(gsl_rng_uniform(rng) * 4)];
}

inline char dna_random_nuc_prob(gsl_rng *rng, double prob_a, double prob_t, double prob_g)
{
	const double r = gsl_rng_uniform(rng);
	if (r < prob_a)
	{
		return 'A';
	}
	else if (r < prob_a + prob_t)
	{
		return 'T';
	}
	else if (r < prob_a + prob_t + prob_g)
	{
		return 'G';
	}
	else
	{
		return 'C';
	}
}

inline char* dna_random_nuc_seq(gsl_rng *rng, int seq_size)
{
	assert(seq_size > 0);
	char* dna_seq = (char*)malloc(seq_size + 1);
	char nuc[4 + 1] = "ATGC";
	
	for (int i = 0; i < seq_size; ++i)
	{
		dna_seq[i] = nuc[(int)(gsl_rng_uniform(rng) * 4)];
	}	
	dna_seq[seq_size] = '\0';
	return dna_seq;
}

inline char rna_random_nuc(gsl_rng *rng)
{
	return "AUGC"[(int)(gsl_rng_uniform(rng) * 4)];
}

inline char rna_random_nuc_prob(gsl_rng *rng, double prob_a, double prob_u, double prob_g)
{
	const double r = gsl_rng_uniform(rng);
	if (r < prob_a)
	{
		return 'A';
	}
	else if (r < prob_a + prob_u)
	{
		return 'U';
	}
	else if (r < prob_a + prob_u + prob_g)
	{
		return 'G';
	}
	else
	{
		return 'C';
	}
}

inline char* rna_random_nuc_seq(gsl_rng *rng, int seq_size)
{
	assert(seq_size > 0);
	char *rna_seq = (char*)malloc(seq_size + 1);
	char nuc[4 + 1] = "AUGC";
	
	for (int i = 0; i < seq_size; ++i)
	{
		rna_seq[i] = nuc[(int)(gsl_rng_uniform(rng) * 4)];
	}	
	rna_seq[seq_size] = '\0';
	
	return rna_seq;
}

inline int a_count(const char *seq)
{
	int i = 0;
	int count = 0;
	while (seq[i] != '\0')
	{
		if (seq[i] == 'A')
		{
			++count;
		}
		++i;
	}
	return count;
}

inline int t_count(const char *seq)
{
	int i = 0;
	int count = 0;
	while (seq[i] != '\0')
	{
		if (seq[i] == 'T')
		{
			++count;
		}
		++i;
	}
	return count;
}

inline int u_count(const char *seq)
{
	int i = 0;
	int count = 0;
	while (seq[i] != '\0')
	{
		if (seq[i] == 'U')
		{
			++count;
		}
		++i;
	}
	return count;
}

inline int g_count(const char *seq)
{
	int i = 0;
	int count = 0;
	while (seq[i] != '\0')
	{
		if (seq[i] == 'G')
		{
			++count;
		}
		++i;
	}
	return count;
}

inline int c_count(const char *seq)
{
	int i = 0;
	int count = 0;
	while (seq[i] != '\0')
	{
		if (seq[i] == 'C')
		{
			++count;
		}
		++i;
	}
	return count;
}

inline int gc_count(const char *seq)
{
	int i = 0;
	int count = 0;
	while (seq[i] != '\0')
	{
		if (seq[i] == 'G' || seq[i] == 'C')
		{
			++count;
		}
		++i;
	}
	return count;
}

inline double gc_content(const char *seq)
{
	int i = 0;
	int count = 0;
	while (seq[i] != '\0')
	{
		if (seq[i] == 'G' || seq[i] == 'C')
		{
			++count;
		}
		++i;
	}
	return (double)count / i;
}

inline bool dna_pure_seq(const char *dna_seq)
{
	int i = 0;
	while (dna_seq[i] != '\0')
	{
		if (dna_seq[i] == 'A' || dna_seq[i] == 'T' || dna_seq[i] == 'G' || dna_seq[i] == 'C')
		{
			++i;
		}
		else
		{
			return false;
		}
	}
	return true;
}

inline bool rna_pure_seq(const char *rna_seq)
{
	int i = 0;
	while (rna_seq[i] != '\0')
	{
		if (rna_seq[i] == 'A' || rna_seq[i] == 'U' || rna_seq[i] == 'G' || rna_seq[i] == 'C')
		{
			++i;
		}
		else
		{
			return false;
		}
	}
	return true;
}

inline char *dna_rmv_amb(char *dna_seq)
{
	char *new_dna_seq = (char*)malloc(strlen(dna_seq));

	int count = 0;
	for (int i = 0; dna_seq[i] != '\0'; i++)
	{
		if (dna_seq[i] == 'A' || dna_seq[i] == 'T' || dna_seq[i] == 'G' || dna_seq[i] == 'C')
		{
			new_dna_seq[count++] = dna_seq[i];
		}
	}
	new_dna_seq = (char*)realloc((void*)new_dna_seq, count + 1);
	new_dna_seq[count] = '\0';

	return new_dna_seq;
}

inline char* rna_rmv_amb(char *rna_seq)
{
	char* new_rna_seq = (char*)malloc(strlen(rna_seq));

	int count = 0;
	for (int i = 0; rna_seq[i] != '\0'; ++i)
	{
		if (rna_seq[i] == 'A' || rna_seq[i] == 'U' || rna_seq[i] == 'G' || rna_seq[i] == 'C')
		{
			new_rna_seq[count++] = rna_seq[i];
		}
	}
	new_rna_seq = (char*)realloc((void*)new_rna_seq, count + 1);
	new_rna_seq[count] = '\0';

	return new_rna_seq;
}

inline char *dna_antisense(const char *dna_seq)
{
	//assert(dna_pure_seq(char *dna_seq));
	const int seq_len = strlen(dna_seq);
	char *dna_antisense = (char*)malloc(seq_len + 1);

	for (int i = 0; i < seq_len; ++i)
	{
		if (dna_seq[i] == 'T')
		{
			dna_antisense[seq_len - 1 - i] = 'A';
		}
		else if (dna_seq[i] == 'A')
		{
			dna_antisense[seq_len - 1 - i] = 'T';
		}
		else if (dna_seq[i] == 'G')
		{
			dna_antisense[seq_len - 1 - i] = 'C';
		}
		else
		{
			dna_antisense[seq_len - 1 - i] = 'G';
		}
	}
	dna_antisense[seq_len] = '\0';

	return dna_antisense;
}

inline char* transcription(const char* dna_seq)
{
	//assert(dna_pure_seq(const char *dna_seq));
	const int seq_len = strlen(dna_seq);
	char* rna_seq = (char*)malloc(seq_len + 1);

	for (int i = 0; i < seq_len; ++i)
	{
		if (dna_seq[i] == 'T')
		{
			rna_seq[i] = 'U';
		}
		else
		{
			rna_seq[i] = dna_seq[i];
		}
	}
	rna_seq[seq_len] = '\0';
	return rna_seq;
}

inline char *translation(const char *rna_seq)
{
	//assert(rna_pure_seq(rna_seq);
	const int n_amino = strlen(rna_seq) / 3;
	char* amino_seq = (char*)malloc(n_amino + 1);

	int i = 0, a = 0;
	#ifndef STDGCODE
	while (a < n_amino)
	{
		if (rna_seq[i] == 'U')
		{
			if (rna_seq[i + 1] == 'U')
			{
				if (rna_seq[i + 2] == 'U')
				{
					amino_seq[a] = GCODE_UUU;
				}
				else if (rna_seq[i + 2] == 'G')
				{
					amino_seq[a] = GCODE_UUG;
				}
				else if (rna_seq[i + 2] == 'C')
				{
					amino_seq[a] = GCODE_UUC;
				}
				else
				{
					amino_seq[a] = GCODE_UUA;
				}
			}
			else if (rna_seq[i + 1] == 'G')
			{
				if (rna_seq[i + 2] == 'U')
				{
					amino_seq[a] = GCODE_UGU;
				}
				else if (rna_seq[i + 2] == 'G')
				{
					amino_seq[a] = GCODE_UGG;
				}
				else if (rna_seq[i + 2] == 'C')
				{
					amino_seq[a] = GCODE_UGC;
				}
				else
				{
					amino_seq[a] = GCODE_UGA;
				}
			}
			else if (rna_seq[i + 1] == 'C')
			{
				if (rna_seq[i + 2] == 'U')
				{
					amino_seq[a] = GCODE_UCU;
				}
				else if (rna_seq[i + 2] == 'G')
				{
					amino_seq[a] = GCODE_UCG;
				}
				else if (rna_seq[i + 2] == 'C')
				{
					amino_seq[a] = GCODE_UCC;
				}
				else
				{
					amino_seq[a] = GCODE_UCA;
				}
			}
			else
			{
				if (rna_seq[i + 2] == 'U')
				{
					amino_seq[a] = GCODE_UAU;
				}
				else if (rna_seq[i + 2] == 'G')
				{
					amino_seq[a] = GCODE_UAG;
				}
				else if (rna_seq[i + 2] == 'C')
				{
					amino_seq[a] = GCODE_UAC;
				}
				else
				{
					amino_seq[a] = GCODE_UAA;
				}
			}
		}
		else if (rna_seq[i] == 'G')
		{
			if (rna_seq[i + 1] == 'U')
			{
				if (rna_seq[i + 2] == 'U')
				{
					amino_seq[a] = GCODE_GUU;
				}
				else if (rna_seq[i + 2] == 'G')
				{
					amino_seq[a] = GCODE_GUG;
				}
				else if (rna_seq[i + 2] == 'C')
				{
					amino_seq[a] = GCODE_GUC;
				}
				else
				{
					amino_seq[a] = GCODE_GUA;
				}
			}
			else if (rna_seq[i + 1] == 'G')
			{
				if (rna_seq[i + 2] == 'U')
				{
					amino_seq[a] = GCODE_GGU;
				}
				else if (rna_seq[i + 2] == 'G')
				{
					amino_seq[a] = GCODE_GGG;
				}
				else if (rna_seq[i + 2] == 'C')
				{
					amino_seq[a] = GCODE_GGC;
				}
				else
				{
					amino_seq[a] = GCODE_GGA;
				}
			}
			else if (rna_seq[i + 1] == 'C')
			{
				if (rna_seq[i + 2] == 'U')
				{
					amino_seq[a] = GCODE_GCU;
				}
				else if (rna_seq[i + 2] == 'G')
				{
					amino_seq[a] = GCODE_GCG;
				}
				else if (rna_seq[i + 2] == 'C')
				{
					amino_seq[a] = GCODE_GCC;
				}
				else
				{
					amino_seq[a] = GCODE_GCA;
				}
			}
			else
			{
				if (rna_seq[i + 2] == 'U')
				{
					amino_seq[a] = GCODE_GAU;
				}
				else if (rna_seq[i + 2] == 'G')
				{
					amino_seq[a] = GCODE_GAG;
				}
				else if (rna_seq[i + 2] == 'C')
				{
					amino_seq[a] = GCODE_GAC;
				}
				else
				{
					amino_seq[a] = GCODE_GAA;
				}
			}
		}
		else if (rna_seq[i] == 'C')
		{
			if (rna_seq[i + 1] == 'U')
			{
				if (rna_seq[i + 2] == 'U')
				{
					amino_seq[a] = GCODE_CUU;
				}
				else if (rna_seq[i + 2] == 'G')
				{
					amino_seq[a] = GCODE_CUG;
				}
				else if (rna_seq[i + 2] == 'C')
				{
					amino_seq[a] = GCODE_CUC;
				}
				else
				{
					amino_seq[a] = GCODE_CUA;
				}
			}
			else if (rna_seq[i + 1] == 'G')
			{
				if (rna_seq[i + 2] == 'U')
				{
					amino_seq[a] = GCODE_CGU;
				}
				else if (rna_seq[i + 2] == 'G')
				{
					amino_seq[a] = GCODE_CGG;
				}
				else if (rna_seq[i + 2] == 'C')
				{
					amino_seq[a] = GCODE_CGC;
				}
				else
				{
					amino_seq[a] = GCODE_CGA;
				}
			}
			else if (rna_seq[i + 1] == 'C')
			{
				if (rna_seq[i + 2] == 'U')
				{
					amino_seq[a] = GCODE_CCU;
				}
				else if (rna_seq[i + 2] == 'G')
				{
					amino_seq[a] = GCODE_CCG;
				}
				else if (rna_seq[i + 2] == 'C')
				{
					amino_seq[a] = GCODE_CCC;
				}
				else
				{
					amino_seq[a] = GCODE_CCA;
				}
			}
			else
			{
				if (rna_seq[i + 2] == 'U')
				{
					amino_seq[a] = GCODE_CAU;
				}
				else if (rna_seq[i + 2] == 'G')
				{
					amino_seq[a] = GCODE_CAG;
				}
				else if (rna_seq[i + 2] == 'C')
				{
					amino_seq[a] = GCODE_CAC;
				}
				else
				{
					amino_seq[a] = GCODE_CAA;
				}
			}
		}
		else
		{
			if (rna_seq[i + 1] == 'U')
			{
				if (rna_seq[i + 2] == 'U')
				{
					amino_seq[a] = GCODE_AUU;
				}
				else if (rna_seq[i + 2] == 'G')
				{
					amino_seq[a] = GCODE_AUG;
				}
				else if (rna_seq[i + 2] == 'C')
				{
					amino_seq[a] = GCODE_AUC;
				}
				else
				{
					amino_seq[a] = GCODE_AUA;
				}
			}
			else if (rna_seq[i + 1] == 'G')
			{
				if (rna_seq[i + 2] == 'U')
				{
					amino_seq[a] = GCODE_AGU;
				}
				else if (rna_seq[i + 2] == 'G')
				{
					amino_seq[a] = GCODE_AGG;
				}
				else if (rna_seq[i + 2] == 'C')
				{
					amino_seq[a] = GCODE_AGC;
				}
				else
				{
					amino_seq[a] = GCODE_AGA;
				}
			}
			else if (rna_seq[i + 1] == 'C')
			{
				if (rna_seq[i + 2] == 'U')
				{
					amino_seq[a] = GCODE_ACU;
				}
				else if (rna_seq[i + 2] == 'G')
				{
					amino_seq[a] = GCODE_ACG;
				}
				else if (rna_seq[i + 2] == 'C')
				{
					amino_seq[a] = GCODE_ACC;
				}
				else
				{
					amino_seq[a] = GCODE_ACA;
				}
			}
			else
			{
				if (rna_seq[i + 2] == 'U')
				{
					amino_seq[a] = GCODE_AAU;
				}
				else if (rna_seq[i + 2] == 'G')
				{
					amino_seq[a] = GCODE_AAG;
				}
				else if (rna_seq[i + 2] == 'C')
				{
					amino_seq[a] = GCODE_AAC;
				}
				else
				{
					amino_seq[a] = GCODE_AAA;
				}
			}
		}
		i += 3;
		++a;
	}
	#else
	while (a < n_amino)
	{
		if (rna_seq[i] == 'U')
		{
			if (rna_seq[i + 1] == 'U')
			{
				if (rna_seq[i + 2] == 'U' || rna_seq[i + 2] == 'C')
				{
					amino_seq[a] = 'F';
				}
				else
				{
					amino_seq[a] = 'L';
				}
			}
			else if (rna_seq[i + 1] == 'C')
			{
				amino_seq[a] = 'S';
			}
			else if (rna_seq[i + 1] == 'A')
			{
				if (rna_seq[i + 2] == 'U' || rna_seq[i + 2] == 'C')
				{
					amino_seq[a] = 'Y';
				}
				else
				{
					amino_seq[a] = 'Z';
				}
			}
			else
			{
				if (rna_seq[i + 2] == 'U' || rna_seq[i + 2] == 'C')
				{
					amino_seq[a] = 'C';
				}
				else if (rna_seq[i + 2] == 'A')
				{
					amino_seq[a] = 'Z';
				}
				else
				{
					amino_seq[a] = 'W';
				}
			}
		}
		else if (rna_seq[i] == 'C')
		{
			if (rna_seq[i + 1] == 'U')
			{
				amino_seq[a] = 'L';
			}
			else if (rna_seq[i + 1] == 'C')
			{
				amino_seq[a] = 'P';
			}
			else if (rna_seq[i + 1] == 'A')
			{
				if (rna_seq[i + 2] == 'U' || rna_seq[i + 2] == 'C')
				{
					amino_seq[a] = 'H';
				}
				else
				{
					amino_seq[a] = 'Q';
				}
			}
			else
			{
				amino_seq[a] = 'R';
			}
		}
		else if (rna_seq[i] == 'A')
		{
			if (rna_seq[i + 1] == 'U')
			{
				if (rna_seq[i + 2] == 'G')
				{                       
					amino_seq[a] = 'M';
				}
				else
				{
					amino_seq[a] = 'I';
				}
			}
			else if (rna_seq[i + 1] == 'C')
			{
				amino_seq[a] = 'T';
			}
			else if (rna_seq[i + 1] == 'A')
			{
				if (rna_seq[i + 2] == 'U' || rna_seq[i + 2] == 'C')
				{
					amino_seq[a] = 'N';
				}
				else
				{
					amino_seq[a] = 'K';
				}
			}
			else
			{
				if (rna_seq[i + 2] == 'U' || rna_seq[i + 2] == 'C')
				{
					amino_seq[a] = 'S';
				}
				else
				{
					amino_seq[a] = 'R';
				}
			}
		}
		else
		{
			if (rna_seq[i + 1] == 'U')
			{
				amino_seq[a] = 'V';
			}
			else if (rna_seq[i + 1] == 'C')
			{
				amino_seq[a] = 'A';
			}
			else if (rna_seq[i + 1] == 'A')
			{
				if (rna_seq[i + 2] == 'U' || rna_seq[i + 2] == 'C')
				{
					amino_seq[a] = 'D';
				}
				else
				{
					amino_seq[a] = 'E';
				}
			}
			else
			{
				amino_seq[a] = 'G';
			}
		}
		i += 3;
		++a;
	}
	#endif
	amino_seq[n_amino] = '\0';

	return amino_seq;
}
