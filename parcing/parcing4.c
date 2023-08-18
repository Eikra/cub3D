/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iecharak <iecharak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 19:45:17 by iecharak          #+#    #+#             */
/*   Updated: 2023/08/18 20:34:49 by iecharak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
                return(ft_err("Incomplet map"));
        }
        free(str);
        str = get_next_line(data->fd);
    }
    if (!data->lines)
        return (ft_err("Empty map"));
    return (0);
}
