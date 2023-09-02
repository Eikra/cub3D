#include "../cub3d.h"

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