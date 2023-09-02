#include "../cub3d.h"

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