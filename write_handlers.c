#include "main.h"
/**
 * handle_write_char - Prints the string.
 * @ch_c: a char types.
 * @ch_buffer: Buffer char array to handle print.
 * @int_flags:  Calculates the active flags.
 * @wth: get the width.
 * @prc: a precision specifier.
 * @siz: a Size specifier.
 * Return: a Number of chars printed.
 */
int handle_write_char(char ch_c, char ch_buffer[],
	int int_flags, int wth, int prc, int siz)
{
	int i = 0;
	char padd = ' ';

	M_UNUSED(prc);
	M_UNUSED(siz);

	if (int_flags & M_F_ZERO)
		padd = '0';

	ch_buffer[i++] = ch_c;
	ch_buffer[i] = '\0';

	if (wth > 1)
	{
		ch_buffer[BU_SIZE - 1] = '\0';
		for (i = 0; i < wth - 1; i++)
			ch_buffer[BU_SIZE - i - 2] = padd;

		if (int_flags & M_F_MINUS)
			return (write(1, &ch_buffer[0], 1) +
					write(1, &ch_buffer[BU_SIZE - i - 1], wth - 1));
		else
			return (write(1, &ch_buffer[BU_SIZE - i - 1], wth - 1) +
					write(1, &ch_buffer[0], 1));
	}

	return (write(1, &ch_buffer[0], 1));
}


/**
 * write_number - Prints the string.
 * @int_is_positive: a Lista of arguments.
 * @int_ind: a char types.
 * @ch_buffer: a Buffer array to handle print
 * @int_flags:  Calculates the active flags.
 * @wth: get the width.
 * @prc: a precision specifier.
 * @siz: Size specifier.
 * Return: a Number of chars printed.
 */
int write_number(int int_is_positive, int int_ind, char ch_buffer[],
	int int_flags, int wth, int prc, int siz)
{
	int len_th = BU_SIZE - int_ind - 1;
	char padd = ' ', extra_ch = 0;

	M_UNUSED(siz);

	if ((int_flags & M_F_ZERO) && !(int_flags & M_F_MINUS))
		padd = '0';
	if (int_is_positive)
		extra_ch = '-';
	else if (int_flags & M_F_PLUS)
		extra_ch = '+';
	else if (int_flags & M_F_SPACE)
		extra_ch = ' ';

	return (write_num(int_ind, ch_buffer, int_flags, wth, prc,
		len_th, padd, extra_ch));
}

/**
 * write_num - Write the number using a bufffer.
 * @int_ind: Index at which the number starts on the buffer.
 * @ch_bff: Buffer of char.
 * @int_flags: the int Flags.
 * @wth:  a width.
 * @prec: a Precision specifier.
 * @length: a Number length.
 * @ch_padd: a Pading char.
 * @ch_extra_c: the Extra char.
 * Return: the Number of printed chars.
 */
int write_num(int int_ind, char ch_bff[], int int_flags, int wth, int prec,
		int length, char ch_padd, char ch_extra_c)
{
	int i, padd_start = 1;

	if (prec == 0 && int_ind == BU_SIZE - 2 && ch_bff[int_ind] == '0' && wth == 0)
		return (0);
	if (prec == 0 && int_ind == BU_SIZE - 2 && ch_bff[int_ind] == '0')
		ch_bff[int_ind] = ch_padd = ' ';
	if (prec > 0 && prec < length)
		ch_padd = ' ';
	while (prec > length)
		ch_bff[--int_ind] = '0', length++;
	if (ch_extra_c != 0)
		length++;
	if (wth > length)
	{
		for (i = 1; i < wth - length + 1; i++)
			ch_bff[i] = ch_padd;
		ch_bff[i] = '\0';
		if (int_flags & M_F_MINUS && ch_padd == ' ')
		{
			if (ch_extra_c)
				ch_bff[--int_ind] = ch_extra_c;
			return (write(1, &ch_bff[int_ind], length) + write(1, &ch_bff[1], i - 1));
		}
		else if (!(int_flags & M_F_MINUS) && ch_padd == ' ')
		{
			if (ch_extra_c)
				ch_bff[--int_ind] = ch_extra_c;
			return (write(1, &ch_bff[1], i - 1) + write(1, &ch_bff[int_ind], length));
		}
		else if (!(int_flags & M_F_MINUS) && ch_padd == '0')
		{
			if (ch_extra_c)
				ch_bff[--padd_start] = ch_extra_c;
			return (write(1, &ch_bff[padd_start], i - padd_start) +
				write(1, &ch_bff[int_ind], length - (1 - padd_start)));
		}
	}
	if (ch_extra_c)
		ch_bff[--int_ind] = ch_extra_c;
	return (write(1, &ch_bff[int_ind], length));
}

/**
 * write_unsgnd - Writes the  unsigned number.
 * @int_is_negative: the Number indicating if the num is negative.
 * @int_ind: Index at which the number starts in a buffer.
 * @ch_buffer: Array of a chars.
 * @int_flags: a Flags specifiers
 * @wth: a Width specifier
 * @prc: a Precision specifier
 * @siz: a Size specifier
 * Return: a Number of written chars.
 */
int write_unsgnd(int int_is_negative, int int_ind,
	char ch_buffer[],
	int int_flags, int wth, int prc, int siz)
{
	int length = BU_SIZE - int_ind - 1, i = 0;
	char padd = ' ';

	M_UNUSED(int_is_negative);
	M_UNUSED(siz);

	if (prc == 0 && int_ind == BU_SIZE - 2 && ch_buffer[int_ind] == '0')
		return (0);

	if (prc > 0 && prc < length)
		padd = ' ';

	while (prc > length)
	{
		ch_buffer[--int_ind] = '0';
		length++;
	}

	if ((int_flags & M_F_ZERO) && !(int_flags & M_F_MINUS))
		padd = '0';

	if (wth > length)
	{
		for (i = 0; i < wth - length; i++)
			ch_buffer[i] = padd;

		ch_buffer[i] = '\0';
		if (int_flags & M_F_MINUS)
		{
			return (write(1, &ch_buffer[int_ind], length) + write(1, &ch_buffer[0], i));
		}
		else
		{
			return (write(1, &ch_buffer[0], i) + write(1, &ch_buffer[int_ind], length));
		}
	}

	return (write(1, &ch_buffer[int_ind], length));
}

/**
 * write_pointer - Write the memory address.
 * @ch_buffer: buffer of char Arrays of chars
 * @int_ind: Index at which the number starts in the buffer.
 * @int_length: a Length of number.
 * @wth: a Width specifier.
 * @int_flags: a Flags specifier.
 * @ch_padd: a Char representing the padding.
 * @ch_extra_c: the Char representing extra char.
 * @int_padd_start: the Index at which padding should start.
 * Return: a Number of the  written chars.
 */
int write_pointer(char ch_buffer[], int int_ind, int int_length,
	int wth, int int_flags, char ch_padd, char ch_extra_c, int int_padd_start)
{
	int i;

	if (wth > int_length)
	{
		for (i = 3; i < wth - int_length + 3; i++)
			ch_buffer[i] = ch_padd;
		ch_buffer[i] = '\0';
		if (int_flags & M_F_MINUS && ch_padd == ' ')
		{
			ch_buffer[--int_ind] = 'x';
			ch_buffer[--int_ind] = '0';
			if (ch_extra_c)
				ch_buffer[--int_ind] = ch_extra_c;
			return (write(1, &ch_buffer[int_ind], int_length) +
					write(1, &ch_buffer[3], i - 3));
		}
		else if (!(int_flags & M_F_MINUS) && ch_padd == ' ')
		{
			ch_buffer[--int_ind] = 'x';
			ch_buffer[--int_ind] = '0';
			if (ch_extra_c)
				ch_buffer[--int_ind] = ch_extra_c;
			return (write(1, &ch_buffer[3], i - 3) +
					write(1, &ch_buffer[int_ind], int_length));
		}
		else if (!(int_flags & M_F_MINUS) && ch_padd == '0')
		{
			if (ch_extra_c)
				ch_buffer[--int_padd_start] = ch_extra_c;
			ch_buffer[1] = '0';
			ch_buffer[2] = 'x';
			return (write(1, &ch_buffer[int_padd_start], i - int_padd_start) +
				write(1, &ch_buffer[int_ind], int_length - (1 - int_padd_start) - 2));
		}
	}
	ch_buffer[--int_ind] = 'x';
	ch_buffer[--int_ind] = '0';
	if (ch_extra_c)
		ch_buffer[--int_ind] = ch_extra_c;
	return (write(1, &ch_buffer[int_ind], BU_SIZE - int_ind - 1));
}
