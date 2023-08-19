/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   parcing7.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: iecharak <iecharak@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/08/19 10:27:21 by iecharak		  #+#	#+#			 */
/*   Updated: 2023/08/19 11:49:35 by iecharak		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_atoi_rang(const char *str)
{
	int				i;
	unsigned long	rslt;
	int				sign;

	rslt = 0;
	sign = 1;
	i = 0;
	while (str[i] == '\t' || str[i] == ' ' || str[i] == '\v' || str[i] == '\r'
		|| str[i] == '\f' || str[i] == '\n')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		rslt = rslt * 10 + str[i] - 48;
		i++;
		if (rslt > 255)
			return (-1);
	}
	return (rslt *= sign);
}

int	invalid_char_color(char *color)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (color && color[i])
	{
		if (!ft_isdigit(color[i]) && color[i] != ',' && color[i] != '+')
			return (ft_err("Invalid color code"));
		if (ft_isdigit(color[i]) && color[i + 1] && (color[i + 1] == '+'))
			return (ft_err("Invalid color code"));
		if ((color[i] == '+') && color[i + 1] && !ft_isdigit(color[i]))
			return (ft_err("Invalid color code"));
		if (color[i] == '+')
			j++;
		if (color[i] == ',')
			k++;
		i++;
	}
	if (k != 2 || j > 3)
		return (ft_err("Invalid color code"));
	return (0);
}

void	freestr(char ***strsplit)
{
	int		i;
	char	**str;

	i = 0;
	str = NULL;
	str = *strsplit;
	if (!str)
		return ;
	while (str && str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	invalid_rang_color(char *strc, int *color)
{
	char	**str;
	int		i;
	int		range;

	i = 0;
	*(color) = 0;
	str = ft_split(strc, ',');
	if (!str)
		return (1);
	while (str && str[i++])
	{
		range = ft_atoi_rang(str[i - 1]);
		if (range < 0)
			return (freestr(&str), ft_err("Invalid color code"));
		else if (i == 1)
			*(color) += (range << 16);
		else if (i == 2)
			*(color) += (range << 8);
		else if (i == 3)
			*(color) += range;
	}
	freestr(&str);
	return (0);
}

int	color_err(t_data *data)
{	
	if (invalid_char_color(data->char_c))
		return (1);
	if (invalid_char_color(data->char_f))
		return (1);
	if (invalid_rang_color(data->char_f, &data->f_color))
		return (1);
	if (invalid_rang_color(data->char_c, &data->c_color))
		return (1);
	return (0);
}
	// while (str[i])
	// 	i++;
	// if (i != 3)
	// 	return (freestr(&str), ft_err("Invalid color code"));