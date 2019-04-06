/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putfloat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcrisp <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 06:03:52 by jcrisp            #+#    #+#             */
/*   Updated: 2019/04/06 06:12:15 by jcrisp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int				int_to_str(int x, char str[], int d)
{
	int			i;

	i = 0;
	while (x)
	{
		str[i++] = (x % 10) + '0';
		x = x / 10;
	}
	while (i < d)
		str[i++] = '0';
	str = ft_strrev(str);
	str[i] = '\0';
	return (i);
}

int				num_len(long double n)
{
	int			i;

	i = 0;
	while (n > 0)
	{
		n /= 10.0;
		i++;
	}
	return (i);
}

void			ftoa(long double n, char *res, int afterpoint)
{
	int			ipart;
	long double	fpart;
	int			i;

	ipart = (int)n;
	fpart = n - (long double)ipart;
	i = int_to_str(ipart, res, 0);
	if (afterpoint != 0)
	{
		res[i] = '.';
		fpart = fpart * pow(10, afterpoint);
		int_to_str((int)fpart, res + i + 1, afterpoint);
	}
}
