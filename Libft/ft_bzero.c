#include <libft.h>

void ft_bzero(void *s, size_t n)
{
    size_t i;
    char *c;

    if (!n)
        return ;

    c = (char *)s;
    i = 0;
    while(i++ < n)
        *(c + i) = 0;
}