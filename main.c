/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iecharak <iecharak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:07:07 by iecharak          #+#    #+#             */
/*   Updated: 2023/08/19 15:44:06 by iecharak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_data(t_data *data)
{
	t_line	*tmp;

	while (data->lines)
	{
		tmp = data->lines;
		data->lines = data->lines->next;
		free(tmp->line);
		free(tmp);
	}
	if (data->map)
		free(data->map);
	if (data->path_ea)
		free(data->path_ea);
	if (data->path_no)
		free(data->path_no);
	if (data->path_so)
		free(data->path_so);
	if (data->path_we)
		free(data->path_we);
	if (data->char_c)
		free(data->char_c);
	if (data->char_f)
		free(data->char_f);
}

void	init_data(t_data *data)
{
	data->buffer = NULL;
	data->lines = NULL;
	data->map = NULL;
	data->path_ea = NULL;
	data->path_no = NULL;
	data->path_so = NULL;
	data->path_we = NULL;
	data->char_f = NULL;
	data->char_c = NULL;
	data->p_n = 0;
	data->p_s = 0;
	data->p_e = 0;
	data->p_w = 0;
}

void	print_data(t_data data)
{
	int	i;

	if (data.path_no)
		printf("%s\n", data.path_no);
	if (data.path_so)
		printf("%s\n", data.path_so);
	if (data.path_we)
		printf("%s\n", data.path_we);
	if (data.path_ea)
		printf("%s\n", data.path_ea);
	if (data.char_f)
		printf("%s====> %d\n", data.char_f, data.f_color);
	if (data.char_c)
		printf("%s====> %d\n", data.char_c, data.c_color);
	i = 0;
	while (data.map && data.map[i])
	{
		printf("%s\n-", data.map[i]);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data	data;

	init_data(&data);
	if (ac == 2)
	{
		if (check_map_name(av))
			return (0);
		if (open_file_error(&data, av[1]))
			return (free_data(&data), 0);
		if (read_map(&data))
			return (free_data(&data), 0);
		if (map_errors(&data))
			return (free_data(&data), 0);
		print_data(data);
		free_data(&data);
	}
	else
		ft_err("Invalid number of arguments!");
	return (0);
}
