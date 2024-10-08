/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:26:19 by ahamalai          #+#    #+#             */
/*   Updated: 2024/08/22 13:07:25 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static void	rayposition(t_map *map)
{
	if (map->raydirx < 0)
	{
		map->stepx = -1;
		map->rayposx = (map->cameraposx - map->mapx) * map->deltadistx;
	}
	else
	{
		map->stepx = 1;
		map->rayposx = (map->mapx + 1.0 - map->cameraposx) * map->deltadistx;
	}
	if (map->raydiry < 0)
	{
		map->stepy = -1;
		map->rayposy = (map->cameraposy - map->mapy) * map->deltadisty;
	}
	else
	{
		map->stepy = 1;
		map->rayposy = (map->mapy + 1.0 - map->cameraposy) * map->deltadisty;
	}
}

static int	ray_loop(t_map *map)
{
	while (1)
	{
		if (map->rayposx < map->rayposy)
		{
			map->rayposx += map->deltadistx;
			map->mapx += map->stepx;
			map->side = 0;
		}
		else
		{
			map->rayposy += map->deltadisty;
			map->mapy += map->stepy;
			map->side = 1;
		}
		if (map->mapsave[map->mapy][map->mapx] == '1')
			return (0);
		if (map->mapsave[map->mapy][map->mapx] == '2')
		{
			map->is_door = 1;
			return (0);
		}
	}
}

static void	shoot_ray(t_map *map)
{
	map->mapy = map->cameraposy;
	map->mapx = map->cameraposx;
	map->deltadistx = sqrt(1 + (map->raydiry * map->raydiry)
			/ (map->raydirx * map->raydirx));
	map->deltadisty = sqrt(1 + (map->raydirx * map->raydirx)
			/ (map->raydiry * map->raydiry));
	rayposition(map);
	map->is_door = 0;
	ray_loop(map);
}

void	makethelines(t_map *map)
{
	int	i;

	i = 0;
	map->rayamount = -1;
	map->raydiry = map->diry;
	map->raydirx = map->dirx;
	map->raypa = map->pa - DEGREE * FOV / 2;
	while (i < SCREENWIDTH)
	{
		map->rayamount += 1;
		map->raypa += DEGREE / (double)(SCREENWIDTH / FOV);
		if (map->raypa > 2 * PI)
		{
			map->raypa -= 2 * PI;
		}
		map->raydirx = cos(map->raypa);
		map->raydiry = sin(map->raypa);
		shoot_ray(map);
		makethewalls(map);
		i++;
	}
}
