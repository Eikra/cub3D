/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   parcing3.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: iecharak <iecharak@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/08/18 19:39:42 by iecharak		  #+#	#+#			 */
/*   Updated: 2023/08/19 10:10:20 by iecharak		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_err(char *err)
{
	ft_putstr_fd("\033[0;31mError:\033[0m \033[0;33m", 2);
	ft_putstr_fd(err, 2);
	ft_putstr_fd("\033[0m\n", 2);
	return (1);
}

int	ft_strrncmp(char *s, char *r, int n)
{
	int	i;
	int	j;

	i = ft_strlen(s) - 1;
	j = ft_strlen(r) - 1;
	while (n)
	{
		if (s[i] != r[j])
			return (1);
		n--;
		i--;
		j--;
	}
	return (0);
}

int	check_map_name(char **av)
{
	if (ft_strrncmp(av[1], ".cub", 4))
		return (ft_err("Invalid file type, use .cub"));
	return (0);
}

int	open_file_error(t_data *data, char *av)
{
	data->fd = open(av, O_RDONLY);
	if (data->fd < 0)
		return (ft_err("File not found or permission denied!"));
	return (0);
}

int	path_error(t_data *data)
{
	if (no_err(data->lines) || so_err(data->lines)
		|| we_err(data->lines) || ea_err(data->lines))
		return (ft_err("Invalid path to the textures"));
	if (f_err(data->lines) || c_err(data->lines))
		return (ft_err("Invalid type color identifier"));
	if (map_elmnt_err(data))
		return (1);
	return (0);
}
