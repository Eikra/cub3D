/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iecharak <iecharak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:16:11 by iecharak          #+#    #+#             */
/*   Updated: 2023/08/30 21:48:50 by iecharak         ###   ########.fr       */
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
#define	RED 255 << 8



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

# define SET "\n \t\r\v\f"
//ray_len_ver = REC - (int)data->p_x % (int)REC - 1;
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

#endif