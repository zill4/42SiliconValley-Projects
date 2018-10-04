
char *ft_strsub(char const *s, unsigned int start, size_t len)
{
    char *nstr;
    int i;

    i = 0;
    nstr = (char*)malloc(sizeof(char*)* len + 1);

    while(s[start + i] && i < len)
    {
        nstr[i] = s[start + i++];
    }
    return(nstr);
}