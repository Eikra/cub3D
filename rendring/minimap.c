#include "../cub3d.h"

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
		i = -1;
		while (++i < 10.0)
			my_mlx_pixel_put(data, (data->p_x / REC * MINI) + i * cos(field), (data->p_y / REC * MINI) + i * sin(field), GREEN);
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
				if (data->map[y][x] == '0' || data->map[y][x] == 'N' || data->map[y][x] == 'S' || data->map[y][x] == 'W' || data->map[y][x] == 'E')
				draw_rectangle_mini(data,x, y,  0);
			x++;
		}
		y++;
	}
	draw_miniplayer(data);
}