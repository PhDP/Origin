/*! \file
 *
 * \brief Elementary functions to handle strings.
 */ 

#ifndef STR_H_
#define STR_H_

// For C++ compilers:
#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////
// Read options supplied by the user

/**
 * \brief Read a matrix from a file and store it in a jagged array.
 *
 * This function will be replaced by a more sophisticated version that will
 * allow the user to specify where in the file the matrix is. Currently the
 * file must only contain the matrix separated with elements separated by spaces
 * and rows separated by the newline character.
 * 
 * \param    m       The jagged array where the matrix is going to be stored.
 * \param    nrows   Number of rows of the matrix.
 * \param    ncols   Number of columns of the matrix.
 * \param    input   The input file.
 */
void read_dmatrix(double **m, int nrows, int ncols, FILE *input);

/**
 * \brief Read a matrix from a file and store it in a jagged array.
 *
 * This function will be replaced by a more sophisticated version that will
 * allow the user to specify where in the file the matrix is. Currently the
 * file must only contain the matrix separated with elements separated by spaces
 * and rows separated by the newline character.
 * 
 * \param    m       The jagged array where the matrix is going to be stored.
 * \param    nrows   Number of rows of the matrix.
 * \param    ncols   Number of columns of the matrix.
 * \param    input   The input file.
 */
void read_imatrix(int **m, int nrows, int ncols, FILE *input);

/**
 * \brief Return the substring in a string of the form [option_name]=[substring].
 *
 * \param    arg   The argument read.
 * \return         The substring in "[option_name]=[substring]".
 */
char * get_opt_s(const char *arg);

/**
 * \brief Return the int in a string of the form [option_name]=[int].
 *
 * \param    arg   The argument read.
 * \return         The int in "[option_name]=[int]".
 */
int get_opt_i(const char *arg);

/**
 * \brief Return the double in a string of the form [option_name]=[double].
 *
 * \param    arg   The argument read.
 * \return         The double in "[option_name]=[double]".
 */
double get_opt_d(const char *arg);

/**
 * \brief Read an int from an option submitted to the program.
 * 
 * Send an array of strings and the name of an option. The function will
 * look for an string of the form -OPTION=X and send X to param. e.g.:
 * <br>
 * <br>int i;
 * <br>read_opt_i("x", argv, 5, &i);
 * <br>
 * <br>will read the 5 strings in argv, seach for a string of the form 
 * "-x=A" and copy A to i.
 *
 * \param   option   The name of the option.
 * \param   argv     The array of strings.
 * \param   n        Number of strings in argv.
 * \param   param    A pointer to the int where the result is stored.
 * \return           'true' (1) if the option was found, 'false' (0) otherwise.
 */
int read_opt_i(const char *option, const char *argv[], int n, int *param);

/**
 * \brief Read a double from an option submitted to the program.
 * 
 * Send an array of strings and the name of an option. The function will
 * look for an string of the form -OPTION=X and send X to param. e.g.:
 * <br>
 * <br>double s;
 * <br>read_opt_d("selection", argv, 5, &s);
 * <br>
 * <br>will read the 5 strings in argv, seach for a string of the form 
 * "-selection=A" and copy A to s.
 *
 * \param   option   The name of the option.
 * \param   argv     The array of strings.
 * \param   n        Number of strings in argv.
 * \param   param    A pointer to the double where the result is stored.
 * \return           'true' (1) if the option was found, 'false' (0) otherwise.
 */
int read_opt_d(const char *option, const char *argv[], int n, double *param);

/**
 * \brief Read an option submitted to the program.
 * 
 * Send an array of strings and the name of an option. The function will
 * look for an string with the form -OPTION=X and send X to param. e.g.:
 * <br>
 * <br>char *s;
 * <br>read_opt_i("x", argv, 5, s);
 * <br>
 * <br>Will read the 5 strings in argv, seach for a string of the form 
 * "-x=A" and copy A to s.
 *
 * \param   option   The name of the option.
 * \param   argv     The array of strings.
 * \param   n        Number of strings in argv.
 * \param   param    A pointer to a string where the option is printed. Make
 *                   sure the string has enough space to contain the option.
 * \return           'true' (1) if the option was found, 'false' (0) otherwise.
 */
int read_opt_s(const char *option, const char *argv[], int n, char *param);

////////////////////////////////////////////////////////////////////
// Formatting

/**
 * \brief Format a number of seconds to a string.
 *
 * Transform a number of seconds into a more detailed string (days, hours,
 * minutes, seconds).
 *
 * \param  seconds   The number to format.
 * \return           The seconds in a string with the format "DD days HH hours
 *                   MM minutes SS seconds".
 */
char *sec_to_string(long seconds);

/**
 * \brief Format a 'int' with spaces.
 *
 * Transform a long to a string with spaces, e.g.: 19939200 => "19 939 200".
 *
 * \param   integer   The integer to format.
 * \return            Formatted string.
 */
char *int_with_space(int integer);

/**
 * \brief Format a 'long' with spaces.
 *
 * Transform a long to a string with spaces, e.g.: 72036854775808 => "72 036 854 775 808".
 *
 * \param   integer   The integer to format.
 * \return            Formatted string.
 */
char * long_with_space(long integer);

/**
 * \brief Convert the string's lowercase characters to uppercase.
 *
 * \param   str   String to convert to lowercase.
 */
void convert_to_lower_case(char *str);

/**
 * \brief Convert the string's lowercase characters to uppercase.
 *
 * \param   str   String to convert to uppercase.
 */
void convert_to_upper_case(char *str);

/**
 * \brief Return a copy of the string with upper case characters converted to
 * lower case.
 *
 * \param   str   Any valid string.
 * \return        Lower-case deep copy of the string.
 */
char * get_lower_case(const char *str);

/**
 * \brief Return a copy of the string with lower case characters converted to
 * upper case.
 *
 * \param   str   Any valid string.
 * \return        Upper-case deep copy of the string.
 */
char * get_upper_case(const char *str);

#ifdef __cplusplus
}
#endif

#endif
