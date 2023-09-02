#include "../cub3d.h"


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

	i = 0;
	while (i < ray_len)
	{
		my_mlx_pixel_put(data, data->p_x + i * cos(angl), data->p_y + i * sin(angl), color);
		i++;
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

void	draw_raycasting(t_data *data)
{
	double	ray_angl;
	double	ray_len;
	double	deg_by_pex;
	double		x;

	ray_angl = data->angl - (H_F_V);
	deg_by_pex = (F_V) / (W_W);
	x = 0;
	while (x < W_W)
	{
		if (ray_angl > (M_PI * 2.0))
			ray_angl = ray_angl - (M_PI * 2.0);
		if (ray_angl < 0.0)
			ray_angl = ray_angl + (M_PI * 2.0);
		ray_len = get_ray_len(data, ray_angl);
		if(data->r[1] == 1)
			draw_ray(data, ray_angl, GREEN, ray_len);
		else draw_ray(data, ray_angl, YALLOW, ray_len);
		ray_angl += deg_by_pex;
		x++;
	}
}

void	draw_rays(t_data *data)
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
				draw_rectangle(data,x, y,  0);
			x++;
		}
		y++;
	}
	draw_raycasting(data);
}