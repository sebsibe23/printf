#include "main.h"

/**
 * get_width - Determines the printing width.
 * @ch_format: Formatted string into which the arguments will be printed.
 * @int_d: Arguments to be printed list.
 * @val_list: Arguments list.
 *
 * Return: width.
 */

int get_width(const char *ch_format, int *int_d, va_list val_list)
{
	int curr_i;
	int width = 0;

	for (curr_i = *int_d + 1; ch_format[curr_i] != '\0'; curr_i++)
	{
		if (is_digit(ch_format[curr_i]))
		{
			width *= 10;
			width += ch_format[curr_i] - '0';
		}
		else if (ch_format[curr_i] == '*')
		{
			curr_i++;
			width = va_arg(val_list, int);
			break;
		}
		else
			break;
	}

	*int_d = curr_i - 1;

	return (width);
}
