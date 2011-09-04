#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "common.h"
#include "str.h"

char *get_opt_s(const char *arg)
{
	const int length = strlen(arg);
	int n = 0;
	while (n < length && arg[n] != '=')
	{
		++n;
	}
	if (arg[n] != '=')
	{
		return NULL;
	}

	const int ss_length = length - n; // - 1 ('=') + 1 ('\0')
	char *substring = (char*)malloc(ss_length);

	for (int i = 0; i < ss_length - 1; ++i)
	{
		substring[i] = arg[i + n + 1];
	}
	substring[ss_length - 1] = '\0';

	return substring;
}

int get_opt_i(const char *arg)
{
	char *str = get_opt_s(arg);
	const int number = atoi(str);
	free(str);
	return number;
}

double get_opt_d(const char *arg)
{
	char *str = get_opt_s(arg);
	const double number = atof(str);
	free(str);
	return number;
}

bool read_opt_i(const char *option, const char *argv[], int n, int *param)
{
	const int length = strlen(option);
	
	for (int i = 0; i < n; ++i)
	{
		int j = 0;
		const int inplen = strlen(argv[i]);
		while (j < length)
		{
			if (inplen < j + 1 || argv[i][j + 1] != option[j])
			{
				break;
			}
			else
			{
				++j;
			}
		}
		if (j == length && argv[i][length + 1] == '=')
		{
			*param = get_opt_i(argv[i]);
			return true;
		}
	}
	return false;
}

bool read_opt_d(const char *option, const char *argv[], int n, double *param)
{
	const int length = strlen(option);
	
	for (int i = 0; i < n; ++i)
	{
		int j = 0;
		const int inplen = strlen(argv[i]);
		while (j < length)
		{
			if (inplen < j + 1 || argv[i][j + 1] != option[j])
			{
				break;
			}
			else
			{
				++j;
			}
		}
		if (j == length && argv[i][length + 1] == '=')
		{
			*param = get_opt_d(argv[i]);
			return true;
		}
	}
	return false;
}

bool read_opt_s(const char *option, const char *argv[], int n, char *param)
{
	const int length = strlen(option);
	
	for (int i = 1; i < n; ++i)
	{
		int j = 0;
		const int inplen = strlen(argv[i]);
		while (j < length)
		{
			if (inplen < j + 1 || argv[i][j + 1] != option[j])
			{
				break;
			}
			else
			{
				++j;
			}
		}
		if (j == length && argv[i][length + 1] == '=')
		{
			sprintf(param, "%s", get_opt_s(argv[i]));
			return true;
		}
	}
	return false;
}

char *sec_to_string(long seconds)
{
	char *str = (char*)malloc(21);
  
	const long d = seconds / (60 * 60 * 24);
	const long h = seconds / (60 * 60) - (d * 24);
	const long m = seconds / 60 - (h * 60) - (d * 24 * 60);
	const long s = seconds % 60;

	if (d > 0)
	{
		sprintf(str, "%ld d %ld h %ld m %ld s", d, h, m, s);
	}
	else if (h > 0)
	{
		sprintf(str, "%ld h %ld m %ld s", h, m, s);
	}
	else if (m > 0)
	{
		sprintf(str, "%ld m %ld s", m, s);
	}
	else
	{
		sprintf(str, "%ld s", s);
	}
	return str;
}

char *int_with_space(int integer)
{
	char *str0 = (char*)malloc(11); // String without spaces
	sprintf(str0, "%d", integer);

	const int length0 = strlen(str0); // Size of the string without spaces
	const int length1 = length0 + (length0 - 1) / 3; // Size of the new string

	char *str1 = (char*)malloc(length1 + 1);
	str1[length1] = '\0';

	int next_space = (length0 % 3) == 0 ? 3 : (length0 % 3);

	int i0 = 0; // Index for the old string
	for (int i1 = 0; i1 < length1; ++i1)
	{
		if (i1 == next_space)
		{
			str1[i1] = UTILS_SEPARATOR;
			next_space += 4;
		}
		else
		{
			str1[i1] = str0[i0++];
		}
	}
	free(str0);
	return str1;
}

char *long_with_space(long integer)
{
	char *str0 = (char*)malloc(21); // String without spaces
	sprintf(str0, "%ld", integer);

	const int length0 = strlen(str0); // Size of the string without spaces
	const int length1 = length0 + (length0 - 1) / 3; // Size of the new string

	char *str1 = (char*)malloc(length1 + 1);
	str1[length1] = '\0';

	int next_space = (length0 % 3) == 0 ? 3 : (length0 % 3);

	int i0 = 0; // Index for the old string
	for (int i1 = 0; i1 < length1; ++i1)
	{
		if (i1 == next_space)
		{
			str1[i1] = UTILS_SEPARATOR;
			next_space += 4;
		}
		else
		{
			str1[i1] = str0[i0++];
		}
	}
	free(str0);
	return str1;
}

void convert_to_lower_case(char *str)
{
	const int length = strlen(str);

	for (int i = 0; i < length; ++i)
	{
		if (str[i] >= 0x41 && str[i] <= 0x5A)
		{
			str[i] += 0x20;
		}
	}
}

void convert_to_upper_case(char *str)
{
	const int length = strlen(str);

	for (int i = 0; i < length; ++i)
	{
		if (str[i] >= 0x61 && str[i] <= 0x7A)
		{
			str[i] -= 0x20;
		}
	}
}

char *get_lower_case(const char *str)
{
	const int length = strlen(str);
	char *new_str = (char*)malloc(length + 1);

	for (int i = 0; i < length; ++i)
	{
		if (str[i] >= 0x41 && str[i] <= 0x5A)
		{
			new_str[i] = str[i] + 0x20;
		}
		else
		{
			new_str[i] = str[i];
		}
	}
	new_str[length] = '\0';
	return new_str;
}

char *get_upper_case(const char *str)
{
	const int length = strlen(str);
	char *new_str = (char*)malloc(length + 1);

	for (int i = 0; i < length; ++i)
	{
		if (str[i] >= 0x61 && str[i] <= 0x7A)
		{
			new_str[i] = str[i] - 0x20;
		}
		else
		{
			new_str[i] = str[i];
		}
	}
	new_str[length] = '\0';
	return new_str;
}
