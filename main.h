#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>


/**
 * struct str_fmt - Struct op
 *
 * @ch_fmt: The format.
 * @int_fn: The function associated.
 */
struct str_fmt
{
	char ch_fmt;
	int (*int_fn)(va_list, char[], int, int, int, int);
};


/**
 * typedef struct str_fmt str_fmt_t - Struct op
 *
 * @ch_fmt: The format.
 * @str_fm_t: The function associated.
 */
typedef struct str_fmt str_fmt_t;

int _printf(const char *ch_format, ...);
int handle_print(const char *ch_fmt, int *int_d,
va_list val_list, char ch_buffer[], int int_flags, int wth, int prc, int siz);

#define M_UNUSED(x) (void)(x)
#define BU_SIZE 1024
#define M_F_MINUS 1
#define M_F_PLUS 2
#define M_F_ZERO 4
#define M_F_HASH 8
#define M_F_SPACE 16

#define M_S_LONG 2
#define M_S_SHORT 1
int print_char(va_list val_types, char ch_buffer[],
	int int_flags, int wth, int prc, int siz);
int print_string(va_list val_types, char ch_buffer[],
	int int_flags, int wth, int prc, int siz);
int print_percent(va_list val_types, char ch_buffer[],
	int int_flags, int wth, int prc, int siz);

int print_int(va_list val_types, char ch_buffer[],
	int int_flags, int wth, int prc, int siz);
int print_binary(va_list val_types, char ch_buffer[],
	int int_flags, int wth, int prc, int siz);
int print_unsigned(va_list val_types, char ch_buffer[],
	int int_flags, int wth, int prc, int siz);
int print_octal(va_list val_types, char ch_buffer[],
	int int_flags, int wth, int prc, int siz);
int print_hexadecimal(va_list val_types, char ch_buffer[],
	int int_flags, int wth, int prc, int siz);
int print_hexa_upper(va_list val_types, char ch_buffer[],
	int int_flags, int wth, int prc, int siz);

int print_hexa(va_list val_types, char ch_map_to[],
char ch_buffer[], int int_flags, char ch_flag_ch, int wth, int prc, int siz);


int print_non_printable(va_list val_types, char ch_buffer[],
	int int_flags, int wth, int prc, int siz);

int print_pointer(va_list val_types, char ch_buffer[],
	int int_flags, int wth, int prc, int siz);
int get_flags(const char *ch_format, int *int_d);
int get_width(const char *ch_format, int *int_d, va_list val_list);
int get_precision(const char *ch_format, int *int_d, va_list val_list);
int get_size(const char *ch_format, int *int_d);
int print_reverse(va_list val_types, char ch_buffer[],
	int int_flags, int wth, int prc, int siz);
int print_rot13string(va_list val_types, char ch_buffer[],
	int int_flags, int wth, int prc, int siz);
int handle_write_char(char ch_c, char ch_buffer[],
	int int_flags, int wth, int prc, int siz);
int write_number(int int_is_positive, int int_ind, char ch_buffer[],
	int int_flags, int wth, int prc, int siz);
int write_num(int int_ind, char ch_bff[], int int_flags, int wth, int prc,
	int length, char ch_padd, char ch_extra_c);
int write_pointer(char ch_buffer[], int int_ind, int int_length,
	int wth, int int_flags, char ch_padd, char ch_extra_c, int int_padd_start);

int write_unsgnd(int int_is_negative, int int_ind,
char ch_buffer[],
	int int_flags, int wth, int prc, int siz);
int is_printable(char);
int append_hexa_code(char, char[], int);
int is_digit(char);

long int convert_size_number(long int int_num, int siz);
long int convert_size_unsgnd(unsigned long int int_num, int siz);

#endif /* MAIN_H */
