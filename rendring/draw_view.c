#include "../cub3d.h"

void	put_texture_color(t_data *data, double x, double y, t_textures *t, double texture_y)
{
	char	*src;
	int		xt;
	int		yt;
	int		color;

	xt = floor(data->r[0] % (int)REC);
	xt = floor(((double)xt / REC) * (double)t->w);
	yt = floor(texture_y);
	src = t->addr + (yt * t->line_length + xt * (t->bits_per_pixel / 8));
	color = *(unsigned int*)src;
	my_mlx_pixel_put(data, x, y, color);
}

void	draw_directions(t_data *data, double x, double y, double texture_y)
{
	if (data->dierc == 1)
		put_texture_color(data, x, y, &data->t[0], texture_y);
	else if (data->dierc == 2)
		put_texture_color(data, x, y, &data->t[1], texture_y);
	else if (data->dierc == 3)
		put_texture_color(data, x, y, &data->t[2], texture_y);
	else if (data->dierc == 4)
		put_texture_color(data, x, y, &data->t[3], texture_y);
	//(void)field;
}

void	draw_colum(t_data *data, double ray_len, double x, double field)
{
	double	w_start;
	double	w_end;
	double	wall_len;
	double		y;
	double		j;

	wall_len = (W_H * ( 64)) / (ray_len);
	w_start = W_H / 2.0 - wall_len / 2.0;
	w_end = W_H / 2.0 + wall_len / 2.0;
	y = 0;
	while (y < w_start)
	{
		my_mlx_pixel_put(data, x, y, WHITE);
		y++;
	}
	j = 0;

	if(w_start < 0 && data->dierc == 1)
		j = (data->t[0].h / wall_len) * fabs(w_start);
	if(w_start < 0 && data->dierc == 2)
		j = (data->t[1].h / wall_len) * fabs(w_start);
	if(w_start < 0 && data->dierc == 3)
		j = (data->t[2].h / wall_len) * fabs(w_start);
	if(w_start < 0 && data->dierc == 4)
		j = (data->t[3].h / wall_len) * fabs(w_start);	



	while (y <  w_end && y < (double)W_H)
	{
		if (data->dierc == 1)
		{
			put_texture_color(data, x, y, &data->t[0], j);
			j = j + (data->t[0].h / wall_len);
		}

		else if (data->dierc == 2)
		{
			put_texture_color(data, x, y, &data->t[1], j);
			j = j + (data->t[1].h / wall_len);
		}

		else if (data->dierc == 3)
		{
			put_texture_color(data, x, y, &data->t[2], j);
			j = j + (data->t[2].h / wall_len);
		}
			
		else if (data->dierc == 4)
		{
			put_texture_color(data, x, y, &data->t[3], j);
			j = j + (data->t[3].h / wall_len);
		}
			
		y++;
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
	while (x < W_W)
	{
		if (ray_angl > (M_PI * 2.0))
			ray_angl = ray_angl - (M_PI * 2.0);
		if (ray_angl < 0.0)
			ray_angl = ray_angl + (M_PI * 2.0);
		ray_len = get_ray_len(data, ray_angl);
		draw_colum(data,fabs(cos(data->angl - ray_angl) * ray_len), x, ray_angl);
		ray_angl += deg_by_pex;
		x++;
	}
}