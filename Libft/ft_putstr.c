
void ft_putstr(char const *s)
{
    int i;

    i = 0;
    if(!*s)
        return;
    else
        while(s[i])
            ft_putchar(s[i++]);
        
}