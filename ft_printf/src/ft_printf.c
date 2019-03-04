/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcrisp <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 10:45:50 by jcrisp            #+#    #+#             */
/*   Updated: 2018/09/20 19:09:30 by jcrisp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/ft_printf.h"
#include <stdio.h>
#include <limits.h>

void isFlag(char *str_cap, va_list ap, int *count)
{
  int i;
  int k;
  char flags[30] = "cspdioufxXlhL0123456789.*#0-+ ";

  i = 0;
  k = 0;
  // Till str_cap finds another % or till end of str_cap
  while (str_cap[i] != '%' || !str_cap[i])
  {
    // Given a flag respective function
    while (flags[k])
    {

      k++;
    }
    i++;
  }
  
	if (c == 's')
		pf_putstr(va_arg(ap, char*), count);
	else if (c == 'c')
		pf_putchar(va_arg(ap, int), count);
	else if (c == 'd' || c == 'i')
		pf_putnbr(va_arg(ap, int), count);
	else if (c == 'p'){
		pf_putstr("0x", count);
		pf_atoib(va_arg(ap, int64_t), 16, count);
	}
	else if (c == 'o')
		pf_atoib(va_arg(ap, int64_t), 8, count);
	else if (c == 'u')
		pf_atoib(va_arg(ap, int64_t), 10, count);
	else if (c == 'x')
		pf_atoib(va_arg(ap, int64_t), 16, count);
  else if (c == 'X'){
		pf_atoib_cap(va_arg(ap, int64_t), 16, count);
  }

}

int b_printf(char* str, ...)
{
	va_list valist;
	int i;
	int count;
    // String capture of the squence to check.
  char *str_cap;

	count = 0;
	va_start(valist, str);
	i = 0;
	while(str[i])
	{
		if (str[i] == '%')
		{
      //  Must send whole string till a given point.
      //  str_cap should be equal to position as is in read.
      str_cap = str + i + 1;
      isFlag(str_cap, valist, &count);
			i++;
		}
		else
			pf_putchar(str[i], &count);
		i++;
	}

return count;
}


  int   main(void)
  {
    char            *str = "hello";
    char            chr = 'g';
    int                snum = -2466;
    int                psnum = 2466;
    unsigned int    unum = -444;
    unsigned int    xnum = -500;
    unsigned int    onum = -467;
    char            *empty = NULL;

    printf("mine = %d, actual = %d\n", b_printf("my   int (-d | +i):\t%d | %i\n", snum, psnum), printf("real int (-d | +i):\t%d | %i\n", snum, psnum));
    printf("\n");

    printf("mine = %d, actual = %d\n", b_printf("my   hex:\t\t%x\n", xnum), printf("real hex:\t\t%x\n", xnum));
    printf("\n");

    printf("mine = %d, actual = %d\n", b_printf("my   hex:\t\t%x\n", xnum*-1), printf("real hex:\t\t%x\n", xnum*-1));
    printf("\n");

    printf("mine = %d, actual = %d\n", b_printf("my   oct:\t\t%o\n", onum), printf("real oct:\t\t%o\n", onum));
    printf("\n");

    printf("mine = %d, actual = %d\n", b_printf("my   oct:\t\t%o\n", onum*-1), printf("real oct:\t\t%o\n", onum*-1));
    printf("\n");

    printf("mine = %d, actual = %d\n", b_printf("my   unsigned:\t\t%u\n", unum), printf("real unsigned:\t\t%u\n", unum));
    printf("\n");

    printf("mine = %d, actual = %d\n", b_printf("my   unsigned:\t\t%u\n", unum*-1), printf("real unsigned:\t\t%u\n", unum*-1));
    printf("\n");

    printf("mine = %d, actual = %d\n", b_printf("my   string:\t\t%s\n", str), printf("real string:\t\t%s\n", str));
    printf("\n");

    printf("mine = %d, actual = %d\n", b_printf("my   string:\t\t%c\n", chr), printf("real string:\t\t%c\n", chr));
    printf("\n");

    printf("mine = %d, actual = %d\n", b_printf("my   pointer:\t\t%p\n", str), printf("real pointer:\t\t%p\n", str));
    printf("\n");
    printf("real str empty:\t\t%s\n", empty);
    printf("mine = %-d, actual = %-d\n", b_printf("my   str empty:\t\t%s\n", empty), printf("real str empty:\t\t%s\n", empty));
    printf("\n");
    printf("\t\t\t---> my   length: %d <---\n", b_printf("%d %s %c %x  ~random-words./\'\\ %o %u %p\n", SHRT_MAX, str, chr, xnum, onum, unum, str));
    printf("\t\t\t---> real length: %d <---\n", printf("%+-.*f %s %c %-#x  ~random-words./\'\\ %#o %u %p\n",-100,SHRT_MAX * 1.0, str, chr, xnum, onum, unum, str));
    printf("\n");
    int x = 365;
    const char * y = "monkeys";
    printf ("<%d> is not justified.\n", x);
    printf ("<%5d> is right-justified.\n", x);
    printf ("<%-5d> The minus sign makes it left-justified.\n", x);
    printf ("'%s' is not justified.\n", y);
    printf ("'%10s' is right-justified.\n", y);
    printf ("'%-10s' is left-justified using a minus sign.\n", y);

  	return (0);
  }
