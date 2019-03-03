#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdarg.h>

void pf_atoib(long value, int base, int *count);
void pf_putnbr(long d, int *count);
void pf_putstr(char* s, int *count);
void pf_putchar(char c, int *count);

#endif