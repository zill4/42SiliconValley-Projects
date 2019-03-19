#include "libft.h"

char    *ft_strrev(char *str)
{
    char    *p1;
    char    *p2;

    if (!str || !*str)
        return (str);
    p1 = str;
    p2 = str + ft_strlen(str) - 1;
    while (p2 > p1)
    {
        *p1 ^= *p2;
        *p2 ^= *p1;
        *p1 ^= *p2;
        ++p1;
        --p2;
    }
    return (str);
}