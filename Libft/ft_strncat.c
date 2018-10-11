/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcrisp <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 02:57:22 by jcrisp            #+#    #+#             */
/*   Updated: 2018/10/08 15:00:29 by jcrisp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *restrict s1, const char *restrict s2, size_t n)
{
	int i;
	int k;

	k = 0;
	i = ft_strlen(s1);
	while (s2[k] && k < (int)n)
		s1[i++] = s2[k++];
	s1[i] = '\0';
	return (s1);
}
