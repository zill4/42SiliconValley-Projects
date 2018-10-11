/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcrisp <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 02:49:18 by jcrisp            #+#    #+#             */
/*   Updated: 2018/10/08 13:47:06 by jcrisp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	size_t		i;
	char		*p_dst;
	char		*p_src;

	i = 0;
	p_src = (char *)src;
	p_dst = (char *)dst;
	while (i < n)
	{
		*(char *)(p_dst + i) = *(char *)(p_src + i);
		i++;
	}
	return (dst);
}
