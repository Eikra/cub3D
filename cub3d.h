/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m <m@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:16:11 by iecharak          #+#    #+#             */
/*   Updated: 2023/08/15 15:25:07 by m                ###   ########.fr       */
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

char		*get_next_line(int fd);
char		*ft_read_add_to_str(char *str, int fd);
char		*add_to_str(char *str, char *buffer, int readed);
char		*ft_str_to_line(char *str);
char		*ft_clean_str(char *str);
char		*ftg_strchr(const char *s, int c);
size_t		ftg_strlen(const char *s);
char	*ftg_memcpy(char *dst, char *src, int index);

#endif