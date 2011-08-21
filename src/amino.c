#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "seshat.h"
#include "amino.h"
#include "seq.h"

inline const char* amino_name(char amino)
{
	switch(amino)
	{
	case 'A': 
		return "Alanine";
	case 'R': 
		return "Arginine";
	case 'N': 
		return "Asparagine";
	case 'D': 
		return "Aspartic acid";
	case 'C': 
		return "Cysteine";
	case 'E': 
		return "Glutamic acid";
	case 'Q': 
		return "Glutamine";
	case 'G': 
		return "Glycine";
	case 'H': 
		return "Histidine";
	case 'I': 
		return "Isoleucine";
	case 'L': 
		return "Leucine";
	case 'K': 
		return "Lysine";
	case 'M': 
		return "Methionine";
	case 'F': 
		return "Phenylalanine";
	case 'P': 
		return "Proline";
	case 'S': 
		return "Serine";
	case 'T': 
		return "Threonine";
	case 'W': 
		return "Tryptophan";
	case 'Y': 
		return "Tyrosine";
	case 'V': 
		return "Valine";
	default:  
		return NULL;
	}
}

inline const char* amino_1to3(char amino)
{
	switch(amino)
	{
	case 'A': 
		return "Ala";
	case 'R': 
		return "Arg";
	case 'N': 
		return "Asn";
	case 'D': 
		return "Asp";
	case 'C': 
		return "Cys";
	case 'Q': 
		return "Gln";
	case 'E': 
		return "Glu";
	case 'G': 
		return "Gly";
	case 'H': 
		return "His";
	case 'I': 
		return "Ile";
	case 'L': 
		return "Leu";
	case 'K': 
		return "Lys";
	case 'M': 
		return "Met";
	case 'F': 
		return "Phe";
	case 'P': 
		return "Pro";
	case 'S': 
		return "Ser";
	case 'T': 
		return "Thr";
	case 'W': 
		return "Trp";
	case 'Y': 
		return "Tyr";
	case 'V': 
		return "Val";
	default:  
		return NULL;
	}
}

inline AminoAcid amino_to_enum(char amino)
{
	switch(amino)
	{
	case 'A': 
		return ALA;
	case 'R': 
		return ARG;
	case 'N': 
		return ASN;
	case 'D': 
		return ASP;
	case 'C': 
		return CYS;
	case 'Q': 
		return GLN;
	case 'E': 
		return GLU;
	case 'G':
		return GLY;
	case 'H': 
		return HIS;
	case 'I': 
		return ILE;
	case 'L': 
		return LEU;
	case 'K': 
		return LYS;
	case 'M': 
		return MET;
	case 'F': 
		return PHE;
	case 'P': 
		return PRO;
	case 'S': 
		return SER;
	case 'T': 
		return THR;
	case 'W': 
		return TRP;
	case 'Y':
		return TYR;
	case 'V':
		return VAL;
	case 'Z':
		return STOP;
	default:
		exit(0);
	}
}

inline char enum_to_amino(AminoAcid amino)
{
	switch(amino)
	{
	case ALA: 
		return 'A';
	case ARG: 
		return 'R';
	case ASN: 
		return 'N';
	case ASP: 
		return 'D';
	case CYS: 
		return 'C';
	case GLN: 
		return 'Q';
	case GLU: 
		return 'E';
	case GLY: 
		return 'G';
	case HIS: 
		return 'H';
	case ILE: 
		return 'I';
	case LEU: 
		return 'L';
	case LYS: 
		return 'K';
	case MET: 
		return 'M';
	case PHE: 
		return 'F';
	case PRO: 
		return 'P';
	case SER: 
		return 'S';
	case THR: 
		return 'T';
	case TRP: 
		return 'W';
	case TYR: 
		return 'Y';
	case VAL: 
		return 'V';
	case STOP:
		return 'Z';
	default:
		return ' ';
	}
}

inline char amino_3to1(const char* amino)
{
	assert(strlen(amino) == 3);
	switch(amino[0])
	{
	case 'A': 
		if (amino[1] == 'r')
		{
			return 'R';
		}
		else if (amino[2] == 'n')
		{
			return 'N';
		}
		else if (amino[2] == 'p')
		{
			return 'D';
		}
		else
		{
			return 'A';
		}
	case 'G':
		if (amino[2] == 'u')
		{
			return 'E';
		}
		else if (amino[2] == 'n')
		{
			return 'Q';
		}
		else
		{
			return 'G';
		}
	case 'L':
		if (amino[1] == 'k')
		{
			return 'K';
		}
		else
		{
			return 'L';
		}
	case 'P':
		if (amino[1] == 'h')
		{
			return 'F';
		}
		else
		{
			return 'P';
		}
	case 'T': 
		if (amino[1] == 'r')
		{
			return 'W';
		}
		else if (amino[1] == 'y')
		{
			return 'Y';
		}
		else
		{
			return 'T';
		}
	case 'H':
	case 'I':
	case 'M':
	case 'S':
	case 'V':
	case 'C':
		return amino[0];
	default:
		return ' ';
	}
}

inline int amino_pubchem(char amino)
{
	switch(amino)
	{
	case 'A':
		return 5950;
	case 'R': 
		return 6322;
	case 'N': 
		return  236;
	case 'D': 
		return  424;
	case 'C': 
		return 5862;
	case 'E': 
		return  611;
	case 'Q': 
		return  738;
	case 'G': 
		return  750;
	case 'H': 
		return  773;
	case 'I': 
		return  791;
	case 'L': 
		return 6106;
	case 'K': 
		return  866;
	case 'M': 
		return  876;
	case 'F': 
		return  994;
	case 'P': 
		return  614;
	case 'S': 
		return  617;
	case 'T': 
		return 6288;
	case 'W': 
		return 6305;
	case 'Y': 
		return 1153;
	case 'V': 
		return 1182;
	default: 
		return 0;
	}
}

inline double amino_hydropathy_index(char amino)
{
	switch(amino)
	{
	case 'A': 
		return  1.8;
	case 'R': 
		return -4.5;
	case 'N': 
		return -3.5;
	case 'D': 
		return -3.5;
	case 'C': 
		return  2.5;
	case 'E': 
		return -3.5;
	case 'Q': 
		return -3.5;
	case 'G': 
		return -0.4;
	case 'H': 
		return -3.2;
	case 'I': 
		return  4.5;
	case 'L': 
		return  3.8;
	case 'K': 
		return -3.9;
	case 'M': 
		return  1.9;
	case 'F': 
		return  2.8;
	case 'P': 
		return -1.6;
	case 'S': 
		return -0.8;
	case 'T': 
		return -0.7;
	case 'W': 
		return -0.9;
	case 'Y': 
		return -1.3;
	case 'V': 
		return  4.2;
	default:  
		return  0.0;
	}
}

inline bool has_polar_side_chain(char amino)
{
	switch(amino)
	{
	case 'D':
	case 'E':
	case 'H':
	case 'K':
	case 'N':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'Y':
		return true;
	default:
		return false;
	}
}

inline bool is_valid_amino(char amino)
{
	switch(amino)
	{
	case 'A':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'V':
	case 'W':
	case 'Y':
		return true;
	default:
		return false;
	}
}

inline bool is_valid_amino2(char amino)
{
	switch(amino)
	{
	case 'A':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'V':
	case 'W':
	case 'Y':
	case 'Z':
		return true;
	default:
		return false;
	}
}

inline bool is_nonpolar(char amino)
{
	if (amino == 'F' || amino == 'L' || amino == 'I' || amino == 'V' || amino == 'G' || amino == 'P' || amino == 'A' || amino == 'M' || amino == 'W')
	{
		return true;
	}
	else
	{
		return false;
	}
}

inline bool is_polar(char amino)
{
	if (amino == 'S' || amino == 'Y' || amino == 'C' || amino == 'T' || amino == 'Q' || amino == 'N')
	{
		return true;
	}
	else
	{
		return false;
	}
}

inline bool is_basic(char amino)
{
	if (amino == 'H' || amino == 'K' || amino == 'R')
	{
		return true;
	}
	else
	{
		return false;
	}
}

inline bool is_acidic(char amino)
{
	if (amino == 'D' || amino == 'E')
	{
		return true;
	}
	else
	{
		return false;
	}
}
