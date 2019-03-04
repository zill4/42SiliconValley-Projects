#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdarg.h>
# include "../libft/src/libft.h"


/* Flag Functions */

// d - Print Decimal, i - Print Integer
void pf_putnbr(long d, int *count);
// s - Print String
void pf_putstr(char* s, int *count);
// c - Print character
void pf_putchar(char c, int *count);
// p - base 16 (pointer), o - base 8, u - base 10 (unsigned), x - base 16 
void pf_atoib(long value, int base, int *count);
// x - base 16 (Caps
void pf_atoib_cap(long value, int base, int *count);
// f - print floating point, double
void pf_putdoub(long long d, int *count);
// l - print long modifier - L - print long double.
void pf_modlong(long l, int *count);
// ll - print long long modifier
void pf_modlonglong(long long ll, int *count);
// h - print short modifier
void pf_modshort(short s, int *count);
// hh - print char modifier
void pf_modshortshort(char i, int* count);
// 0123456789.0123456789(-) - precision modifiers
void pf_precmod(long long min, long long max, int* count);
// * - allignment modifier
void pf_multmod(long long num, int *count);
// +(space) - sign modifiers
void pf_signmod(char s, int* count);
// # - alternate modifier
void pf_altmod(char a, int* count);
// 0 - zero pad?
void pf_zeropadmod(char z, int* count);
// Pointer function 
void (* const pf[])(char, int*) = {pf_putchar};
//assumed to match "cspdioufxXlhL0123456789.*#0-+ "
// See for next step.
#endif