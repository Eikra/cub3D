/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iecharak <iecharak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 18:50:29 by iecharak          #+#    #+#             */
/*   Updated: 2022/11/01 23:33:55 by iecharak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count(int num)
{
	int	n;

	n = 0;
	if (num <= 0)
		n++;
	while (num)
	{
		n++;
		num /= 10;
	}
	return (n);
}

char	*ft_itoa(int n)
{
	char	*num;
	int		len;
	long	nn;

	nn = n;
	len = count(n);
	num = malloc((len + 1) * sizeof(char));
	if (!num)
		return (0);
	num[len--] = '\0';
	if (nn < 0)
	{
		num[0] = '-';
		nn *= -1;
	}
	if (nn == 0)
		num[0] = '0';
	while (nn)
	{
		num[len--] = (nn % 10) + 48;
		nn /= 10;
	}
	return (num);
}
