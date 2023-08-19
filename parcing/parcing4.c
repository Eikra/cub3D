/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   parcing4.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: iecharak <iecharak@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/08/18 19:45:17 by iecharak		  #+#	#+#			 */
/*   Updated: 2023/08/19 12:20:56 by iecharak		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../cub3d.h"

int	str_content(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] > 32)
			return (1);
		i++;
	}
	return (0);
}

int	read_map2(t_data *data, char *str, int *i)
{
	if (str_content(str) && (*i) < 6)
	{
		ft_lineadd_back(&data->lines, ft_linenew(ft_strtrim(str, "\n \t\r\v\f")));
		(*i)++;
	}
	else if ((*i) > 5)
	{
		if (str_content(str))
		{
			ft_lineadd_back(&data->lines, ft_linenew(ft_strrtrim(str, SET)));
			(*i)++;
		}
		else if (!str_content(str) && (*i) > 6)
			return (free(str), ft_err("Empty line in map"));
	}
	return (0);
}

int	read_map(t_data *data)
{
	char	*str;
	int		i;

	str = get_next_line(data->fd);
	i = 0;
	while (str && str[0])
	{
		if (read_map2(data, str, &i))
			return (1);
		free(str);
		str = get_next_line(data->fd);
	}
	if (!data->lines)
		return (ft_err("Empty map"));
	return (0);
}

int	check_textures(t_data *data, char ***s)
{
	char	**str;

	str = *s;
	if (!ft_strncmp(str[0], "EA", 3))
		data->path_ea = str[1];
	else if (!ft_strncmp(str[0], "NO", 3))
		data->path_no = str[1];
	else if (!ft_strncmp(str[0], "SO", 3))
		data->path_so = str[1];
	else if (!ft_strncmp(str[0], "WE", 3))
		data->path_we = str[1];
	else if (!ft_strncmp(str[0], "F", 2))
		data->char_f = str[1];
	else if (!ft_strncmp(str[0], "C", 2))
		data->char_c = str[1];
	else
		return (1);
	return (0);
}

int	get_textures(t_data *data)
{
	char	**str;
	t_line	*tmp;
	int		i;

	tmp = data->lines;
	i = 0;
	while (tmp && i < 6)
	{
		str = get_split_line(tmp->line);
		if (!str)
			return (1);
		if (check_textures(data, &str))
			return (1);
		free (str[0]);
		free(str);
		tmp = tmp->next;
		i++;
	}
	return (0);
}
// if (str_content(str) && i < 6)
// {
// 	ft_lineadd_back(&data->lines, ft_linenew(ft_strtrim(str, "\n \t\r\v\f")));
// 	i++;
// }
// else if (i > 5)
// {
// 	if (str_content(str))
// 	{
// 		ft_lineadd_back(&data->lines, ft_linenew(ft_strrtrim(str, "\n \t\r\v\f")));
// 		i++;
// 	}
// 	else if (!str_content(str) && i > 6)
// 		return (free(str), ft_err("Empty line in map"));
// }