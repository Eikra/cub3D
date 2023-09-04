/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iecharak <iecharak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:16:11 by iecharak          #+#    #+#             */
/*   Updated: 2023/09/03 09:57:16 by iecharak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include <mlx.h>
#include <math.h>

# define BUFFER_SIZE 10


// #define UP_LEFT	1
// #define DOWN_LEFT 2
// #define DOWN_RIGHT 3
// #define UP_RIGHT 4


#define	VER_LEFT 1
#define VER_HOR 2
#define HOR_UP	3

//*************MACOS**********
// # define ESC 53
// # define A 0
// # define W 13
// # define S 1
// # define D 2
//  # define BACK 125
// # define ON 126
// # define LEFT 123
// # define RIGHT 124

//*************linux**********
# define ESC 65307
# define A 97
# define W 119
# define S 115
# define D 100
 # define BACK 65364
# define ON 65362
# define LEFT 65361
# define RIGHT 65363



#define MOVE 3
#define WHITE 16777215
#define YALLOW 16776960
#define	GREEN (255 << 8)



#define W_W 1280.0
#define W_H 720.0
//#define W_H (15.0 * REC)



#define H_F_V ((M_PI * 30.0) / 180.0)
#define F_V   ((M_PI * 60.0) / 180.0)




#define N_C 126378464
#define E_C 65535
#define S_C 16770029
#define W_C 16739040

#define	REC	64.0
#define MINI 10.0

# define SET "\n \t\r\v\f"
//ray_len_ver = REC - (int)data->p_x % (int)REC - 1;
typedef struct s_textures
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		w;
	int		h;
	int		direc;
}			t_textures;


typedef struct cub3d
{
	char			**buffer;
	char			**map;
	char			*path_no;
	char			*path_so;
	char			*path_we;
	char			*path_ea;
	int				map_len;
	int				f_color;
	char			*char_f;
	char			*char_c;
	int				c_color;
	int				fd;
	int				row;
	int				len;
	int				p_n;
	int				p_s;
	int				p_e;
	int				p_w;
	struct s_line	*lines;
	void			*id;
	void			*w_id;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	double			p_x;
	double			p_y;
	double			r_x;
	double			r_y;
	double			angl;
	double			ref;
	int				pos;
	int				dierc;
	int				up_dowm[2];
	int				left_right[2];
	int				rotate[2];
	int				arawdir[2];
	int				dir_keys[3];
	struct s_textures	t[4];
	int				r[2];
	
}					t_data;

typedef struct s_line
{
	char			*line;
	struct s_line	*next;
}					t_line;

typedef struct gamme_elmnt
{
	int				row;
	int				len;
	int				p_n;
	int				p_s;
	int				p_e;
	int				p_w;
}					t_map_elmnt;

typedef struct s_dirc
{
	int				n;
	int				s;
	int				w;
	int				e;
	int				f;
	int				c;
	int				i;
}					t_dirc;

/**********************PARCING********************************/

char	*get_next_line(int fd);
char	*ft_read_add_to_str(char *str, int fd);
char	*add_to_str(char *str, char *buffer, int readed);
char	*ft_str_to_line(char *str);
char	*ft_clean_str(char *str);
char	*ftg_strchr(const char *s, int c);
size_t	ftg_strlen(const char *s);
char	*ftg_memcpy(char *dst, char *src, int index);
int		ft_linesize(t_line *lst);
int		c_err(t_line *lines);
void	ft_lineadd_back(t_line **lst, t_line *new);
t_line	*ft_linenew(char *content);
int		no_err(t_line *lines);
int		so_err(t_line *lines);
int		we_err(t_line *lines);
int		ea_err(t_line *lines);
int		f_err(t_line *lines);
int		c_err(t_line *lines);
int		ft_err(char *err);
int		ft_strrncmp(char *s, char *r, int n);
int		check_map_name(char **av);
int		open_file_error(t_data *data, char *av);
int		path_error(t_data *data);
int		read_map(t_data *data);
int		get_map_line(t_data *data);
int		map_elmnt_err(t_data *data);
int		get_map_len(t_line *lines);
int		map_errors(t_data *data);
int		check_map_name(char **av);
int		color_err(t_data *data);
int		check_textures(t_data *data, char ***s);
int		get_textures(t_data *data);
char	**get_split_line(char *line);
int		ft_strraw(char **map);
int	KeyRelease(int key, t_data *data);
int	Keypress(int key, t_data *data);
int deal_keys(t_data *data);
int	player_movement(t_data *data);
int	ft_exit(void);
void	put_texture_color(t_data *data, double x, double y, t_textures *t, double texture_y);
void	draw_directions(t_data *data, double x, double y, double texture_y);
void	draw_colum(t_data *data, double ray_len, double x, double field);
void	draw_view(t_data *data);
double	distance_up_right(t_data *data, double field);
double	distance_down_right(t_data *data, double field);
double	distance_down_left(t_data *data, double field);
double	distance_up_left(t_data *data, double field);
double	get_ray_len(t_data *data, double field);
int	is_wall_front(t_data *data);
int	is_wall_back(t_data *data);
void	update_angle(t_data *data, int dir);
int	is_wall_right(t_data *data);
int	is_wall_left(t_data *data);
void draw_rectangle_mini(t_data *data, double x, double y, int color);
void	draw_miniplayer(t_data *data);
void	draw_minimap(t_data *data);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_ray(t_data *data, double angl, int color, double ray_len);
void draw_rectangle(t_data *data, double x, double y, int color);
void	draw_raycasting(t_data *data);
void	draw_rays(t_data *data);
void	free_data(t_data *data);
void	init_data(t_data *data);
void	print_data(t_data data);
int	ft_exit(void);
void	init_angle(t_data *data);
void	ft_get_position(double *p_x, double *p_y, char **map);
int	open_textures(void	*id,char *path, t_textures *t , int dirc);
void set_textures(t_data *data);

#endif