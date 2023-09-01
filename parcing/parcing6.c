/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   parcing6.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: iecharak <iecharak@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/08/18 19:53:36 by iecharak		  #+#	#+#			 */
/*   Updated: 2023/08/19 10:20:52 by iecharak		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../cub3d.h"

int	get_map_len(t_line *lines)
{
	t_line	*tmp;
	int		len;
	int		n;
	int		i;

	len = 0;
	i = 0;
	tmp = lines;
	while (tmp)
	{
		if (i > 5)
		{
			n = ft_strlen(tmp->line);
			if (len < n)
				len = n;
		}
		tmp = tmp->next;
		i++;
	}
	return (len);
}

int	char_err(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map && map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != ' ' && map[i][j] != '0' && map[i][j] != '1'
				&& map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'E'
				&& map[i][j] != 'W')
				return (ft_err("Invalid character in map !!"));
			j++;
		}
		i++;
	}
	return (0);
}

int	char_err2(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map && data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'N')
				data->p_n++;
			if (data->map[i][j] == 'S')
				data->p_s++;
			if (data->map[i][j] == 'E')
				data->p_e++;
			if (data->map[i][j] == 'W')
				data->p_w++;
			j++;
		}
		i++;
	}
	if ((data->p_n + data->p_s + data->p_e + data->p_w) != 1)
		ft_err("cub3D need one player not more not less!!");
	return (0);
}

int	border_err(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map && map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				if (!i || !map[i + 1] || !j || !map[i][j + 1])
					return (ft_err("cub3D need a closed map borders!!"));
				if ((map[i + 1] && (int)ft_strlen(map[i + 1]) <= j)
					|| (map[i + 1] && map[i + 1][j] == ' ') || ((int)
					ft_strlen(map[i - 1]) <= j) || map[i - 1][j] == ' '
					|| map[i][j + 1] == ' ' || map[i][j - 1] == ' ')
					return (ft_err("cub3D need a closed map borders!!"));
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	set_pos(t_data *data)
{
	if (data->p_n)
		data->pos = 1;
	if (data->p_e)
		data->pos = 2;
	if (data->p_s)
		data->pos = 3;
	if (data->p_w)
		data->pos = 4;
}

int	map_errors(t_data *data)
{
	if (ft_linesize(data->lines) <= 8)
		return (ft_err("Incomplet map"));
	if (path_error(data))
		return (1);
	if (color_err(data))
		return (1);
	if (char_err(data->map))
		return (1);
	if (char_err2(data))
		return (1);
	if (border_err(data->map))
		return (1);
	//get_textures(data);
	set_pos(data);
	return (0);
}
