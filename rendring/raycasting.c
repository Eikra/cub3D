#include "../cub3d.h"
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
	data->r[1] = 1;
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
	while (y_v + REC < (ft_strraw(data->map) * REC) && y_v >= 0 && x_v + REC < ft_strlen (data->map[(int)((y_v + 1) / REC)]) * REC && x_v >= 0 && (data->map[(int)(y_v /REC)][(int)((x_v + 1) / REC)] != '1') )//&& data->map[(int)(y_v + 1) /REC][(int)((x_v - 1) / REC)] != '1'
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
	while (y_v + REC < (ft_strraw(data->map) * REC) && y_v >= 0 && x_v - 1 < ft_strlen (data->map[(int)(y_v / REC)]) * REC && (data->map[(int)(y_v /REC)][(int)((x_v - 1) / REC)] != '1'))
	{
		x_v = floor(data->p_x / REC)* REC - REC * k;
		y_v = data->p_y + fabs(tan(field) * (x_v - data->p_x));
		k++;
	}
	ray_len_ver = sqrt(pow((x_v - data->p_x),2) + pow((y_v - data->p_y), 2));
	data->dierc = 4;
	data->r[0] = y_v;
	data->r[1] = 1;
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
	while (x_v < W_W && x_v - 1 >= 0 && y_v < W_H && y_v >= 0 && (data->map[(int)((y_v) /REC)][(int)((x_v - 1) / REC)] != '1'))
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