/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_error_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 09:26:29 by plang             #+#    #+#             */
/*   Updated: 2024/08/21 14:03:38 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

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
	mlx_delete_texture(map->wall.door);
	if (imagef == 0)
		ft_putstr_fd(MLXLPFAIL, 2);
	else if (imagef == 1 || imagef == 3)
		ft_putstr_fd(MLXTXTFAIL, 2);
	else if (imagef == 2)
		ft_putstr_fd(MLXIMGFAIL, 2);
	mlx_terminate(map->mlx);
	exit (1);
}

void	ft_loadimage_fail(t_map *map, int gun_index)
{
	if (gun_index == 1)
		mlx_delete_texture(map->gun1_txt);
	if (gun_index == 2)
		mlx_delete_texture(map->gun2_txt);
	if (gun_index == 3)
		mlx_delete_texture(map->gun3_txt);
	if (gun_index == 4)
		mlx_delete_texture(map->gun4_txt);
	ft_loadpng_fail2(map, 3, 3);
}

void	invalid_input(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}

void	error_inside_file(t_fcheck *check, char *str)
{
	int	i;

	i = 0;
	ft_putstr_fd(str, 2);
	while (i < check->linecount)
	{
		ft_strfree(check->file[i]);
		i++;
	}
	ft_arrfree(check->file);
	i = 0;
	while (i < check->map_size)
	{
		ft_strfree(check->mapcpy[i]);
		i++;
	}
	ft_arrfree(check->mapcpy);
	ft_strfree(check->north);
	ft_strfree(check->south);
	ft_strfree(check->west);
	ft_strfree(check->east);
	ft_strfree(check->ground);
	ft_strfree(check->sky);
	exit (1);
}
