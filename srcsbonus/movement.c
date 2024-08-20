/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:24:42 by ahamalai          #+#    #+#             */
/*   Updated: 2024/08/20 15:17:56 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3dbonus.h"

static int	is_colliding(int y, int x, t_map *map)
{
	if (map->mapsave[y][x] == '1' || map->mapsave[y][x] == '2')
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
	if (map->gunpos == 20)
		map->gunway = 1;
	else if (map->gunpos == 0)
		map->gunway = 0;
	if (map->gunway == 0)
	{
		map->gun1->instances[0].x += 4;
		map->gun2->instances[0].x += 4;
		map->gun3->instances[0].x += 4;
		map->gun4->instances[0].x += 4;
		map->gunpos++;
	}
	else
	{
		map->gun1->instances[0].x -= 4;
		map->gun2->instances[0].x -= 4;
		map->gun3->instances[0].x -= 4;
		map->gun4->instances[0].x -= 4;
		map->gunpos--;
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
