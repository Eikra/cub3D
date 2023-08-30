/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iecharak <iecharak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 21:44:37 by iecharak          #+#    #+#             */
/*   Updated: 2023/08/30 22:02:12 by iecharak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	KeyRelease(int key, t_data *data)
{
	printf("%d\n", key);
	if (key == W || key == S)
		data->dir_keys[0] = -1;
	// if (key == A || key == D) // && !is_wall_right(data)
	// 	data->dir_keys[1] = -1;
	if (key == LEFT || key == RIGHT) // && !is_wall_right(data)
		data->dir_keys[2] = -1 ;
	return (0);
}

int	Keypress(int key, t_data *data)
{
	printf("%d\n", key);
	if (key == ESC)
	{
		printf("You closed the game using ESC key !");
		mlx_destroy_window(data->id, data->w_id);
		exit(0);
	}
	if (key == W || key == S)
		data->dir_keys[0] = key;
	// if (key == A || key == D) // && !is_wall_right(data)
	// 	data->dir_keys[1] = key;
	if (key == LEFT || key == RIGHT) // && !is_wall_right(data)
		data->dir_keys[2] = key ;
	return (0);
}

int deal_keys(t_data *data)
{
	mlx_hook(data->w_id, 2, 1L<<0,  Keypress, data);
	mlx_hook(data->w_id, 3, 1L<<1, KeyRelease, data);
	mlx_hook(data->w_id, 17, 0, ft_exit, data);
	player_movement(data);
	return 0;
}