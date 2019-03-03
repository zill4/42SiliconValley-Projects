#include "../includes/ft_printf.h"

void pf_putstr(char* s, int *count)
{
	int i;

	i = 0;
	if (s == NULL)
		pf_putstr("(null)", count);
	else
		while(s[i])
			pf_putchar(s[i++], count);
}
