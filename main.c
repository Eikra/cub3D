/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m <m@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:07:07 by iecharak          #+#    #+#             */
/*   Updated: 2023/09/01 22:28:17 by m                ###   ########.fr       */
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
	exit(0);
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
	data->dierc = 0;
	data->r[0] = 0;
	data->r[1] = 0;
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
	if( y + 1 >= W_H || x + 1 >= W_W || y < 0 || x < 0)
		return;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_ray(t_data *data, double angl, int color, double ray_len)
{
	double i;

	i = ray_len - 1.0;
	while (i < ray_len)
	{
		my_mlx_pixel_put(data, data->p_x + i * cos(angl), data->p_y + i * sin(angl), color);
		i++;
	}
}

double	distance_up_right(t_data *data, double field)
{
	double	ray_len_ver;
	double	ray_len_hor;
	double	x_v;
	double	y_v;
	double	x_h;
	double	y_h;
	double	k;
	k = 1;
	x_v = floor(data->p_x / REC)* REC + REC * k;
	y_v = data->p_y - fabs(tan(field) * (x_v - data->p_x));
	while (x_v < W_W && x_v >= 0 && y_v < W_H && y_v >= 0 && data->map[(int)(y_v / REC)][(int)((x_v + 1) / REC)] != '1')
	{
		x_v = floor(data->p_x / REC)* REC + REC * k;
		y_v = data->p_y - fabs(tan(field) * (x_v - data->p_x));
		k++;
	}
	ray_len_ver = sqrt(pow((x_v - data->p_x),2) + pow((y_v - data->p_y), 2));
	data->r[0] = y_v;
	k = 0;
	y_h = floor(data->p_y / REC) * REC - REC * k;
	x_h = fabs(y_h - data->p_y) / fabs(tan(field)) + data->p_x;
	while (x_h < W_W && x_h >= 0 && y_h < W_H && y_h >= 0 && y_h - REC >= 0.0 && data->map[(int)((y_h - 1) /REC) ][(int)(x_h / REC)] != '1')
	{
		y_h = floor(data->p_y / REC) * REC - REC * k;
		x_h = fabs(y_h - data->p_y) / fabs(tan(field)) + data->p_x;
		k++;
	}
	ray_len_hor = sqrt(pow((x_h - data->p_x),2) + pow((y_h - data->p_y), 2));
	data->dierc = 2;
	if(ray_len_ver < ray_len_hor)
		return(ray_len_ver);
	data->dierc = 1;
	data->r[0] = x_h;
	return(ray_len_hor);
}

double	distance_down_right(t_data *data, double field)
{
	double	ray_len_ver;
	double	ray_len_hor;
	double	x_v;
	double	y_v;
	double	x_h;
	double	y_h;
	double	k;
	
	k = 1;
	x_v = floor(data->p_x / REC)* REC + REC * k;
	y_v = data->p_y + fabs(tan(field) * (x_v - data->p_x));
	while (y_v + REC < (ft_strraw(data->map) * REC) && y_v >= 0 && x_v + REC < ft_strlen (data->map[(int)((y_v + 1) / REC)]) * REC && x_v >= 0 && (data->map[(int)(y_v /REC)][(int)((x_v + 1) / REC)] != '1') )//&& data->map[(int)(y_v + 1) /REC][(int)((x_v - 1) / REC)] != '1'
	{
		x_v = floor(data->p_x / REC)* REC + REC * k;
		y_v = data->p_y + fabs(tan(field) * (x_v - data->p_x));
		k++;
	}
	ray_len_ver = sqrt(pow((x_v - data->p_x),2) + pow((y_v - data->p_y), 2));
	data->r[0] = y_v;
	data->dierc = 2;
	k = 1;
	y_h = floor(data->p_y / REC) * REC + REC * k;
	x_h = fabs(y_h - data->p_y) / fabs(tan(field)) + data->p_x;
	while (y_h + REC < (ft_strraw(data->map) * REC) && y_h >= 0 && x_h + REC < ft_strlen (data->map[(int)((y_h + 1) /REC)]) * REC && x_h >= 0 && data->map[(int)(((y_h + 1) /REC))][(int)((x_h) / REC)] != '1')
	{
		y_h = floor(data->p_y / REC) * REC + REC * k;
		x_h = fabs(y_h - data->p_y) / fabs(tan(field)) + data->p_x;
		k++;
	}
	ray_len_hor = sqrt(pow((x_h - data->p_x),2) + pow((y_h - data->p_y), 2));
	
	if(ray_len_ver < ray_len_hor)
		return(ray_len_ver);
	data->dierc = 3;
	data->r[0] = x_h;
	return(ray_len_hor);
}

double	distance_down_left(t_data *data, double field)
{
	double	ray_len_ver;
	double	ray_len_hor;
	double	x_v;
	double	y_v;
	double	x_h;
	double	y_h;
	double	k;

	k = 0;
	
	x_v = floor(data->p_x / REC)* REC - REC * k;
	y_v = data->p_y + fabs(tan(field) * (x_v - data->p_x));
	while (y_v + REC < (ft_strraw(data->map) * REC) && y_v >= 0 && x_v - 1 < ft_strlen (data->map[(int)(y_v / REC)]) * REC && (data->map[(int)(y_v /REC)][(int)((x_v - 1) / REC)] != '1'))
	{
		x_v = floor(data->p_x / REC)* REC - REC * k;
		y_v = data->p_y + fabs(tan(field) * (x_v - data->p_x));
		k++;
	}
	ray_len_ver = sqrt(pow((x_v - data->p_x),2) + pow((y_v - data->p_y), 2));
	data->dierc = 4;
	data->r[0] = y_v;
	k = 0;
	y_h = floor(data->p_y / REC) * REC + REC * k;
	x_h = data->p_x - fabs(y_h - data->p_y) / fabs(tan(field));
	while (y_h + 1 + REC < (ft_strraw(data->map) * REC) && y_h >= 0 && x_h >= 0 && x_h + REC < ft_strlen (data->map[(int)((y_h + 1) / REC)]) * REC  && data->map[(int)((y_h + 1) /REC)][(int)((x_h) / REC)] != '1')
	{
		y_h = floor(data->p_y / REC) * REC + REC * k;
		x_h = data->p_x - fabs(y_h - data->p_y) / fabs(tan(field));
		k++;
	}
	ray_len_hor = sqrt(pow((x_h - data->p_x),2) + pow((y_h - data->p_y), 2));
	printf("vertical = %f, horisintal = %f\n",ray_len_ver, ray_len_hor);
	if(ray_len_ver < ray_len_hor)
		return(ray_len_ver);
	data->dierc = 3;
	data->r[0] = x_h;
	return(ray_len_hor);
}

double	distance_up_left(t_data *data, double field)
{
	double	ray_len_ver;
	double	ray_len_hor;
	double	x_v;
	double	y_v;
	double	x_h;
	double	y_h;
	double	k;

	k = 1;
	x_v = floor(data->p_x / REC)* REC;
	y_v = data->p_y - fabs(tan(field) * (x_v - data->p_x));
	while (x_v < W_W && x_v - 1 >= 0 && y_v < W_H && y_v >= 0 && (data->map[(int)((y_v) /REC)][(int)((x_v - 1) / REC)] != '1'))
	{
		x_v = floor(data->p_x / REC)* REC - REC * k;
		y_v = data->p_y - fabs(tan(field) * (x_v - data->p_x));
		k++;
	}
	ray_len_ver = sqrt(pow((x_v - data->p_x),2) + pow((y_v - data->p_y), 2));
	data->dierc = 4;
	data->r[0] = y_v;
	k = 1;
	y_h = floor(data->p_y / REC) * REC;
	x_h = data->p_x - fabs(y_h - data->p_y) / fabs(tan(field));
	while (x_h < W_W && x_h >= 0 && y_h - 1 >= 0  && y_h < W_H  && data->map[(int)((y_h - 1) /REC)][(int)(x_h / REC)] != '1')
	{
		y_h = floor(data->p_y / REC) * REC - REC * k;
		x_h = data->p_x - fabs(y_h - data->p_y) / fabs(tan(field));
		k++;
	}
	ray_len_hor = sqrt(pow((x_h - data->p_x),2) + pow((y_h - data->p_y), 2));
	//printf("vertical = %f, horisintal = %f\n",ray_len_ver, ray_len_hor);
	if(ray_len_ver < ray_len_hor)
		return( ray_len_ver);//,
	data->dierc = 1;
	data->r[0] = x_h;
	//printf("horisintal\n");
	return(ray_len_hor);
}

double	get_ray_len(t_data *data, double field)
{
	if (field > ((3.0 * M_PI) / 2.0) && field < (2.0 * M_PI))
		return(distance_up_right(data, field));
	if (field > 0.0 && field < (M_PI / 2.0))
		return(distance_down_right(data, field));
	if (field > (M_PI / 2.0) && field < M_PI)
		return(distance_down_left(data, field));
	if (field > M_PI && field < ((3.0 * M_PI) / 2.0))
		return(distance_up_left(data, field));
	return (0);
}

void	put_texture_color(t_data *data, double x, double y, t_textures *t, double field)
{
	char	*src;
	int		xt;
	int		yt;
	int		color;

	xt = floor(data->r[0] % (int)REC);
	yt = floor(field);
	src = t->addr + (yt * t->line_length + xt * (t->bits_per_pixel / 8));
	color = *(unsigned int*)src;
	my_mlx_pixel_put(data, x, y, color);
	(void ) (field);
}

void	draw_directions(t_data *data, double x, double y, double field)
{
	// if (data->dierc == 1)
	// 	my_mlx_pixel_put(data, x, y, N_C);
	// else if (data->dierc == 2)
	// 	my_mlx_pixel_put(data, x, y, W_C);
	// else if (data->dierc == 3)
	// 	my_mlx_pixel_put(data, x, y, S_C);
	// else if (data->dierc == 4)
	// 	my_mlx_pixel_put(data, x, y, E_C);
	if (data->dierc == 1)
		put_texture_color(data, x, y, &data->t[0], field);
	else if (data->dierc == 2)
		put_texture_color(data, x, y, &data->t[1], field);
	else if (data->dierc == 3)
		put_texture_color(data, x, y, &data->t[2], field);
	else if (data->dierc == 4)
		put_texture_color(data, x, y, &data->t[3], field);
	(void)field;
}

void	draw_colum(t_data *data, double ray_len, double x, double field)
{
	double	w_start;
	double	w_end;
	double	wall_len;
	double		y;
	double		j;

	wall_len = (W_H * ( REC)) / (ray_len);
	w_start = W_H / 2.0 - wall_len / 2.0;
	w_end = W_H / 2.0 + wall_len / 2.0;
	y = 0;
	while (y < w_start)
	{
		my_mlx_pixel_put(data, x, y, WHITE);
		y++;
	}
	j = 0;
	// while ( w_start < 0)
	// {
	// 	j = j +  REC / wall_len;
	// 	w_start++;
	// }
	if(w_start < 0)
		j = (REC / wall_len) * fabs(w_start);
	while (y <  w_end && y < (double)W_H)
	{
		draw_directions(data, x, y, j);
		y++;
		j = j +  REC / wall_len;
	}
	while (y < (double)W_H)
	{
		my_mlx_pixel_put(data, x, y, (216 << 16) + (191 << 8) + 216);
		y++;
	}
	data->dierc = 0;
	(void)field;
}

void	draw_view(t_data *data)
{
	double	ray_angl;
	double	ray_len;
	double	deg_by_pex;
	double		x;

	ray_angl = data->angl - (H_F_V);
	deg_by_pex = (F_V) / (W_W);
	x = 0;
	//printf("=====================\n");
	while (x < W_W)
	{
		if (ray_angl > (M_PI * 2.0))
			ray_angl = ray_angl - (M_PI * 2.0);
		if (ray_angl < 0.0)
			ray_angl = ray_angl + (M_PI * 2.0);
		ray_len = get_ray_len(data, ray_angl);
		//printf("x = %d      y = %d\n", data->r[0], data->r[1]);
		printf("x = %f, ", x);
		draw_colum(data,fabs(cos(data->angl - ray_angl) * ray_len), x, ray_angl);
		// draw_colum(data,fabs(ray_len), x, ray_angl);
		//draw_ray(data, ray_angl, RED, ray_len);
		ray_angl += deg_by_pex;
		x++;
	}
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
				(*p_y) = (double)(((y) * REC) + REC / 2);
				(*p_x) = (double)(((x) * REC) + REC / 2);
				return ;
			}
			x++;
		}
		y++;
	}
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
			if (!j || !i)
			my_mlx_pixel_put(data, (x * REC) + j, (y * REC) + i,255);
			else 
			my_mlx_pixel_put(data, (x * REC) + j, (y * REC) + i,color);
			j++;
		}
		i++;
	}
}

void draw_rectangle_mini(t_data *data, double x, double y, int color)
{
	double i;
	double j;

	i = 0;
	while (i < MINI)
	{
		j = 0;
		while (j < MINI)
		{
			if (!j || !i)
			my_mlx_pixel_put(data, (x * MINI) + j, (y * MINI) + i,255);
			else 
			my_mlx_pixel_put(data, (x * MINI) + j, (y * MINI) + i,color);
			j++;
		}
		i++;
	}
}

// void	draw_miniplayer(t_data *data, double angl, int color, double ray_len)
// {
// 	double i;

// 	i = 0;
// 	while (i < ray_len)
// 	{
// 		my_mlx_pixel_put(data, data->p_x + i * cos(angl), data->p_y + i * sin(angl), color);
// 		i++;
// 	}
// }

void	draw_miniplayer(t_data *data)
{
	double	field;
	//double	ray_len;
	double	deg_by_pex;
	double	x;
	double	i;

	field = data->angl - (H_F_V);
	deg_by_pex = (F_V) / (W_W);
	x = 0;
	
	while (x < W_W)
	{
		if (field > (M_PI * 2.0))
			field = field - (M_PI * 2.0);
		if (field < 0.0)
			field = field + (M_PI * 2.0);
		//ray_len = get_ray_len(data, field);
		i = -1;
		while (++i < 20.0)
			my_mlx_pixel_put(data, (data->p_x / REC * MINI) + i * cos(field), (data->p_y / REC * MINI) + i * sin(field), RED);
		field += deg_by_pex;
		x++;
	}
}

void	draw_minimap(t_data *data)
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
				draw_rectangle_mini(data,x, y,  12632256);
			else
				draw_rectangle_mini(data,x, y,  0);
			x++;
		}
		y++;
	}
	draw_miniplayer(data);
}

void	ft_display(t_data *data)
{
	draw_view(data);
	draw_minimap(data);return;
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
				draw_rectangle(data,x, y,  0);
			x++;
		}
		y++;
	}
	draw_view(data);
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
	double i;
	double	j;
	i = data->p_y + 38.0 * sin(data->angl);
	j = data->p_x + 38.0 * cos(data->angl);
	if (data->map[(int)(i / REC)][(int)(j / REC)] == '1')
		return (1);
	if (data->map[(int)(i / REC)][(int)(j / REC)] == '0' && data->p_y > i && data->p_x < j && data->map[(int)(i / REC)][(int)(j - 1)] == '1' && data->map[(int)((i + 1) / REC)][(int)(j / REC)] == '1')
		return (1);
	if (data->map[(int)(i / REC)][(int)(j / REC)] == '0' && data->p_y > i && data->p_x > j && data->map[(int)((i + 1) / REC)][(int)(j / REC)] == '1' && data->map[(int)(i / REC)][(int)((j + 1) / REC)] == '1')
		return (1);
	if (data->map[(int)(i / REC)][(int)(j / REC)] == '0' && data->p_y < i && data->p_x < j && data->map[(int)((i - 1) / REC)][(int)(j / REC)] == '1' && data->map[(int)(i / REC)][(int)((j - 1) / REC)] == '1')
		return (1);
	if (data->map[(int)(i / REC)][(int)(j / REC)] == '0' && data->p_y < i && data->p_x > j && data->map[(int)((i - 1) / REC)][(int)(j / REC)] == '1' && data->map[(int)(i / REC)][(int)((j + 1) / REC)] == '1')
		return (1);
	return (0);
}

int	is_wall_back(t_data *data)
{
	double i;
	double	j;

	i = data->p_y - (32.0 * sin(data->angl));
	j = data->p_x - (32.0 * cos(data->angl));
	if (data->map[(int)(i / REC)][(int)(j / REC)] == '1')
		return (1);
	if (data->map[(int)(i / REC)][(int)(j / REC)] == '0' && data->p_y > i && data->p_x < j && data->map[(int)(i / REC)][(int)(j - 1)] == '1' && data->map[(int)((i + 1) / REC)][(int)(j / REC)] == '1')
		return (1);
	if (data->map[(int)(i / REC)][(int)(j / REC)] == '0' && data->p_y > i && data->p_x > j && data->map[(int)((i + 1) / REC)][(int)(j / REC)] == '1' && data->map[(int)(i / REC)][(int)((j + 1) / REC)] == '1')
		return (1);
	if (data->map[(int)(i / REC)][(int)(j / REC)] == '0' && data->p_y < i && data->p_x < j && data->map[(int)((i - 1) / REC)][(int)(j / REC)] == '1' && data->map[(int)(i / REC)][(int)((j - 1) / REC)] == '1')
		return (1);
	if (data->map[(int)(i / REC)][(int)(j / REC)] == '0' && data->p_y < i && data->p_x > j && data->map[(int)((i - 1) / REC)][(int)(j / REC)] == '1' && data->map[(int)(i / REC)][(int)((j + 1) / REC)] == '1')
		return (1);
	return (0);
}

void	update_angle(t_data *data, int dir)
{
	if (dir == RIGHT)
	{
		data->angl += (M_PI / 180.0 * 3.0);
		if (data->angl > (M_PI * 2.0))
			data->angl = data->angl - (M_PI * 2.0);
	}
	if (dir == LEFT)
	{
		data->angl -= (M_PI / 180.0 * 3.0);
		if (data->angl <= 0.0)
			data->angl = data->angl + (M_PI * 2.0);
	}
}

int	is_wall_right(t_data *data)
{
	double	new_angle;
	int i;
	int	j;

	new_angle = data->angl + (M_PI / (double)180) * (double)30;
	i = ((data->p_y + (double)17 * sin(new_angle))/ (double)REC);
	j = ((data->p_x + (double)17 * cos(new_angle)) / (double)REC);
	if (data->map[i][j] == '1')
		return (1);
	return (0);
}

int	is_wall_left(t_data *data)
{
	double	new_angle;
	int i;
	int	j;

	new_angle = data->angl - ((M_PI * (double)30) / (double)180) ;
	i = ((data->p_y + (double)17 * sin(new_angle))/ (double)REC);
	j = ((data->p_x + (double)17 * cos(new_angle)) / (double)REC);
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

void	init_angle(t_data *data)
{
	if (data->pos == 1)
	{
		data->angl = M_PI / (double)2;
		data->angl *= (double)3;	
	}
	if (data->pos == 2)
	{
		data->angl = (double)0;
	}
	if (data->pos == 3)
	{
		data->angl = M_PI / (double)2;
	}
	if (data->pos == 4)
	{
		data->angl = M_PI;
	}
}

int	open_textures(void	*id,char *path, t_textures *t , int dirc)
{
		t->img =  mlx_xpm_file_to_image(id, path, &t->w, &t->h);
		t->direc = dirc;
		if (!t->img)
			return (ft_err("corrupted xpm"));
		t->addr = mlx_get_data_addr(t->img, &t->bits_per_pixel, &t->line_length,
								&t->endian);
		return (0);
}

void set_textures(t_data *data)
{
	if(open_textures(data->id,data->path_no, &data->t[0], 1))
		free_data(data);
	if(open_textures(data->id,data->path_ea, &data->t[1], 2))
		free_data(data);
	if(open_textures(data->id,data->path_so, &data->t[2], 3))
		free_data(data);
	if(open_textures(data->id,data->path_we, &data->t[3], 4))
		free_data(data);
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