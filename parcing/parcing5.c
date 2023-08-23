/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   parcing5.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: iecharak <iecharak@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/08/18 19:44:14 by iecharak		  #+#	#+#			 */
/*   Updated: 2023/08/18 19:48:52 by iecharak		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../cub3d.h"

int	get_map_line(t_data *data)
{
	t_line	*tmp;
	int		i;

	tmp = data->lines;
	i = 0;
	data->map = malloc(sizeof(char *) * (data->row + 1));
	if (!data->map)
		return (1);
	while (i++ < 6)
		tmp = tmp->next;
	i = 0;
	while (tmp)
	{
		data->map[i] = tmp->line;
		tmp = tmp->next;
		i++;
	}
	data->map[i] = NULL;
	return (0);
}

int	ft_line_len(char *line)
{
	int		i;
	int		j;
	int		sp;

	i = 0;
	j = 0;
	sp = 0;
	while (line && line[i])
	{
		if (line[i] <= REC)
		{
			sp++;
			j++;
		}
		while (line[i] && line[i] <= REC)
			i++;
		if (line[i])
		{
			i++;
			j++;
		}
	}
	if (sp > 1)
		return (0);
	return (j);
}

void	get_line2(char *line, char **s)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = *s;
	while (line && line[i])
	{
		if (line[i] <= REC)
		{
			tmp[j] = ' ';
			j++;
		}
		while (line[i] && line[i] <= REC)
			i++;
		if (line[i])
		{
			tmp[j] = line[i];
			i++;
			j++;
		}
	}
	tmp[j] = '\0';
}

char	**get_split_line(char *line)
{
	int		j;
	char	*tmp;
	char	**ret;

	j = ft_line_len(line);
	if (j == 0)
		return (NULL);
	tmp = malloc (sizeof(char) * (j + 1));
	if (!tmp)
		return (NULL);
	get_line2(line, &tmp);
	if (!tmp)
		return (NULL);
	ret = ft_split(tmp, ' ');
	if (!ret)
		return (NULL);
	free(tmp);
	return (ret);
}

int	map_elmnt_err(t_data *data)
{
	data->map_len = get_map_len(data->lines);
	data->row = ft_linesize(data->lines) - 6;
	if (get_map_line(data))
		return (1);
	if (get_textures(data))
		return (1);
	return (0);
}
