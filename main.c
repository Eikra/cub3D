/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iecharak <iecharak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:07:07 by iecharak          #+#    #+#             */
/*   Updated: 2023/08/23 17:56:03 by iecharak         ###   ########.fr       */
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
		printf("%s\n", data.map[i]);
		i++;
	}
}

int	ft_exit(void)
{
	printf("Exit the program with the X !!");
	exit(0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_rectangle(t_data *data, double x, double y, int color)
{
	double i;
	double j;

	i = 0;
	while (i < REC)
	{
		j = 0;
		while (j < REC)
		{
			// if (!j || !i)
			// my_mlx_pixel_put(data, (x * REC) + j, (y * REC) + i,255);
			// else 
			my_mlx_pixel_put(data, (x * REC) + j, (y * REC) + i,color);
			j++;
		}
		i++;
	}
}

// void	draw_player(t_data *data, int x, int y, int color)
// {
// 	int i;
// 	int j;

// 	i = -1;
// 	while (i < 2)
// 	{
// 		j = -1;
// 		while (j < 2)
// 		{
// 			my_mlx_pixel_put(data, x + j, y  + i, 0);
// 			j++;
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	while (i < 16)
// 	{
// 		my_mlx_pixel_put(data, x + j * cos(data->angl), y   + i * sin(data->angl), color);
// 		j++;
// 		i++;
// 	}
// }

void	draw_ray(t_data *data, double angl, int color, int ray_len)
{
	int i;

	i = 0;
	while (i < ray_len)
	{
		my_mlx_pixel_put(data, data->p_x + i * cos(angl), data->p_y + i * sin(angl), color);
		i++;
	}
}

int	closed_erea(char **map, int i, int j)
{
	if(map[i - 1][j] == '1' && map[i + 1][j] == '1' && map[i][j + 1] == '1' && map[i][j - 1] == '1')
		return (1);
	return (0);
}

long	get_ray_len(t_data *data, double field)
{
	long	ray_len;
	int		i;
	int		j;
	
	ray_len = 0;
	while (1)
	{
		i = ((data->p_y + ray_len * sin(field))/ (double)REC);
		j = ((data->p_x + ray_len * cos(field)) / (double)REC);
		if (data->map[i][j] == '1'|| (data->map[i][j] == '0' && closed_erea(data->map, i, j)))
			return (ray_len);
		ray_len++;
	}
	return (0);
	
}

void	draw_view(t_data *data, int color)
{
	double	field;
	long	ray_len;
	double	deg_by_pex;

	field = data->angl - ((M_PI / 180) * 30);
	deg_by_pex = ((M_PI / 180) * 60) / (32 * ft_strlen(data->map[0]));
	while (field < data->angl + (M_PI / 180) * 30)
	{
		//ray_len = 20;
		ray_len = get_ray_len(data, field);
		draw_ray(data, field, color, ray_len);
		field += deg_by_pex;
	}
}

void	draw_player(t_data *data, double x, double y, int color)
{
	int i;

	i = 0;
	my_mlx_pixel_put(data, x, y, color);
	// while (i < 16)
	// {
	// 	my_mlx_pixel_put(data, x + i * cos(data->angl), y   + i * sin(data->angl), color);
	// 	i++;
	// }
	//16776960
	draw_view(data, color);
	my_mlx_pixel_put(data, x, y, 0);
}

void	ft_get_position(double *p_x, double *p_y, char **map)
{
		int x;
	int y;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'W' || map[y][x] == 'E')
			{
				(*p_y) = ((y) * REC) + 16;
				(*p_x) = ((x) * REC) + 16;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	ft_display(t_data *data)
{
	int x;
	int y;

	y = 0;
	while (data->map[(y)])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == '1')
				draw_rectangle(data,x, y,  12632256);
			else
				draw_rectangle(data,x, y,  WHITE);
			x++;
		}
		y++;
	}
	draw_player(data,data->p_x, data->p_y,  255 << 16);
}

int	ft_strraw(char **map)
{
	int i;
	
	i = 0;
	while(map && map[i])
		i++;
	return (i);
}

int	is_wall_front(t_data *data)
{
	int i;
	int	j;
	i = ((data->p_y + 17 * sin(data->angl))/ (double)REC);
	j = ((data->p_x + 17 * cos(data->angl)) / (double)REC);
	if (data->map[i][j] == '1')
		return (1);
	return (0);
}

int	is_wall_back(t_data *data)
{
	int i;
	int	j;
	i = ((data->p_y - (6 * sin(data->angl)))/ (double)REC);
	j = ((data->p_x - (6 * cos(data->angl))) / (double)REC);
	if (data->map[i][j] == '1')
		return (1);
	return (0);
}

void	update_angle(t_data *data, int dir)
{
	if (dir == RIGHT)
	{
		data->angl += (M_PI / 180);
		if (data->angl == (M_PI * 2))
			data->angl = 0;
	}
	if (dir == LEFT)
	{
		data->angl -= (M_PI / 180);
		if (data->angl < 0)
			data->angl += data->angl;
	}
}

int	is_wall_right(t_data *data)
{
	double	new_angle;
	int i;
	int	j;

	new_angle = data->angl + (M_PI / 180) * 30;
	i = ((data->p_y + 17 * sin(new_angle))/ (double)REC);
	j = ((data->p_x + 17 * cos(new_angle)) / (double)REC);
	if (data->map[i][j] == '1')
		return (1);
	return (0);
}

int	is_wall_left(t_data *data)
{
	double	new_angle;
	int i;
	int	j;

	new_angle = data->angl - (M_PI / 180) * 30;
	i = ((data->p_y + 17 * sin(new_angle))/ (double)REC);
	j = ((data->p_x + 17 * cos(new_angle)) / (double)REC);
	if (data->map[i][j] == '1')
		return (1);
	return (0);
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
		data->p_x += (6 * cos(data->angl));
		data->p_y += (6 * sin(data->angl));
		ft_display(data);
		mlx_put_image_to_window(data->id, data->w_id, data->img, 0, 0);
	}
	if ((key == BACK || key == S) && !is_wall_back(data))
	{
		data->p_x -= (6 * cos(data->angl));
		data->p_y -= (6 * sin(data->angl));
		ft_display(data);
		mlx_put_image_to_window(data->id, data->w_id, data->img, 0, 0);
	}
	if (key == RIGHT && !is_wall_right(data)) //
	{
		update_angle(data, RIGHT);
		ft_display(data);
		mlx_put_image_to_window(data->id, data->w_id, data->img, 0, 0);
	}
	if (key == LEFT && !is_wall_left(data))//&& 
	{
		update_angle(data, LEFT);
		ft_display(data);
		mlx_put_image_to_window(data->id, data->w_id, data->img, 0, 0);
	}
	return (0);
}

void	init_angle(t_data *data)
{
	if (data->pos == 1)
	{
		data->angl = M_PI / 2;
		data->angl *= 3;	
	}
	if (data->pos == 2)
	{
		data->angl = 0;
	}
	if (data->pos == 3)
	{
		data->angl = M_PI / 2;
	}
	if (data->pos == 4)
	{
		data->angl = M_PI;
	}
}

void	ft_mlx(t_data *data)
{
	ft_get_position(&data->p_x, &data->p_y, data->map);
	init_angle(data);
	data->id = mlx_init();
	data->w_id = mlx_new_window(data->id, REC * (int)ft_strlen(data->map[0]), REC * ft_strraw(data->map), "cub3D");
	data->img = mlx_new_image(data->id, REC * (int)ft_strlen(data->map[0]), REC * ft_strraw(data->map));
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
		ft_mlx(&data);
		//print_data(data);
		//free_data(&data);
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
// 	j = data->p_x / REC;
// 	if (data->map[i][j] == '1' && (data->p_y + 6) > (i * REC))
// 		return (1);
// 	return (0);
// }

// int	is_wall_up(t_data *data)
// {
// 	int i;
// 	int	j;
// 	i = (data->p_y / REC);
// 	j = data->p_x / REC;
// 	if (data->map[i -1][j] == '1' && (data->p_y - 17) <= (i * REC))
// 		return (1);
// 	return (0);
// }