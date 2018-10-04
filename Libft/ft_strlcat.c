size_t ft_strlcat(char * restrict dst, const char * restrict src, size_t dstsize)
{
    size_t dst_len;
    size_t src_len;
    
    dst_len = 0;
    src_len = 0;
    while(dst[dst_len])
    dst_len++;
    while(src[src_len])
    src_len++;
    if (dst_len + src_len - 1 > dstsize)
        return(dst_len + src_len - 1);
    else
    {
        dst_len = 0;
     while(src[src_len])
        dst[dst_len++] = src[src_len++];
    }
    dst[dst_len] = '\0';
    return(dst_len + src_len - 1);
}