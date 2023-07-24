#include "main.h"
void print_buffer(char buffer[], int *buff_ind);
/**
 * _printf - Printf function
 * @ch_format: format.
 * Return: Printed chars.
 */
int _printf(const char *ch_format, ...)
{
	int int_d, printed = 0, printed_chars = 0;
	int int_flags, wth, prc, siz, buff_ind = 0;
	va_list val_list;
	char buffer[BU_SIZE];

	if (ch_format == NULL)
		return (-1);

	va_start(val_list, ch_format);

	for (int_d = 0; ch_format && ch_format[int_d] != '\0'; int_d++)
	{
		if (ch_format[int_d] != '%')
		{
			buffer[buff_ind++] = ch_format[int_d];
			if (buff_ind == BU_SIZE)
				print_buffer(buffer, &buff_ind);
			printed_chars++;
		
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			int_flags = get_flags(ch_format, &int_d);
			wth = get_width(ch_format, &int_d, val_list);
			prc = get_precision(ch_format, &int_d, val_list);
			siz = get_size(ch_format, &int_d);
			++int_d;
			printed = handle_print(ch_format, &int_d, val_list, buffer,
				int_flags, wth, prc, siz);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}

	print_buffer(buffer, &buff_ind);

	va_end(val_list);

	return (printed_chars);
}

/**
 * print_buffer - Prints the contents of the buffer if it exist.
 * @buffer: Array of chars.
 * @buff_ind: Index at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}

