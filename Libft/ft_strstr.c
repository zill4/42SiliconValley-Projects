char *ft_strstr(const char *haystack, const char *needle)
{
    int j;
    int c;
    int found;

    found = 0;
    j = 0;
    c = 0;
    while(*haystack)
    {
        if(*haystack == needle[j])
            j++;
        else
            j = 0;
        haystack++;
    }
    return((char*)haystack - j);
}