
char *ft_strjoin(char const *s1, char const *s2)
{
    char *nstr;
    int i;
    int size;
    size = 0;
    i = 0;
    while(s1[i])
        i++;
    size += i;
    i = 0;
    while(s2[i])
        i++;
    size += i;
    i = 0;
    nstr = (char*)malloc(sizeof(char *) * size + 1);
    while(s1[i])
        nstr[i] = s1[i++];
    size = i;
    i = 0;
    while(s2[i])
        nstr[i + size] = s2[i++];
    return (nstr);    
}
