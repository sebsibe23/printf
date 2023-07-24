#include "main.h"
/**
 * handle_print - Prints an argument based on the type.
 * @ch_fmt: Formatted string in which to print a arguments.
 * @val_list: a List of arguments to be printed.
 * @int_d: int_d.
 * @ch_buffer: Buffer array of  to handle the  print.
 * @int_flags: Calculates a active flags.
 * @wth: get the width.
 * @prc: a Precision specification.
 * @siz: a Size specifier.
 * Return: 1 or 2 .
 */

int handle_print(const char *ch_fmt, int *int_d, va_list val_list,
	char ch_buffer[], int int_flags, int wth, int prc, int siz)
{
	int i, unknow_len = 0, printed_chars = -1;
	str_fmt_t fmt_types[] = {
		 {'c', print_char}, {'s', print_string}, {'%', print_percent},
		 {'i', print_int}, {'d', print_int}, {'b', print_binary},
		 {'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		 {'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		 {'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};
	for (i = 0; fmt_types[i].ch_fmt != '\0'; i++)
		if (ch_fmt[*int_d] == fmt_types[i].ch_fmt)
			return (fmt_types[i].int_fn(val_list, ch_buffer, int_flags, wth, prc, siz));

	if (fmt_types[i].ch_fmt == '\0')
	{
		if (ch_fmt[*int_d] == '\0')
			return (-1);
		unknow_len += write(1, "%%", 1);
		if (ch_fmt[*int_d - 1] == ' ')
			unknow_len += write(1, " ", 1);
		else if (wth)
		{
			--(*int_d);
			while (ch_fmt[*int_d] != ' ' && ch_fmt[*int_d] != '%')
				--(*int_d);
			if (ch_fmt[*int_d] == ' ')
				--(*int_d);
			return (1);
		}
		unknow_len += write(1, &ch_fmt[*int_d], 1);
		return (unknow_len);
	}
	return (printed_chars);
}
