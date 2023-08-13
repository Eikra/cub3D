/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iecharak <iecharak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 22:20:21 by iecharak          #+#    #+#             */
/*   Updated: 2022/11/03 19:01:20 by iecharak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*frst_list;

	frst_list = malloc(sizeof(t_list));
	if (!frst_list)
		return (NULL);
	frst_list->content = content;
	frst_list->next = NULL;
	return (frst_list);
}
