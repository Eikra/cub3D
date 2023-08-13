/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iecharak <iecharak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 13:46:53 by iecharak          #+#    #+#             */
/*   Updated: 2022/10/20 21:34:22 by iecharak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*c1;
	unsigned char	*c2;

	c1 = (unsigned char *) s1;
	c2 = (unsigned char *) s2;
	i = 0;
	while (n > 0)
	{
		if (c1[i] != c2[i])
			return (c1[i] - c2[i]);
		n--;
		i++;
	}
	return (0);
}
