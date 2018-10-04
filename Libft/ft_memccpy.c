#include "libft.h"

void *ft_memccpy(void *restrict dst, const void* restrict src, int c, size_t n)
{
    size_t i;
    char *c;

    c = (char*)dst;
    i = 0;
    while ( i++ < n )
    {
        if (*(char *)src == (unsigned char) c)
        break;

        *(char *)(c + i) = *(unsigned char *)(src + i);
    }
    return (dst + i);
}