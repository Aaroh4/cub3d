/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:24:42 by ahamalai          #+#    #+#             */
/*   Updated: 2024/08/19 14:20:41 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3dbonus.h"

static int	is_colliding(int y, int x, t_map *map)
{
	if (map->mapsave[y][x] == '1')
		return (1);
	return (0);
}

void	playerstrafe(t_map *map)
{
	if (mlx_is_key_down(map->mlx, MLX_KEY_A))
	{
		if (!is_colliding(map->cameraposy - map->dirx / 3
				, map->cameraposx - -map->diry / 3, map))
		{
			map->cameraposy -= map->dirx / 3;
			map->cameraposx -= -map->diry / 3;
		}
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_D))
	{
		if (!is_colliding(map->cameraposy + map->dirx / 3
				, map->cameraposx + -map->diry / 3, map))
		{
			map->cameraposy += map->dirx / 3;
			map->cameraposx += -map->diry / 3;
		}
	}
}

void	playermovement(t_map *map)
{
	if (mlx_is_key_down(map->mlx, MLX_KEY_W))
	{
		if (!is_colliding(map->cameraposy + map->diry / 2
				, map->cameraposx + map->dirx / 2, map))
		{
			map->cameraposy += map->diry / 2;
			map->cameraposx += map->dirx / 2;
		}
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_S))
	{
		if (!is_colliding(map->cameraposy - map->diry / 2
				, map->cameraposx - map->dirx / 2, map))
		{
			map->cameraposy -= map->diry / 2;
			map->cameraposx -= map->dirx / 2;
		}
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
