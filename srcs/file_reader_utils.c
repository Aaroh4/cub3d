/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reader_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:33:49 by plang             #+#    #+#             */
/*   Updated: 2024/08/16 12:54:44 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_check_struct(t_fcheck *check)
{
	int	i;

	i = 0;
	while (i < check->linecount)
	{
		ft_strfree(check->file[i]);
		i++;
	}
	ft_arrfree(check->file);
	ft_strfree(check->north);
	ft_strfree(check->south);
	ft_strfree(check->west);
	ft_strfree(check->east);
	ft_strfree(check->ground);
	ft_strfree(check->sky);
}

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
