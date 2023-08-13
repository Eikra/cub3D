/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iecharak <iecharak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 21:40:53 by iecharak          #+#    #+#             */
/*   Updated: 2022/11/01 22:41:28 by iecharak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	size_t	len;

	if ((char)c == 0)
		return ((char *)s + ft_strlen(s));
	len = ft_strlen(s);
	i = len - 1;
	while (i < len)
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i--;
		len--;
	}
	return (0);
}
