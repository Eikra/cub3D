/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   parcing1.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: iecharak <iecharak@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/08/18 19:30:52 by iecharak		  #+#	#+#			 */
/*   Updated: 2023/08/19 12:48:01 by iecharak		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../cub3d.h"

t_line	*ft_linenew(char *content)
{
	t_line	*frst_list;

	frst_list = malloc(sizeof(t_line));
	if (!frst_list)
		return (NULL);
	frst_list->line = content;
	frst_list->next = NULL;
	return (frst_list);
}

t_line	*ft_linelast(t_line *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	ft_lineadd_back(t_line **lst, t_line *new)
{
	if (*lst)
		ft_linelast(*lst)->next = new;
	else
		*lst = new;
}

int	ft_linesize(t_line *lst)
{
	int		size;
	t_line	*ptr;

	size = 0;
	ptr = lst;
	while (ptr != NULL)
	{
		ptr = ptr->next;
		size++;
	}
	return (size);
}

int	c_err(t_line *lines)
{
	t_line	*tmp;
	int		i;
	int		j;

	tmp = lines;
	i = 0;
	j = 0;
	while (tmp && i < 6)
	{
		if (!ft_strncmp(tmp->line, "C ", 2))
			j++;
		tmp = tmp->next;
		i++;
	}
	if (j != 1)
		return (1);
	return (0);
}
