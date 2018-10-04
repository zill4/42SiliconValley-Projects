int ft_strequ(char *s1, char const *s2)
{
    int i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
    
	return (((unsigned char)s1[i] - (unsigned char)s2[i]) == 0 );
}
