/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_error2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 11:29:01 by plang             #+#    #+#             */
/*   Updated: 2024/08/16 13:17:11 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_loadpng_fail(t_fcheck *check, t_map *map, int index)
{
	while (index >= 0)
	{
		mlx_delete_texture(map->wall.txt[index]);
		index--;
	}
	error_inside_file(check, MLXLPFAIL);
}

void	ft_loadpng_fail2(t_map *map, int index, int imagef)
{
	int	i;

	i = 0;
	if (imagef == 1)
		mlx_delete_texture(map->background_txt);
	while (i < map->map_size)
	{
		ft_strfree(map->mapsave[i]);
		i++;
	}
	ft_arrfree(map->mapsave);
	while (index >= 0)
	{
		mlx_delete_texture(map->wall.txt[index]);
		index--;
	}
	if (imagef == 0)
		ft_putstr_fd(MLXLPFAIL, 2);
	else if (imagef == 1)
		ft_putstr_fd(MLXTXTFAIL, 2);
	mlx_terminate(map->mlx);
	exit (1);
}
