/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m <m@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:07:07 by iecharak          #+#    #+#             */
/*   Updated: 2023/09/02 17:35:05 by m                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_display(t_data *data)
{
	draw_rays(data);return;
	draw_view(data);
	draw_minimap(data);
}

int	ft_strraw(char **map)
{
	int i;
	
	i = 0;
	while(map && map[i])
		i++;
	return (i);
}

int	deal_key(int key, t_data *data)
{
	if (key == ESC)
	{
		printf("You closed the game using ESC key !");
		mlx_destroy_window(data->id, data->w_id);
		exit(0);
	}
	if ((key == ON || key == W) && !is_wall_front(data))
	{
		data->p_x += (6.0 * cos(data->angl));
		data->p_y += (6.0 * sin(data->angl));
		mlx_destroy_image(data->id, data->img);
		data->img = mlx_new_image(data->id, W_W, W_H);
		data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length,
								&data->endian);
		ft_display(data);
		mlx_put_image_to_window(data->id, data->w_id, data->img, 0, 0);
	}
	if ((key == BACK || key == S) && !is_wall_back(data))
	{
		data->p_x -= (6.0 * cos(data->angl));
		data->p_y -= (6.0 * sin(data->angl));
		mlx_destroy_image(data->id, data->img);
		data->img = mlx_new_image(data->id, W_W, W_H);
		data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length,
								&data->endian);
		ft_display(data);
		mlx_put_image_to_window(data->id, data->w_id, data->img, 0, 0);
	}
	if (key == RIGHT) // && !is_wall_right(data)
	{
		update_angle(data, RIGHT);
		mlx_destroy_image(data->id, data->img);
		data->img = mlx_new_image(data->id, W_W, W_H);
		data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length,
								&data->endian);
		ft_display(data);
		mlx_put_image_to_window(data->id, data->w_id, data->img, 0, 0);
	}
	if (key == LEFT )//&& && !is_wall_left(data)
	{
		update_angle(data, LEFT);
		mlx_destroy_image(data->id, data->img);
		data->img = mlx_new_image(data->id, W_W, W_H);
		data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length,
								&data->endian);
		ft_display(data);
		mlx_put_image_to_window(data->id, data->w_id, data->img, 0, 0);
	}
	return (0);
}

void	ft_mlx(t_data *data)
{
	ft_get_position(&data->p_x, &data->p_y, data->map);
	init_angle(data);
	data->id = mlx_init();
	set_textures(data);
	data->w_id = mlx_new_window(data->id, W_W, W_H, "cub3D");
	data->img = mlx_new_image(data->id, W_W, W_H);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length,
								&data->endian);
	ft_display(data);
	mlx_put_image_to_window(data->id, data->w_id, data->img, 0, 0);
	mlx_hook(data->w_id, 2, 1L<<0, deal_key, data);
	mlx_hook(data->w_id, 17, 0, ft_exit, data);
	mlx_loop(data->id);
}

int	main(int ac, char **av)
{
	t_data	data;

	init_data(&data);
	//printf("%f\n", tan((7.0 * M_PI) / 4.0));
	if (ac == 2)
	{
		if (check_map_name(av))
			return (exit(0), 0);
		if (open_file_error(&data, av[1]))
			return (free_data(&data), 0);
		if (read_map(&data))
			return (free_data(&data), 0);
		if (map_errors(&data))
			return (free_data(&data), 0);
		ft_mlx(&data);
	}
	else
		ft_err("Invalid number of arguments!");
	return (0);
}

// void	ft_display(t_data *data)
// {
// 	int x;
// 	int y;
// 	y = 0;
// 	while (data->map[y])
// 	{
// 		x = 0;
// 		while (data->map[y][x])
// 		{
// 			if (data->map[y][x] == '0')
// 				my_mlx_pixel_put(data,x, y,  16777215);
// 			if (data->map[y][x] == 'N')
// 				my_mlx_pixel_put(data,x, y,  255 << 16);
// 			x++;
// 		}
// 		y++;
// 	}
// }

// int	is_wall_down(t_data *data)
// {
// 	int i;
// 	int	j;
// 	i = data->p_y / REC + 1;
// 	j = data->p_x / 64;
// 	if (data->map[i][j] == '1' && (data->p_y + 6) > (i * 64))
// 		return (1);
// 	return (0);
// }

// int	is_wall_up(t_data *data)
// {
// 	int i;
// 	int	j;
// 	i = (data->p_y / 64);
// 	j = data->p_x / REC;
// 	if (data->map[i -1][j] == '1' && (data->p_y - 17) <= (i * REC))
// 		return (1);
// 	return (0);
// }