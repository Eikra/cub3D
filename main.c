/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m <m@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:07:07 by iecharak          #+#    #+#             */
/*   Updated: 2023/08/15 18:44:23 by m                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strrncmp(char *s, char *r, int n)
{
	int	i;
	int	j;

	i = ft_strlen(s) - 1;
	j = ft_strlen(r) - 1;
	while (n)
	{
		if (s[i] != r[j])
			return (1);
		n--;
		i--;
		j--;
	}
	return (0);
}

int check_map_name(char **av)
{
    if (ft_strrncmp(av[1], ".cub", 4))
        return (1);
    return(0);
}

int open_file_error(t_data *data, char *av)
{
    data->fd = open(av, O_RDONLY);
    if (data->fd < 0)
        return(1);
    return(0);
}

int str_content(char *str)
{
    int i;

    i = 0;
    while (str && str[i])
    {
        if (str[i] > 32)
            return (1);
        i++;
    }
    return (0);
}

t_line	*ft_linenew(char *content)
{
	t_line	*frst_list;

	frst_list = malloc(sizeof(t_line));
	if (!frst_list)
		return (NULL);
	frst_list->line = content;
	frst_list->next = NULL;
	return (frst_list);
}

t_line	*ft_linelast(t_line *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	ft_lineadd_back(t_line **lst, t_line *new)
{
	if (*lst)
		ft_linelast(*lst)->next = new;
	else
		*lst = new;
}

int	ft_linesize(t_line *lst)
{
	int		size;
	t_line	*ptr;

	size = 0;
	ptr = lst;
	while (ptr != NULL)
	{
		ptr = ptr->next;
		size++;
	}
	return (size);
}

int read_map(t_data *data)
{
    char    *str;
    int i;
    
    str = get_next_line(data->fd);
    if (!str || !str[0])
        return(1);
    data->lines = NULL;
    i = 0;
    while (str)
    {
        if (str_content(str) && i < 6)
        {
            ft_lineadd_back(&data->lines, ft_linenew(ft_strtrim(str,"\n \t\r\v\f")));
            i++;
        }
        else if ( i > 5)
        {
            if (str_content(str))
            {
                ft_lineadd_back(&data->lines, ft_linenew(ft_strrtrim(str,"\n \t\r\v\f")));
                i++;
            }
            else if(!str_content(str) && i >6)
                return(1);
        }
        free(str);
        str = get_next_line(data->fd);
    }
    if (!data->lines)
        return (1);
    return (0);
}

int NO_err(t_line  *lines)
{
    t_line  *tmp;
    int i;
    int j;

    tmp = lines;
    i = 0;
    j = 0;
    while(tmp && i < 6)
    {
        if(!ft_strncmp(tmp->line, "NO ", 3))
            j++;
        tmp = tmp->next;
        i++;
    }
    if (j != 1)
        return(1);
    return(0);
}

int SO_err(t_line  *lines)
{
    t_line  *tmp;
    int i;
    int j;

    tmp = lines;
    i = 0;
    j = 0;
    while(tmp && i < 6)
    {
        if(!ft_strncmp(tmp->line, "SO ", 3))
            j++;
        tmp = tmp->next;
        i++;
    }
    if (j != 1)
        return(1);
    return(0);
}

int WE_err(t_line  *lines)
{
    t_line  *tmp;
    int i;
    int j;

    tmp = lines;
    i = 0;
    j = 0;
    while(tmp && i < 6)
    {
        if(!ft_strncmp(tmp->line, "WE ", 3))
            j++;
        tmp = tmp->next;
        i++;
    }
    if (j != 1)
        return(1);
    return(0);
}

int EA_err(t_line  *lines)
{
    t_line  *tmp;
    int i;
    int j;

    tmp = lines;
    i = 0;
    j = 0;
    while(tmp && i < 6)
    {
        if(!ft_strncmp(tmp->line, "EA ", 3))
            j++;
        tmp = tmp->next;
        i++;
    }
    if (j != 1)
        return(1);
    return(0);
}

int F_err(t_line  *lines)
{
    t_line  *tmp;
    int i;
    int j;

    tmp = lines;
    i = 0;
    j = 0;
    while(tmp && i < 6)
    {
        if(!ft_strncmp(tmp->line, "F ", 2))
            j++;
        tmp = tmp->next;
        i++;
    }
    if (j != 1)
        return(1);
    return(0);
}

int C_err(t_line  *lines)
{
    t_line  *tmp;
    int i;
    int j;

    tmp = lines;
    i = 0;
    j = 0;
    while(tmp && i < 6)
    {
        if(!ft_strncmp(tmp->line, "C ", 2))
            j++;
        tmp = tmp->next;
        i++;
    }
    if (j != 1)
        return(1);
    return(0);
}

int get_map_len(t_line  *lines)
{
    t_line  *tmp;
    int     len;
    int     n;
    int     i;

    len = 0;
    i = 0;
    tmp = lines;
    while (tmp)
    {
        if (i > 5)
        {
            n = ft_strlen(tmp->line);
            if (len < n)
                len = n;
        }
        tmp = tmp->next;
        i++;
    }
    return (len);
}

int    get_map_line(t_data *data)
{
    t_line  *tmp;
    int     i;

    tmp = data->lines;
    i = 0;
    data->map = malloc(sizeof(char *) * (data->row + 1));
    if (!data->map)
        return (1);
    while (i++ < 6)
        tmp = tmp->next;
    i = 0;
    while (tmp)
    {
        data->map[i] = tmp->line;
        tmp = tmp->next;
        i++;
    }
    data->map[i] = NULL;
    return (0);
}

char    **get_split_line(char *line)
{
    int i;
    int j;
    int sp;
    char    *tmp;
    char    **ret;

    i = 0;
    j = 0;
    sp = 0;
    while(line && line[i])
    {
        if (line[i] <=32)
        {
            sp++;
            j++;
        }
        while(line[i] && line[i] <= 32)
            i++;
        if (line[i])
        {
            i++;
            j++;
        }
    }
    if (sp > 1)
        return (NULL);
    tmp = malloc (sizeof(char) * (j + 1));
    if (!tmp)
        return (NULL);
    i = 0;
    j = 0;
    while(line && line[i])
    {
        if (line[i] <=32)
        {
            tmp[j] = ' ';
            j++;
        }
        while(line[i] && line[i] <= 32)
            i++;
        if (line[i])
        {
            tmp[j] = line[i];
            i++;
            j++;
        }
    }
    tmp[j] = '\0';
    ret = ft_split(tmp, ' ');
    if (!ret)
        return (NULL);
    free(tmp);
    return (ret);
}

int    get_textures(t_data *data)
{
    char    **str;
    t_line  *tmp;
    int     i;
    int     j;

    tmp = data->lines;
    i = 0;
    j = 0;
    while(tmp && i < 6)
    {
        str = get_split_line(tmp->line);
        if (!str)
            return (1);
        if(!ft_strncmp(str[0], "EA", 3))
            data->path_ea = str[1];
        else if(!ft_strncmp(str[0], "NO", 3))
            data->path_no = str[1];
        else if(!ft_strncmp(str[0], "SO", 3))
            data->path_so = str[1];
        else if(!ft_strncmp(str[0], "WE", 3))
            data->path_we = str[1];
        else if(!ft_strncmp(str[0], "F", 2))
            data->char_f = str[1];
        else if(!ft_strncmp(str[0], "C", 2))
            data->char_c = str[1];
        else return (1);
        free (str[0]);
        free(str);
        tmp = tmp->next;
        i++;
    }
    return(0);
}

int map_elmnt_err(t_data *data)
{
    data->map_len = get_map_len(data->lines);
    data->row = ft_linesize(data->lines) - 6;
    if (get_map_line(data))
        return (1);
    if (get_textures(data))
        return (1);
    return(0);
}

int path_error(t_data *data)
{
    if (NO_err(data->lines) || SO_err(data->lines) || WE_err(data->lines) || EA_err(data->lines) || F_err(data->lines) || C_err(data->lines))
        return (1);
    if (map_elmnt_err(data))
        return (1);
    return(0);
}

int char_err(char **map)
{
    int i;
    int j;

    i = 0;
    
    while (map && map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] != ' ' && map[i][j] != '0' && map[i][j] != '1'
                && map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'E' && map[i][j] != 'W')
                return(1);
        j++;
        }
        i++;
    }
    return (0);
}

int char_err2(t_data *data)
{
    int i;
    int j;

    i = 0;
    
    while (data->map && data->map[i])
    {
        j = 0;
        while (data->map[i][j])
        {
            if (data->map[i][j] == 'N')
                data->p_n++;
            if (data->map[i][j] == 'S')
                data->p_s++;
            if (data->map[i][j] == 'E')
                data->p_e++;
            if (data->map[i][j] == 'W')
                data->p_w++;
        j++;
        }
        i++;
    }
    if ((data->p_n + data->p_s + data->p_e + data->p_w) != 1)
        return (1);
    return (0);
}

int border_err(char **map)
{
    int i;
    int j;

    i = 0;
    
    while (map && map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == '0')
            {
                if (!i || !map[i + 1] || !j || !map[i][j + 1])
                    return (1);
                if ((map[i + 1] && map[i + 1][j] == ' ') || map[i - 1][j] == ' ' || map[i][j + 1] == ' ' || map[i][j - 1] == ' ')
                    return (1);
            }
            // if ((!j && map[i][j] == '0') || (map[i][j] == '0' && !map[i][j + 1]) || (!i && map[i][j] == '0')
            //     || (map[i][j] == '0' && !map[i + 1]) || (map[i][j] == '0' && (int)ft_strlen(map[i + 1]) <=j))
            //     return (1);
            // if ((map[i][j] == '0' && map[i][j + 1] == ' ')
            //     || (map[i][j] == '0' && map[i + 1][j] == ' ') || (i && map[i][j] == '0' && (int)ft_strlen(map[i - 1]) <=j))
            //     return (1);
        j++;
        }
        i++;
    }
    return (0);
}

int map_errors(t_data *data)
{
    if(ft_linesize(data->lines) <= 8)
        return(1);
    if(path_error(data))
        return(1);
    if (char_err(data->map))
        return (1);
    if (char_err2(data))
        return (1);
    if (border_err(data->map))
        return (1);
    return(0);
}

void    free_data(t_data *data)
{
    t_line  *tmp;

    while(data->lines)
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
}

void    init_data(t_data *data)
{
    data->buffer = NULL;
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
}

int main(int ac, char **av)
{
    t_data  data;

    init_data(&data);
    if (ac == 2)
    {
        if(check_map_name(av))
            return(ft_putstr_fd("error\n",2), 0);
        if(open_file_error(&data, av[1]))
            return(ft_putstr_fd("error\n",2), 0);
        if (read_map(&data))
            return(ft_putstr_fd("error\n",2), 0);
        if (map_errors(&data))
          ft_putstr_fd("error\n",2);
    }
    else
        ft_putstr_fd("error\n",2);
    // if (data.path_no)
    // printf("%s\n", data.path_no);
    // if (data.path_so)
    // printf("%s\n", data.path_so);
    // if (data.path_we)
    // printf("%s\n", data.path_we);
    // if (data.path_ea)
    // printf("%s\n", data.path_ea);
    // if (data.char_f)
    // printf("%s\n", data.char_f);
    // if (data.char_c)
    // printf("%s\n", data.char_c);
    // int i = 0;
    // while (data.map && data.map[i])
    // {
    //     printf("%s\n", data.map[i]);
    //     i++;
    // }
    free_data(&data);
    //system("leaks cub3D");
    return (0);
}