#include "main.h"
/**
 * print_pointer - Prints the value of a pointer variables.
 * @val_types: List of  arguments.
 * @ch_buffer: char Buffer array to handle the  print.
 * @int_flags:  Calculates the active int_flags.
 * @wth: get the width.
 * @prc: a Precision specification
 * @siz: the Size of  specifier.
 * Return: Number of the chars printed.
 */
int print_pointer(va_list val_types, char ch_buffer[],
	int int_flags, int wth, int prc, int siz)
{
	char ext_c = 0, padd = ' ';
	int ind = BU_SIZE - 2, len = 2, padd_start = 1; /* len=2, for '0x' */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(val_types, void *);

	M_UNUSED(wth);
	M_UNUSED(siz);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	ch_buffer[BU_SIZE - 1] = '\0';
	M_UNUSED(prc);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		ch_buffer[ind--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		len++;
	}

	if ((int_flags & M_F_ZERO) && !(int_flags & M_F_MINUS))
		padd = '0';
	if (int_flags & M_F_PLUS)
		ext_c = '+', len++;
	else if (int_flags & M_F_SPACE)
		ext_c = ' ', len++;

	ind++;

	return (write_pointer(ch_buffer, ind, len,
		wth, int_flags, padd, ext_c, padd_start));
}

/**
 * print_non_printable - Prints ascii codes in hexa.
 * @val_types: the Lista of arguments.
 * @ch_buffer: the Buffer array to handle print.
 * @int_flags:  Calculates the  active int_flags.
 * @wth: get the  width.
 * @prc: a Precision specification.
 * @siz: Size specifier.
 * Return: a Number of chars printed.
 */
int print_non_printable(va_list val_types, char ch_buffer[],
	int int_flags, int wth, int prc, int siz)
{
	int i = 0, offset = 0;
	char *str = va_arg(val_types, char *);

	M_UNUSED(int_flags);
	M_UNUSED(wth);
	M_UNUSED(prc);
	M_UNUSED(siz);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[i] != '\0')
	{
		if (is_printable(str[i]))
			ch_buffer[i + offset] = str[i];
		else
			offset += append_hexa_code(str[i], ch_buffer, i + offset);

		i++;
	}

	ch_buffer[i + offset] = '\0';

	return (write(1, ch_buffer, i + offset));
}


/**
 * print_reverse - Prints the reverse string.
 * @val_types: a Lista of arguments.
 * @ch_buffer: a Buffer array to handle the  print.
 * @int_flags:  Calculates the active int_flags.
 * @wth: get the  width.
 * @prc: the Precision specification
 * @siz: the Size specifier.
 * Return: the Numbers of chars printed.
 */

int print_reverse(va_list val_types, char ch_buffer[],
	int int_flags, int wth, int prc, int siz)
{
	char *str;
	int i, count = 0;

	M_UNUSED(ch_buffer);
	M_UNUSED(int_flags);
	M_UNUSED(wth);
	M_UNUSED(siz);

	str = va_arg(val_types, char *);

	if (str == NULL)
	{
		M_UNUSED(prc);

		str = ")Null(";
	}
	for (i = 0; str[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char z = str[i];

		write(1, &z, 1);
		count++;
	}
	return (count);
}

/**
 * print_rot13string - Print a string in the rot13.
 * @val_types: Lista of the  arguments.
 * @ch_buffer: Buffer array to handle the  print.
 * @int_flags:  Calculates the active flags.
 * @wth: get the  width.
 * @prc: a Precision specification
 * @siz: the Size specifier.
 * Return: a Numbers of chars printed.
 */
int print_rot13string(va_list val_types, char ch_buffer[],
	int int_flags, int wth, int prc, int siz)
{
	char x;
	char *str;
	unsigned int i, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(val_types, char *);
	M_UNUSED(ch_buffer);
	M_UNUSED(int_flags);
	M_UNUSED(wth);
	M_UNUSED(prc);
	M_UNUSED(siz);

	if (str == NULL)
		str = "(AHYY)";
	for (i = 0; str[i]; i++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[i])
			{
				x = out[j];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!in[j])
		{
			x = str[i];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}
