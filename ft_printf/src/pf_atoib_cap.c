#include "../includes/ft_printf.h"


char to_hex_cap(int64_t i)
{
	i = i % 10;
	return ('A' + i);
}

void pf_atoib_cap(long  value, int base, int *count)
{
		long  div_c;
		long  mod_c;

		div_c = value / base;
		mod_c = value % base;

			if (value == 0)
				return;
		value = div_c;
		pf_atoib_cap(value, base, count);
			if (mod_c >= 10 && base > 10)
				pf_putchar(to_hex_cap(mod_c), count);
			else
				pf_putnbr(mod_c, count);
}