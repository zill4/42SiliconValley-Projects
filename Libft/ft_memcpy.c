void *ft_memcpy(void *restrict dst, const void* restrict src, size_t n)
{
    int i;

    i  = 0;
    while( i++ < n)
    {
        *(char *)dst++ = *(char *)src++;
    }
    return (dst);
}      
