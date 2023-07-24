#include "main.h"
/**
 * print_char - Prints the char.
 * @val_types: List a of the  arguments.
 * @ch_buffer: Buffer array to handle print.
 * @int_int_flags:  Calculates the  active int_flags.
 * @wth: Width value.
 * @prc: the Precision specification.
 * @siz: the Size specifier.
 * Return: the Number of chars printed.
 */
int print_char(va_list val_types, char ch_buffer[],
	int int_int_flags, int wth, int prc, int siz)
{
	char c = va_arg(val_types, int);

	return (handle_write_char(c, ch_buffer, int_int_flags, wth, prc, siz));
}
/************************* PRINT A STRING *************************/
/**
 * print_string - Prints the string.
 * @val_types: the List a of arguments.
 * @ch_buffer: Buffer array to handle the print.
 * @int_flags:  Calculates the active int_flags.
 * @wth: get the width.
 * @prc: the Precision specification.
 * @siz: the Size specifier.
 * Return: the Number of chars printed.
 */
int print_string(va_list val_types, char ch_buffer[],
	int int_flags, int wth, int prc, int siz)
{
	int length = 0, i;
	char *str = va_arg(val_types, char *);

	M_UNUSED(ch_buffer);
	M_UNUSED(int_flags);
	M_UNUSED(wth);
	M_UNUSED(prc);
	M_UNUSED(siz);
	if (str == NULL)
	{
		str = "(null)";
		if (prc >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (prc >= 0 && prc < length)
		length = prc;

	if (wth > length)
	{
		if (int_flags & M_F_MINUS)
		{
			write(1, &str[0], length);
			for (i = wth - length; i > 0; i--)
				write(1, " ", 1);
			return (wth);
		}
		else
		{
			for (i = wth - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (wth);
		}
	}

	return (write(1, str, length));
}
/************************* PRINT PERCENT SIGN *************************/
/**
 * print_percent - Prints the  percent sign.
 * @val_types: Lista of the arguments.
 * @ch_buffer: Buffer array to handle the print.
 * @int_flags:  Calculates active the  int_flags.
 * @wth: get a width.
 * @prc: a Precision specification.
 * @siz: a Size specifier.
 * Return: Number of chars printed.
 */
int print_percent(va_list val_types, char ch_buffer[],
	int int_flags, int wth, int prc, int siz)
{
	M_UNUSED(val_types);
	M_UNUSED(ch_buffer);
	M_UNUSED(int_flags);
	M_UNUSED(wth);
	M_UNUSED(prc);
	M_UNUSED(siz);
	return (write(1, "%%", 1));
}

/************************* PRINT INT *************************/
/**
 * print_int - Print the int.
 * @val_types: Lista of a arguments.
 * @ch_buffer: Buffer array to handle a print.
 * @int_flags:  Calculates the  active int_flags.
 * @wth: get a width.
 * @prc: the Precision specification.
 * @siz: a Size specifier.
 * Return: a Number of chars printed
 */
int print_int(va_list val_types, char ch_buffer[],
	int int_flags, int wth, int prc, int siz)
{
	int i = BU_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(val_types, long int);
	unsigned long int num;

	n = convert_size_number(n, siz);

	if (n == 0)
		ch_buffer[i--] = '0';

	ch_buffer[BU_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		ch_buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_number(is_negative, i, ch_buffer, int_flags, wth, prc, siz));
}

/************************* PRINT BINARY *************************/
/**
 * print_binary - Prints an unsigned num.
 * @val_types: the Lista of arguments.
 * @ch_buffer: Buffer the  array to handle a print.
 * @int_flags:  Calculates the  active int_flags.
 * @wth: get the  width.
 * @prc: the Precision specification
 * @siz: the Size specifier
 * Return: a Numbers of char printed.
 */
int print_binary(va_list val_types, char ch_buffer[],
	int int_flags, int wth, int prc, int siz)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int count;

	M_UNUSED(ch_buffer);
	M_UNUSED(int_flags);
	M_UNUSED(wth);
	M_UNUSED(prc);
	M_UNUSED(siz);

	n = va_arg(val_types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
