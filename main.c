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
    return (0);
}

char    **get_split_line(char *line)
{
    int i;
    int j;
    char    *tmp;

    i = 0;
    j = 0;
    while(line && line[i])
    {
        while(line[i] && line[i] < 32)
            i++;
        if (line[i])
            i++;
    }


}

int    get_textures(t_data *data)
{
    char    **tmp;
    int     i;
    int     j;

    tmp = data->lines;
    i = 0;
    j = 0;
    while(tmp && i < 6)
    {
        tmp = get_split_line(tmp->line);
        if(!ft_strncmp(tmp[0], "EA", 3))
        if(!ft_strncmp(tmp[0], "NO", 3))
        if(!ft_strncmp(tmp[0], "SO", 3))
        if(!ft_strncmp(tmp[0], "WE", 3))
        if(!ft_strncmp(tmp[0], "F", 2))
        if(!ft_strncmp(tmp[0], "C", 2))
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


// int map_size_err(t_line *lines)
// {
//     t_line *tmp;
//     int i;

//     i = 0;
//     tmp = lines;
//     while(tmp)
//     {
//         tmp = tmp->next;
//         i++;
//     }
//     if(i <= 8)
//         return(1);
//     return(0);
    
// }

int map_errors(t_data *data)
{
    if(ft_linesize(data->lines) <= 8)
        return(1);
    if(path_error(data))
        return(1);
    
    return(0);
}

int main(int ac, char **av)
{
    t_data  data;
    t_line  *tmp;

    if (ac == 2)
    {
        if(check_map_name(av))
            return(ft_putstr_fd("error\n",2), 0);
        if(open_file_error(&data, av[1]))
            return(ft_putstr_fd("error\n",2), 0);
        if (read_map(&data))
            return(ft_putstr_fd("error\n",2), 0);
        if (map_errors(&data))
            return(ft_putstr_fd("error\n",2), 0);
    }
    else
        ft_putstr_fd("error\n",2);

    while(data.lines)
    {
        tmp = data.lines;
        printf("%s\n", data.lines->line);
        data.lines = data.lines->next;
        free(tmp->line);
        free(tmp);
    }
    free(data.map);
    //system("leaks cub3D");
    return (0);
}