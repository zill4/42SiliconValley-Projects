int ft_memcmp (const void *s1, const void *s2, size_t n)
{
    int i;

	i = 0;
	while (i++ < n && *(char *)s1++ == *(char *)s2++);
    
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}