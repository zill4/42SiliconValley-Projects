#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdarg.h>
# include "../libft/src/libft.h"


/* Flag Functions */

// Define some structure for keeping track of an arugments printable modifiers.
typedef struct  s_argu{
    // Left alignment modifier '-'
    int leftAlign;
    // Precision modifier '.'
    int precision;
    // mutliplicable modifier '*'
    int multiply;
    // signage modifier '+'
    int sign;
    // The multiple if multiply is true.
    long multiple;
    // int space size;
    int space_size;
    // container for modifiable print
    char *cont;
}               t_argu;

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
// get spacing given integer %2
char ft_space(char *str, int pos, t_argu arg);
// Get powers
int ft_getpow(int number);
// Get power of float
int ft_get_doublepow(float number);
// See for next step.
#endif