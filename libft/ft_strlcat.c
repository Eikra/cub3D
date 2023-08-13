/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iecharak <iecharak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 12:12:42 by iecharak          #+#    #+#             */
/*   Updated: 2022/10/21 18:42:23 by iecharak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	src_size;
	size_t	dst_size;
	size_t	i;

	i = 0;
	src_size = 0;
	dst_size = 0;
	while (src[src_size])
		src_size++;
	while (dst_size < dstsize && dst[dst_size])
		dst_size++;
	if (dstsize == 0)
		return (src_size);
	if (dstsize > dst_size)
	{
		while (src[i] && (--dstsize - dst_size) > 0)
		{
			dst[dst_size + i] = src[i];
			i++;
		}
		dst[dst_size + i] = '\0';
		return (src_size + dst_size);
	}
	return (src_size + dstsize);
}
