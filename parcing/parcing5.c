/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iecharak <iecharak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 19:44:14 by iecharak          #+#    #+#             */
/*   Updated: 2023/08/18 19:48:52 by iecharak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

    tmp = data->lines;
    i = 0;
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
