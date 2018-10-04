

char *ft_strnstr(const char *haystack, const char *needle, size_t len)
{
        int j;
    int c;
    int found;

    found = 0;
    j = 0;
    c = 0;
    while(*haystack && len > 0)
    {
        if(*haystack == needle[j])
            j++;
        else
            j = 0;
        haystack++;
        len--;
    }
    return((char*)haystack - j);
}
