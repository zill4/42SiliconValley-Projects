#include "libft.h"

void    ft_putunbr(uintmax_t n)
{
    char c;

    c = '0';
    if (n < 10)
        ft_putchar(c + n);
    else
    {
        ft_putunbr(n / 10);
        ft_putunbr(n % 10);
    }
}