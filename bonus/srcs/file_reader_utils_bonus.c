/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reader_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:33:49 by plang             #+#    #+#             */
/*   Updated: 2024/08/20 17:15:37 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	data_transfer(t_map *map, t_fcheck *check)
{
	map->mapsave = check->mapcpy;
	map->cameraposx = check->cameraposx;
	map->cameraposy = check->cameraposy;
	map->playerstartpos = check->playerstartpos;
	map->map_size = check->map_size;
	map->floor = check->bottom;
	map->ceiling = check->top;
	map->wall.txt[0] = mlx_load_png(check->south);
	if (map->wall.txt[0] == NULL)
		ft_loadpng_fail(check, map, -1);
	map->wall.txt[1] = mlx_load_png(check->north);
	if (map->wall.txt[1] == NULL)
		ft_loadpng_fail(check, map, 0);
	map->wall.txt[2] = mlx_load_png(check->west);
	if (map->wall.txt[2] == NULL)
		ft_loadpng_fail(check, map, 1);
	map->wall.txt[3] = mlx_load_png(check->east);
	if (map->wall.txt[3] == NULL)
		ft_loadpng_fail(check, map, 2);
	map->wall.door = mlx_load_png(DOORTXT);
	if (map->wall.door == NULL)
		ft_loadpng_fail(check, map, 3);
}

void	data_reading(t_fcheck *check)
{
	check->linecount = check->count;
	get_map_information(check);
	if (check->error == 1)
		error_inside_file(check, INVTXTMAP);
	check_rgb_floor(check);
	if (check->error == 1)
		error_inside_file(check, INVRGB);
	check_rgb_ceiling(check);
	if (check->error == 1)
		error_inside_file(check, INVRGB);
	check_player_and_boarder(check);
	clean_input_strings(check);
}
