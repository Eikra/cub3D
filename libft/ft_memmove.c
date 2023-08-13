/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iecharak <iecharak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:30:16 by iecharak          #+#    #+#             */
/*   Updated: 2022/10/30 22:43:01 by iecharak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	if (src == 0 && dst == 0)
		return ((void *)0);
	i = n - 1;
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (d > s)
	{
		while (n > 0)
		{
			d[i] = s[i];
			n--;
			i--;
		}
	}
	else
		return (ft_memcpy(dst, src, n));
	return (dst);
}
