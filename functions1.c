#include "main.h"
/**
 * print_unsigned - Prints an unsigned num.
 * @val_types: List a of the  arguments.
 * @ch_buffer: buffer array to handle a print.
 * @int_flags:  Calculates the  active flags,.
 * @wth: get the width.
 * @prc: a Precision specification.
 * @siz: the size specifier.
 * Return: a Number of chars printed.
 */

int print_unsigned(va_list val_types, char ch_buffer[],
	int int_flags, int wth, int prc, int siz)
{
	int i = BU_SIZE - 2;
	unsigned long int num = va_arg(val_types, unsigned long int);

	num = convert_size_unsgnd(num, siz);

	if (num == 0)
		ch_buffer[i--] = '0';

	ch_buffer[BU_SIZE - 1] = '\0';

	while (num > 0)
	{
		ch_buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_unsgnd(0, i, ch_buffer, int_flags, wth, prc, siz));
}


/**
 * print_octal - Prints the unsigned number in octal notation.
 * @val_types: the Lista of arguments.
 * @ch_buffer: buffer array to handle a print.
 * @int_flags:  Calculates the active flags.
 * @wth: get a width.
 * @prc: the Precision specification.
 * @siz: a size specifier.
 * Return: a Number of chars printed.
 */
int print_octal(va_list val_types, char ch_buffer[],
	int int_flags, int wth, int prc, int siz)
{
	int i = BU_SIZE - 2;
	unsigned long int num = va_arg(val_types, unsigned long int);
	unsigned long int init_num = num;

	M_UNUSED(wth);

	num = convert_size_unsgnd(num, siz);

	if (num == 0)
		ch_buffer[i--] = '0';

	ch_buffer[BU_SIZE - 1] = '\0';

	while (num > 0)
	{
		ch_buffer[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (int_flags & M_F_HASH && init_num != 0)
		ch_buffer[i--] = '0';

	i++;

	return (write_unsgnd(0, i, ch_buffer, int_flags, wth, prc, siz));
}

/*
 * print_hexadecimal - Prints an unsigned number in a hexadecimal notation.
 * @val_types: the Lista of arguments.
 * @ch_buffer: buffer array to handle the  print.
 * @int_flags:  Calculates the active flags.
 * @wth: get the  width.
 * @prc: a Precision specification.
 * @siz: the size specifier.
 * Return: a Number of chars printed.
 */
int print_hexadecimal(va_list val_types, char ch_buffer[],
	int int_flags, int wth, int prc, int siz)
{
	return (print_hexa(val_types, "0123456789abcdef", ch_buffer,
		int_flags, 'x', wth, prc, siz));
}

/*
 *
 * print_hexa_upper - Prints an unsigned number the upper hexadecimal notation.
 * @val_types: Lista of the arguments.
 * @ch_buffer: a buffer  of char array to handle the  print.
 * @int_flags:  Calculates the active flags.
 * @wth: get the width
 * @prc: a Precision specification.
 * @siz: the size specifier.
 * Return: a Number of chars printed.
 */
int print_hexa_upper(va_list val_types, char ch_buffer[],
	int int_flags, int wth, int prc, int siz)
{
	return (print_hexa(val_types, "0123456789ABCDEF", ch_buffer,
		int_flags, 'X', wth, prc, siz));
}


/**
 * print_hexa - Prints a hexadecimal number in upper or lower.
 * @val_types: the Lista of arguments.
 * @ch_map_to: Array of values to map the number to
 * @ch_buffer: buffer of char  array to handle print.
 * @int_flags:  Calculates the  int flags.
 * @flag_ch: Calculates active char flags.
 * @wth: get the  width
 * @prc: a Precision specification
 * @siz: the size specifier.
 * Return: retur a Number of chars printed.
 */
int print_hexa(va_list val_types, char ch_map_to[], char ch_buffer[],
	int int_flags, char flag_ch, int wth, int prc, int siz)
{
	int i = BU_SIZE - 2;
	unsigned long int num = va_arg(val_types, unsigned long int);
	unsigned long int init_num = num;

	M_UNUSED(wth);

	num = convert_size_unsgnd(num, siz);

	if (num == 0)
		ch_buffer[i--] = '0';

	ch_buffer[BU_SIZE - 1] = '\0';

	while (num > 0)
	{
		ch_buffer[i--] = ch_map_to[num % 16];
		num /= 16;
	}

	if (int_flags & M_F_HASH && init_num != 0)
	{
		ch_buffer[i--] = flag_ch;
		ch_buffer[i--] = '0';
	}

	i++;

	return (write_unsgnd(0, i, ch_buffer, int_flags, wth, prc, siz));
}
