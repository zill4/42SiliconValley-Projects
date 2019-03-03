#include "../includes/ft_printf.h"

void pf_putnbr(long d, int *count)
{
	int64_t sign;
	sign = 1;
	if (d < 0)
	{
		pf_putchar('-', count);
		sign = -1;
	}

	if(-9 <= d && d <= 9)
	{
		pf_putchar(d * sign + '0', count);
	}
	else
	{
		pf_putnbr((d / 10) * sign, count);
		pf_putnbr((d % 10) * sign, count);
	}
}
