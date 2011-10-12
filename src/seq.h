/**
 * Basic functions to analyze sequences
 ****************************************************************/

#ifndef SEQ_H_
#define SEQ_H_

#include <stdbool.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

// For C++ compilers:
#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
	Protein = 0,
	RNA = 1,
	DNA = 2,
	DNAorRNA = 3,
	Other = 4,
}
Sequence_type;

typedef struct
{
	char *seq;
	char *seq_info;
	int length;
	Sequence_type type;
}
Fasta_seq;

/** Deduce the type of a sequence. */
Sequence_type get_type(const char *seq);

/** Extract the nth sequence from a file in fasta format. */
void read_fasta_file(const char *filename, int n, Fasta_seq *fasta);

/** Return 'A', 'T', 'C' or 'G'. */
char dna_random_nuc(gsl_rng *rng);

/** Return a random nucleotide with given probabilities (with the probability for C = 1 - prob(A + T + G)). */
char dna_random_nuc_prob(gsl_rng *rng, double prob_a, double prob_t, double prob_g);

/** Return a sequence of 'A', 'T', 'C' or 'G'. */
char* dna_random_nuc_seq(gsl_rng *rng, int seq_size);

/** Return 'A', 'U', 'C' or 'G'. */
char rna_random_nuc(gsl_rng *rng);

/** Return a random nucleotide with given probabilities (with the probability for C = 1 - prob(A + U + G)). */
char rna_random_nuc_prob(gsl_rng *rng, double prob_a, double prob_u, double prob_g);

/** Return a sequence of 'A', 'U', 'C' or 'G'. */
char *rna_random_nuc_seq(gsl_rng *rng, int seq_size);

/** Number of adenosine 'A' in the sequence. */
int a_count(const char *seq);

/** Number of thymidine 'T' in the sequence. */
int t_count(const char *seq);

/** Number of uracil 'U' in the sequence. */
int u_count(const char *seq);

/** Number of guanine 'G' in the sequence. */
int g_count(const char *seq);

/** Number of cytosine 'C' in the sequence. */
int c_count(const char *seq);

/** Number of cytosine 'C' and guanine 'G' in the sequence. */
int gc_count(const char *seq);

/** Return GC content (number of 'G' + number of 'C') / size. */
double gc_content(const char *seq);

/** Return 'true' if the sequence is only made of 'G', 'C', 'T' or 'A'. */
bool dna_pure_seq(const char *dna_seq);

/** Return 'true' if the sequence is only made of 'G', 'C', 'U' or 'A'. */
bool rna_pure_seq(const char *rna_seq);

/** Return a sequence with everything removed except 'G', 'C', 'T' and 'A'. */
char *dna_rmv_amb(char *dna_seq);

/** Return a sequence with everything removed except 'G', 'C', 'U' and 'A'. */
char *rna_rmv_amb(char *rna_seq);

/** Return the antisense stand of a DNA sequence. */
char *dna_antisense(const char *dna_seq);

/** DNA -> RNA. Start reading when encountering a start codon. Both the DNA sequence and the resulting RNA sequence are in the 5' -> 3' direction. */
char *transcription(const char *dna_seq);

/** Translate RNA to an amino acid sequence. */
char *translation(const char *rna_seq);

#ifdef __cplusplus
}
#endif

#endif
