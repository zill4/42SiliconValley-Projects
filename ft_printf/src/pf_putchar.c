#include "../includes/ft_printf.h"

void pf_putchar(char c, int *count)
{
	*count += 1;
	write(1,&c, 1);

}
