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
    // Must keep track of our bit after being shifted to tell which have been flagged.
    int flags;
    // Keeps track of precision of a given string.
    int precision;
    // same as precision but for white space / and zeroing.
    int width;
}               t_argu;

// Macro function for shifting x one bit to the left.
# define FT_BIT (x) (1 << (x))
// The specifiers for printf
# define SPECIFIERS "spdiouxXc"
# define SPECI_SIZE (ft_strlen(SPECIFIERS))

// Endcoding the SPECIFIERS as a macro for shifting easier...
# define S (0)
# define P (1)
# define D (2)
# define I (3)
# define O (4)
# define U (5)
# define LOWER_X (6)
# define UPPER_X (7)
# define C (8)
// Encoding for the attributes of printf
# define HASH       (FT_BIT(0))
# define ZERO       (FT_BIT(1))
# define MINUS      (FT_BIT(2))
# define PLUS       (FT_BIT(3))
# define SPACE      (FT_BIT(4))
# define S_BIT      (FT_BIT(5))
# define P_BIT      (FT_BIT(6))
# define D_BIT      (FT_BIT(7))
# define I_BIT      (FT_BIT(8))
# define O_BIT      (FT_BIT(9))
# define U_BIT      (FT_BIT(10))
# define LOW_X_BIT  (FT_BIT(11))
# define UPP_X_BIT  (FT_BIT(12))
# define HH         (FT_BIT(13))
# define H          (FT_BIT(14))
# define LL         (FT_BIT(15))
# define L          (FT_BIT(16))
# define J          (FT_BIT(17))
# define Z          (FT_BIT(18))
# define WIDTH      (FT_BIT(19))
# define PRECISION  (FT_BIT(20))
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