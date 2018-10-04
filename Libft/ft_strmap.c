char *ft_strmap(char const *s, char (*f)(char))
{
        int i;
    char *nstr;
    i = 0;
    
    while(s[i])
        i++;
    nstr = ft_strnew(i);
    i = 0;
    while(s[i])
        nstr[i] = (*f)(s[i]);
    return (nstr);
}