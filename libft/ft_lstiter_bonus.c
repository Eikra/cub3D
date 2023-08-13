/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iecharak <iecharak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:08:58 by iecharak          #+#    #+#             */
/*   Updated: 2022/11/03 19:01:01 by iecharak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (lst && f)
	{
		while (lst != NULL)
		{
			f(lst->content);
			lst = (lst)->next;
		}
	}
}
/*int	main(void)
{
	t_list	*lst;
	t_list	*new;
	t_list	*head;
	t_list	*temp;

	lst = ft_lstnew(ft_strdup("abcd"));
	new = ft_lstnew(ft_strdup("efgh"));
	head = lst;
	ft_lstadd_back(&lst, new);
	temp = head;
	while (temp)
	{
		printf("%s\n", temp->content);
		temp = temp->next;
	}
	printf("---------------- \n");
	temp = head;
	ft_lstiter(lst, del);
	temp = head;
	while (temp)
	{
		printf("%s\n", temp->content);
		temp = temp->next;
	}
}*/
