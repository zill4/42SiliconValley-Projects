/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcrisp <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 01:48:42 by jcrisp            #+#    #+#             */
/*   Updated: 2019/03/25 01:49:59 by jcrisp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putunbr(uintmax_t n)
{
	char	c;

	c = '0';
	if (n < 10)
		ft_putchar(c + n);
	else
	{
		ft_putunbr(n / 10);
		ft_putunbr(n % 10);
	}
}