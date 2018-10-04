
char *ft_strrchr(const char *str, int c)
{
    
    while (*str)
        str++;
    str--;
   	while (*str)
	{
		if ((char)c == *str)
			return ((char*)str);
		str--;
	}
	if ((char)c == *str)
		return ((char*)str);
	return (NULL); 
}
