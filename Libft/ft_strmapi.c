char *ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
            int i;
    char *nstr;
    i = 0;
    
    while(s[i])
        i++;
    nstr = ft_strnew(i);
    i = 0;
    while(s[i])
        nstr[i] = (*f)(i,s[i]);
    return (nstr);
}
