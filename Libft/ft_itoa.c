
char *ft_itoa(int n)
{
    char *nstr;
    int char_count;
    int i;
    int sign;
    int temp;
    
    temp = n;
    char_count = 0;
    i = 0;
    sign = 1;
    if (temp < 0 )
    {
        sign = -1;
        char_count++;
    }
    while(temp)
    {
        char_count++;
        temp /= 10;
    }
    nstr = (char*)malloc(sizeof(char*)*char_count + 1);
    while(i < char_count)
    {
        temp *= 10;
        i++;
    }
    if (!sign){
        temp /= 10;
        nstr[i++] = '-';
    }
    i = 0;
    while(i < char_count)
    {
        nstr[i++] = n / temp;
        temp /= 10; 
    }
    return (nstr);
}