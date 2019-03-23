// #include "../includes/ft_printf.h"

// char     ft_space(char *str, int pos, t_argu arg)
// {
//     //str is the captured string
//     char *st_num;
//     int i;
//     int number;

//     i = 0;
//     st_num = malloc(ft_strlen(str) + 1);
//     while (ft_isdigit(str[i]))
//     {
//         st_num[i] = str[pos];
//         i++;
//         pos++;
//     }
//     number = ft_atoi(st_num);
//     // Set spacing to the found number
//     arg.space_size = number;
//     if (str[i] == '.')
//         arg.precision = 1;
//     if (str[i] == '*')
//         arg.multiple = 1;
//     if (str[i] == '+')
//         arg.sign = 1;
//     if (str[i] == '-')
//         arg.leftAlign = 1;
//     return (str[i]);
// }


// int ft_getpow(int number)
// {
//     int power;

//     power = 1;
//     if (number == 0)
//         return (0);
//     while (number > 0)
//     {
//         number /= 10;
//         power *= 10;
//     }
//     return (power);
// }

// int ft_get_doublepow(float number)
// {
//     int power;

//     power = 1;
//     if (number == 0)
//         return (0);
//     while (number > 0)
//     {
//         number /= 10;
//         power *= 10;
//     }
//     return (power);
// }

// // char *buildString(t_argu arg)
// // {
// //     char* str;

// //     return (str);
// // }
