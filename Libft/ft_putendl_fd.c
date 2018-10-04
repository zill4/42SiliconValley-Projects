
void ft_putendl_fd(char const *s, int fd)
{
    int i;

    i = 0;
    if(!*s)
        return;
    else
        while(s[i])
            ft_putchar_fd(s[i++], fd);
    ft_putchar('\n');
}