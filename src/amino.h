// Elementary functions on amino acids.

#ifndef AMINO_H_
#define AMINO_H_

#include <stdbool.h>
#include "hon.h"

// For C++ compilers:
#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	ALA, ARG, ASN, ASP, CYS, GLN, GLU, GLY, HIS, ILE, LEU, LYS, MET, PHE, PRO, SER, THR, TRP, TYR, VAL, STOP
} AminoAcid;

/** Return the complete name for the given 1-letter code amino acid */
const char* amino_name(char amino);

/** Return the 3-letters code for the given 1-letter code amino acid */
const char* amino_1to3(char amino);

/** Return the enum for the given 1-letter code */
AminoAcid amino_to_enum(char amino);

/** Return the char for the amino acid */
char enum_to_amino(AminoAcid amino);

/** Return the 1-letter code for the given 3-letters code amino acid */
char amino_3to1(const char* amino);

/** Return the PubChem id of the given amino acid */
int amino_pubchem(char amino);

/** Return the hydropathy index */
double amino_hydropathy_index(char amino);

/** Return true if the amino acid has a polar side chain */
bool has_polar_side_chain(char amino);

/** Return true if the amino acid is valid */
bool is_valid_amino(char amino);

/** Return true if the amino acid is valid. Consider 'Z' (STOP) valid */
bool is_valid_amino2(char amino);

/** Return true if the amino acid is nonpolar */
bool is_nonpolar(char amino);

/** Return true if the amino acid is polar */
bool is_polar(char amino);

/** Return true if the amino acid is basic */
bool is_basic(char amino);

/** Return true if the amino acid is acidic */
bool is_acidic(char amino);

#ifdef __cplusplus
}
#endif

#endif
