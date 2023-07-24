#include "main.h"

/**
 * get_size - Determines the size to cast an argument.
 * @ch_format: Formatted string where to print arguments.
 * @int_d: Arguments to be printed list.
 *
 * Return: Precision.
 */

int get_size(const char *ch_format, int *int_d)
{
	int curr_i = *int_d + 1;
	int size = 0;

	if (ch_format[curr_i] == 'l')
		size = M_S_LONG;
	else if (ch_format[curr_i] == 'h')
		size = M_S_SHORT;

	if (size == 0)
		*int_d = curr_i - 1;
	else
		*int_d = curr_i;

	return (size);
}
