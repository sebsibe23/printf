#include "main.h"

/**
 * get_precision - Determines the printing precision.
 * @ch_format: Formatted string where print arguments.
 * @int_d: Arguments to be printed in a list.
 * @val_list: List of arguments.
 *
 * Return: Precision.
 */
int get_precision(const char *ch_format, int *int_d, va_list val_list)
{
	int curr_i = *int_d + 1;
	int precision = -1;

	if (ch_format[curr_i] != '.')
		return (precision);

	precision = 0;

	for (curr_i += 1; ch_format[curr_i] != '\0'; curr_i++)
	{
		if (is_digit(ch_format[curr_i]))
		{
			precision *= 10;
			precision += ch_format[curr_i] - '0';
		}
		else if (ch_format[curr_i] == '*')
		{
			curr_i++;
			precision = va_arg(val_list, int);
			break;
		}
		else
			break;
	}

	*int_d = curr_i - 1;

	return (precision);
}
