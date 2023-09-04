#include "../cub3d.h"

int	is_wall_intersection(int x, int y, char **map)
{
	if(y >= 0 && y < (ft_strraw(map) * REC) && x >= 0 && x < (ft_strlen (map[(int)(y / REC)]) * REC)
		&& (map[(int)(y / REC)][(int)(x / REC)] == '0' || map[(int)(y / REC)][(int)(x / REC)] == 'N'
		|| map[(int)(y / REC)][(int)(x / REC)] == 'S' || map[(int)(y / REC)][(int)(x / REC)] == 'W'
		|| map[(int)(y / REC)][(int)(x / REC)] == 'E'))
		return (0);
	return (1);
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
	while (!is_wall_intersection(x_v + 1, y_v, data->map))
	{
		x_v = floor(data->p_x / REC)* REC + REC * k;
		y_v = data->p_y - fabs(tan(field) * (x_v - data->p_x));
		k++;
	}
	ray_len_ver = sqrt(pow((x_v - data->p_x),2) + pow((y_v - data->p_y), 2));
	data->r[0] = y_v;
	data->r[1] = 1;
	k = 0;
	y_h = floor(data->p_y / REC) * REC - REC * k;
	x_h = fabs(y_h - data->p_y) / fabs(tan(field)) + data->p_x;
	while (!is_wall_intersection(x_h , y_h - 1, data->map))
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
	data->r[1] = 2;
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
	while (!is_wall_intersection(x_v + 1, y_v, data->map))//&& data->map[(int)(y_v + 1) /REC][(int)((x_v - 1) / REC)] != '1'
	{
		x_v = floor(data->p_x / REC)* REC + REC * k;
		y_v = data->p_y + fabs(tan(field) * (x_v - data->p_x));
		k++;
	}
	ray_len_ver = sqrt(pow((x_v - data->p_x),2) + pow((y_v - data->p_y), 2));
	data->r[0] = y_v;
	data->r[1] = 1;
	data->dierc = 2;
	k = 1;
	y_h = floor(data->p_y / REC) * REC + REC * k;
	x_h = fabs(y_h - data->p_y) / fabs(tan(field)) + data->p_x;
	while (!is_wall_intersection(x_h, y_h + 1, data->map))
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
	data->r[1] = 2;
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
	while (!is_wall_intersection(x_v - 1, y_v, data->map))
	{
		x_v = floor(data->p_x / REC)* REC - REC * k;
		y_v = data->p_y + fabs(tan(field) * (x_v - data->p_x));
		k++;
	}
	ray_len_ver = sqrt(pow((x_v - data->p_x),2) + pow((y_v - data->p_y), 2));
	data->dierc = 4;
	data->r[0] = y_v;
	data->r[1] = 1;
	k = 1;
	y_h = floor(data->p_y / REC) * REC + REC * k;
	x_h = data->p_x - fabs(y_h - data->p_y) / fabs(tan(field));
	while (!is_wall_intersection(x_h, y_h + 1, data->map))
	{
		y_h = floor(data->p_y / REC) * REC + REC * k;
		x_h = data->p_x - fabs(y_h - data->p_y) / fabs(tan(field));
		k++;
	}
	//if(y_h + 1 < (ft_strraw(data->map) * REC) && y_h >= 0 && x_h >= 0 && x_h < ft_strlen (data->map[(int)((y_h + 1) / REC)]) * REC)
	//printf("%c\n",data->map[(int)((y_h + 1) /REC)][(int)((x_h) / REC)]);
	ray_len_hor = sqrt(pow((x_h - data->p_x),2) + pow((y_h - data->p_y), 2));
	//printf("vertical = %f, horisintal = %f\n",ray_len_ver, ray_len_hor);
	if(ray_len_ver < ray_len_hor)
		return(ray_len_ver);
	data->dierc = 3;
	data->r[0] = x_h;
	data->r[1] = 2;
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
	while (!is_wall_intersection(x_v - 1, y_v, data->map))
	{
		x_v = floor(data->p_x / REC)* REC - REC * k;
		y_v = data->p_y - fabs(tan(field) * (x_v - data->p_x));
		k++;
	}
	ray_len_ver = sqrt(pow((x_v - data->p_x),2) + pow((y_v - data->p_y), 2));
	data->dierc = 4;
	data->r[0] = y_v;
	data->r[1] = 1;
	k = 1;
	y_h = floor(data->p_y / REC) * REC;
	x_h = data->p_x - fabs(y_h - data->p_y) / fabs(tan(field));
	while (!is_wall_intersection(x_h, y_h - 1, data->map))
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
	data->r[1] = 2;
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