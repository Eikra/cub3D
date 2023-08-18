/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iecharak <iecharak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:16:11 by iecharak          #+#    #+#             */
/*   Updated: 2023/08/18 20:07:55 by iecharak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "libft/libft.h"
//#include "minilibx/mlx.h"

# define BUFFER_SIZE 10

typedef struct cub3d
{
    char    **buffer;
    char    **map;
    char    *path_no;
    char    *path_so;
    char    *path_we;
    char    *path_ea;
    int     map_len;
    int     f_color;
    char    *char_f;
    char    *char_c;
    int     c_color;
    int     fd;
    int		row;
	int		len;
    int     p_n;
    int     p_s;
    int     p_e;
    int     p_w;
    struct s_line   *lines;
}   t_data;

typedef struct s_line
{
    char    *line;
    struct s_line *next;
}   t_line;

typedef struct gamme_elmnt
{
	int		row;
	int		len;
    int     p_n;
    int     p_s;
    int     p_e;
    int     p_w;
}			map_elmnt;

typedef struct  s_dirc
{
    int n;
    int s;
    int w;
    int e;
    int f;
    int c;
    int i;
}  t_dirc;


/**********************PARCING********************************/

char		*get_next_line(int fd);
char		*ft_read_add_to_str(char *str, int fd);
char		*add_to_str(char *str, char *buffer, int readed);
char		*ft_str_to_line(char *str);
char		*ft_clean_str(char *str);
char		*ftg_strchr(const char *s, int c);
size_t		ftg_strlen(const char *s);
char		*ftg_memcpy(char *dst, char *src, int index);
int	ft_linesize(t_line *lst);
int C_err(t_line  *lines);
void	ft_lineadd_back(t_line **lst, t_line *new);
t_line	*ft_linenew(char *content);
int NO_err(t_line  *lines);
int SO_err(t_line  *lines);
int WE_err(t_line  *lines);
int EA_err(t_line  *lines);
int F_err(t_line  *lines);
int C_err(t_line  *lines);
int ft_err(char *err);
int	ft_strrncmp(char *s, char *r, int n);
int check_map_name(char **av);
int open_file_error(t_data *data, char *av);
int path_error(t_data *data);
int read_map(t_data *data);
int    get_map_line(t_data *data);
int map_elmnt_err(t_data *data);
int get_map_len(t_line  *lines);
int map_errors(t_data *data);
int check_map_name(char **av);


#endif