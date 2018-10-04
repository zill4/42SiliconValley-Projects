char *ft_strncat(char *restrict s1, const char *restrict s2, size_t n)
{
    int i;
    int k;
    k = 0;
    i = 0;
    while(s1[i])
        i++;
    while(s2[k] && k < n)
        s1[i++] = s2[k++];
    s1[i] = '\0';
    return(s1);
}