/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:24:42 by ahamalai          #+#    #+#             */
/*   Updated: 2024/08/22 14:23:17 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static int	is_colliding(int y, int x, t_map *map)
{
	if (map->mapsave[y][x] == '1' || map->mapsave[y][x] == '2')
		return (1);
	if (((int)map->cameraposx != x && (int)map->cameraposy != y) \
		&& (map->mapsave[y][(int)map->cameraposx] == '1' \
		|| map->mapsave[(int)map->cameraposy][x] == '1'))
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
	wayofthegun(map);
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

void	mouse_movement(t_map *map)
{
	double	center_x;

	center_x = SCREENWIDTH / 2.0;
	if (map->mx < center_x && map->mx >= 0 && map->my < SCREENLENGTH \
		&& map->my >= 0)
	{
		map->pa -= 0.05;
		if (map->pa < 0)
			map->pa += 2 * PI;
	}
	else if (map->mx > center_x && map->mx < SCREENWIDTH \
		&& map->my < SCREENLENGTH && map->my >= 0)
	{
		map->pa += 0.05;
		if (map->pa >= 2 * PI)
			map->pa -= 2 * PI;
	}
}
