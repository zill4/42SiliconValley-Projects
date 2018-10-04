/* May be incorrect */
char *ft_strnew(size_t size)
{
    char* str;
    int i;
    
    i = 0;
    str = (char* )ft_memalloc(size);
    if (*str == NULL)
        return(NULL);
    else
        while(str[i])
            str[i++] = '\0';
    return(str);
}