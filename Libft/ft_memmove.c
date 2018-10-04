
void *ft_memmove(void *dst, const void *src, size_t len)
{
    int i;
    
    i = 0;
    
    while (i++ < len)
    {
        *(char *)dst++ = *(char *)src++;
    }
    return (dst);
}