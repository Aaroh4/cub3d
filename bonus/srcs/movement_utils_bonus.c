/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:51:38 by plang             #+#    #+#             */
/*   Updated: 2024/08/21 15:19:53 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	wayofthegun(t_map *map)
{
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

void	door_mechanics(t_map *map)
{
	if (map->middlerayside == 1 && \
		(map->mapsave[(int)map->cameraposy - 1][(int)map->cameraposx] == '2'))
		map->mapsave[(int)map->cameraposy - 1][(int)map->cameraposx] = '3';
	else if (map->middlerayside == 1 && \
		(map->mapsave[(int)map->cameraposy - 1][(int)map->cameraposx] == '3'))
		map->mapsave[(int)map->cameraposy - 1][(int)map->cameraposx] = '2';
	if (map->middlerayside == 2 && \
		(map->mapsave[(int)map->cameraposy][(int)map->cameraposx + 1] == '2'))
		map->mapsave[(int)map->cameraposy][(int)map->cameraposx + 1] = '3';
	else if (map->middlerayside == 2 && \
		(map->mapsave[(int)map->cameraposy][(int)map->cameraposx + 1] == '3'))
		map->mapsave[(int)map->cameraposy][(int)map->cameraposx + 1] = '2';
	if (map->middlerayside == 3 && \
		(map->mapsave[(int)map->cameraposy][(int)map->cameraposx - 1] == '2'))
		map->mapsave[(int)map->cameraposy][(int)map->cameraposx - 1] = '3';
	else if (map->middlerayside == 3 && \
		(map->mapsave[(int)map->cameraposy][(int)map->cameraposx - 1] == '3'))
		map->mapsave[(int)map->cameraposy][(int)map->cameraposx - 1] = '2';
	if (map->middlerayside == 0 && \
		(map->mapsave[(int)map->cameraposy + 1][(int)map->cameraposx] == '2'))
		map->mapsave[(int)map->cameraposy + 1][(int)map->cameraposx] = '3';
	else if (map->middlerayside == 0 && \
		(map->mapsave[(int)map->cameraposy + 1][(int)map->cameraposx] == '3'))
		map->mapsave[(int)map->cameraposy + 1][(int)map->cameraposx] = '2';
}
