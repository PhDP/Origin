// IO and string functions.

#ifndef STR_H_
#define STR_H_

#include <stdbool.h>

// For C++ compilers:
#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////
// Read options supplied by the user

/** Return the substring in a string of the form [something]=[substring]. */
char *get_opt_s(const char *arg);

/** Return the int in a string of the form [something]=[int]. */
int get_opt_i(const char *arg);

/** Return the double in a string of the form [something]=[double]. */
double get_opt_d(const char *arg);

/**
* Send an array of strings and the name of an option. The function will
* look for an string of the form -OPTION=X and send X to param. e.g.:
* <br>
* <br>int i;
* <br>read_opt_i("x", argv, 5, &i);
* <br>
* <br>will read the 5 strings in argv, seach for a string of the form 
* "-x=A" and copy A to i.
*/
bool read_opt_i(const char *option, const char *argv[], int n, int *param);

/**
* Send an array of strings and the name of an option. The function will
* look for an string of the form -OPTION=X and send X to param. e.g.:
* <br>
* <br>double s;
* <br>read_opt_d("selection", argv, 5, &s);
* <br>
* <br>will read the 5 strings in argv, seach for a string of the form 
* "-selection=A" and copy A to s.
*/
bool read_opt_d(const char *option, const char *argv[], int n, double *param);

/**
* Send an array of strings and the name of an option. The function will
* look for an string with the form -OPTION=X and send X to param. e.g.:
* <br>
* <br>char *s;
* <br>read_opt_i("x", argv, 5, s);
* <br>
* <br>Will read the 5 strings in argv, seach for a string of the form 
* "-x=A" and copy A to s.
*/
bool read_opt_s(const char *option, const char *argv[], int n, char *param);

////////////////////////////////////////////////////////////////////
// Formatting

/** Transform a number of seconds into a more detailed string (days, hours, minutes, seconds). */
char *sec_to_string(long seconds);

/** Transform an integer to a string with spaces (e.g.: 19939200 => "19 939 200"). */
char *int_with_space(int integer);

/** Transform a long to a string with spaces (e.g.: 72036854775808 => "72 036 854 775 808"). */
char *long_with_space(long integer);

/** Convert the string's uppercase characters to lowercase. */
void convert_to_lower_case(char *str);

/** Convert the string's lowercase characters to uppercase. */
void convert_to_upper_case(char *str);

/** Return a copy of the string with upper case characters converted to lower case. */
char *get_lower_case(const char *str);

/** Return a copy of the string with lower case characters converted to upper case. */
char *get_upper_case(const char *str);

#ifdef __cplusplus
}
#endif

#endif
