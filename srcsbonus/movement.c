/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:24:42 by ahamalai          #+#    #+#             */
/*   Updated: 2024/08/19 14:02:05 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3dbonus.h"

void	playermovement(t_map *map)
{
	if (mlx_is_key_down(map->mlx, MLX_KEY_W))
	{
		map->cameraposy += map->diry / 2;
		map->cameraposx += map->dirx / 2;
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_S))
	{
		map->cameraposy -= map->diry / 2;
		map->cameraposx -= map->dirx / 2;
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_A))
	{
		map->cameraposy -= map->dirx / 3;
		map->cameraposx -= -map->diry / 3;
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_D))
	{
		map->cameraposy += map->dirx / 3;
		map->cameraposx += -map->diry / 3;
	}
}

void	playerrotation(t_map *map)
{
	if (mlx_is_key_down(map->mlx, MLX_KEY_LEFT))
	{
		map->pa -= 0.05;
		if (map->pa < 0)
			map->pa += 2 * PI;
	}
	else if (mlx_is_key_down(map->mlx, MLX_KEY_RIGHT))
	{
		map->pa += 0.05;
		if (map->pa >= 2 * PI)
			map->pa -= 2 * PI;
	}
	map->dirx = cos(map->pa) / 5;
	map->diry = sin(map->pa) / 5;
}
