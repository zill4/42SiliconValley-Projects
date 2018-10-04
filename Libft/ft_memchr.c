
#include "libft.h"

void *ft_memchr(const void *s, int c, size_t n)
{
    int i;
    
    i = 0;
    while(i++ < n)
    {
         if (*(char *)s == (unsigned char) c)
            return((void *)s);
        s++;
    }
    return (NULL);
}
