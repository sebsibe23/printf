#include "main.h"

/**
 * is_printable - Evaluates if the char is printable.
 * @ch_char: Char to be checked.
 * Return: 1 if the  ch_char is printable, 0 otherwise.
 */
int is_printable(char ch_char)
{
	if (ch_char >= 32 && ch_char < 127)
		return (1);

	return (0);
}

/**
 * append_hexa_code - Append ascci in the hexadecimal code to buffer.
 * @ch_buffer: Array of the chars.
 * @k: Index at which to start the appending.
 * @ascii_c_de: a ASSCI CODE.
 * Return: return  Always 3.
 */

int append_hexa_code(char ascii_c_de, char ch_buffer[], int k)
{
	char map_to[] = "0123456789ABCDEF";

	if (ascii_c_de < 0)
		ascii_c_de *= -1;

	ch_buffer[k++] = '\\';
	ch_buffer[k++] = 'x';

	ch_buffer[k++] = map_to[ascii_c_de / 16];
	ch_buffer[k] = map_to[ascii_c_de % 16];

	return (3);
}

/**
 * is_digit - Verifies if the char is a digit.
 * @ch_char: Char to be hcecked .
 *
 * Return: 1 if ch_char is a digit, 0 otherwise.
 */
int is_digit(char ch_char)
{
	if (ch_char >= '0' && ch_char <= '9')
		return (1);

	return (0);
}

/**
 * convert_size_number - Casts the number to the specified size.
 * @int_num: a Number to be casted.
 * @siz: Number indicating the type will  be casted.
 *
 * Return: Casted the value of int_num.
 */

long int convert_size_number(long int int_num, int siz)
{
	if (siz == M_S_LONG)
		return (int_num);
	else if (siz == M_S_SHORT)
		return ((short)int_num);

	return ((int)int_num);
}

/**
 * convert_size_unsgnd - Casts the  number to the specified size.
 * @int_num: a Number to be casted.
 * @siz: a Num indicating the type to be casted.
 *
 * Return: Casted the value of int_num.
 */
long int convert_size_unsgnd(unsigned long int int_num, int siz)
{
	if (siz == M_S_LONG)
		return (int_num);
	else if (siz == M_S_SHORT)
		return ((unsigned short)int_num);

	return ((unsigned int)int_num);
}
