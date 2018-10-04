

int ft_strnequ(char const *s1, char const *s2, size_t n)
{
    int i;

	i = 0;
	while (s1[i] && s1[i] == s2[i] && --n > 0)
		i++;
    
    return (((unsigned char)s1[i] - (unsigned char)s2[i]) == 0 );
}