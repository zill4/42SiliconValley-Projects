#include "libft.h"

void    ft_putunbr(uintmax_t n)
{
    char c;

    if (n < 10)
        ft_putchar(c + '0');
    else
    {
        ft_putunbr(n / 10);
        ft_putunbr(n % 10);
    }
}