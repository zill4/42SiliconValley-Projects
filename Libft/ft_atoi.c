#include <libft.h>

int ft_atoi(const char *str)
{
    int i;
    int sign;
    int value;
    int place;

    place = 1;
    value = 0;
    sign = 1;
    i = 0;
    if (str[i] == '-')
    {
        sign = -1;
    }
    while(str[i])
        i++;

    while (ft_isdigit(str[--i]) && i >= 0) 
    {
        value += ((str[i] - '0') * place);
        printf("The value: %d  The string char: %c  The place: %d \n", value, str[i], place);
        place *= 10;
    }
    return (value * sign);
    
}