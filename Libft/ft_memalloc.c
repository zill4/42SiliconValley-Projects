void *ft_memalloc(size_t size)
{
    void *mem;

    if (mem = (void *)memalloc(sizeof(void *)* size + 1))
        return(mem);
    else
        return(NULL);

}