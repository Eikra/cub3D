/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   parcing2.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: iecharak <iecharak@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/08/18 19:34:58 by iecharak		  #+#	#+#			 */
/*   Updated: 2023/08/19 12:48:48 by iecharak		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../cub3d.h"

int	no_err(t_line *lines)
{
	t_line	*tmp;
	int		i;
	int		j;

	tmp = lines;
	i = 0;
	j = 0;
	while (tmp && i < 6)
	{
		if (!ft_strncmp(tmp->line, "NO ", 3))
			j++;
		tmp = tmp->next;
		i++;
	}
	if (j != 1)
		return (1);
	return (0);
}

int	so_err(t_line *lines)
{
	t_line	*tmp;
	int		i;
	int		j;

	tmp = lines;
	i = 0;
	j = 0;
	while (tmp && i < 6)
	{
		if (!ft_strncmp(tmp->line, "SO ", 3))
			j++;
		tmp = tmp->next;
		i++;
	}
	if (j != 1)
		return (1);
	return (0);
}

int	we_err(t_line *lines)
{
	t_line	*tmp;
	int		i;
	int		j;

	tmp = lines;
	i = 0;
	j = 0;
	while (tmp && i < 6)
	{
		if (!ft_strncmp(tmp->line, "WE ", 3))
			j++;
		tmp = tmp->next;
		i++;
	}
	if (j != 1)
		return (1);
	return (0);
}

int	ea_err(t_line *lines)
{
	t_line	*tmp;
	int		i;
	int		j;

	tmp = lines;
	i = 0;
	j = 0;
	while (tmp && i < 6)
	{
		if (!ft_strncmp(tmp->line, "EA ", 3))
			j++;
		tmp = tmp->next;
		i++;
	}
	if (j != 1)
		return (1);
	return (0);
}

int	f_err(t_line *lines)
{	
	t_line	*tmp;
	int		i;
	int		j;

	tmp = lines;
	i = 0;
	j = 0;
	while (tmp && i < 6)
	{
		if (!ft_strncmp(tmp->line, "F ", 2))
			j++;
		tmp = tmp->next;
		i++;
	}
	if (j != 1)
		return (1);
	return (0);
}
