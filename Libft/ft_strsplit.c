char **ft_strsplit(char const *s, char c)
{
    char **splits;
    int size_arr;
    int size_str;
    int i;

    i = 0;
    size_arr = 0;
    size_str = 0;
    while(s[i])
        i++;
    splits = (char**)malloc(sizeof(char**)* i);
    i = 0;
    while(s[i])
    {
        if (s[i] != c)
        {
            size_str++;
        }
        else if (size_str > 0)
        {
            splits[size_arr++] = (char *)malloc(sizeof(char*)*size_str+1);
            size_str = 0;
        }
        i++;
    }
    size_str = 0;
    size_arr = 0;
    i = 0;
    while (s[i])
    {
        if(s[i] != c)
        {
            splits[size_arr][size_str++] = s[i];
        }
        else if (size_str > 0)
        {
            splits[size_arr][size_str] = '\0';
            size_str = 0;
            size_arr++;
        }
        i++;
    }

}