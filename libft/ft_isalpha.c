/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iecharak <iecharak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:25:45 by iecharak          #+#    #+#             */
/*   Updated: 2022/10/21 18:55:35 by iecharak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isuper(int c)
{
	if (c >= 65 && c <= 90)
		return (1);
	return (0);
}

int	ft_lower(int c)
{
	if (c >= 97 && c <= 122)
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	if (ft_isuper(c) || ft_lower(c))
		return (1);
	return (0);
}
