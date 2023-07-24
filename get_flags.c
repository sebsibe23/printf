#include "main.h"
/**
 * get_flags - Determines the active flags.
 * @ch_format: Formatted string into where the arguments will be printed.
 * @int_d: Take the parameter
 * Return: Flags:
 */

int get_flags(const char *ch_format, int *int_d)
{
	int j, curr_i;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FA[] = {M_F_MINUS, M_F_PLUS, M_F_ZERO, M_F_HASH, M_F_SPACE, 0};

	for (curr_i = *int_d + 1; ch_format[curr_i] != '\0'; curr_i++)
	{
		for (j = 0; FLAGS_CH[j] != '\0'; j++)
			if (ch_format[curr_i] == FLAGS_CH[j])
			{
				flags |= FA[j];
				break;
			}

		if (FLAGS_CH[j] == 0)
			break;
	}

	*int_d = curr_i - 1;

	return (flags);
}
