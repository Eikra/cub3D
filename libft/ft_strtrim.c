/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m <m@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 21:41:25 by iecharak          #+#    #+#             */
/*   Updated: 2023/08/15 18:37:23 by m                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*strtrim;
	int		i;
	int		j;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	j = ft_strlen(s1) - 1;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (s1[j] && ft_strchr(set, s1[j]))
		j--;
	strtrim = ft_substr(s1, i, j - i + 1);
	return (strtrim);
}

char	*ft_strrtrim(char const *s1, char const *set)
{
	char	*strtrim;
	int		i;
	int		j;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	j = ft_strlen(s1) - 1;
	while (s1[i] && ft_strchr("\n", s1[i]))
		i++;
	while (s1[j] && ft_strchr(set, s1[j]))
		j--;
	strtrim = ft_substr(s1, i, j - i + 1);
	return (strtrim);
}
