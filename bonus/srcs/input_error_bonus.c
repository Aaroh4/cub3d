/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_error_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 09:26:29 by plang             #+#    #+#             */
/*   Updated: 2024/08/20 17:15:40 by plang            ###   ########.fr       */
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
	if (imagef == 0)
		ft_putstr_fd(MLXLPFAIL, 2);
	else if (imagef == 1)
		ft_putstr_fd(MLXTXTFAIL, 2);
	mlx_terminate(map->mlx);
	exit (1);
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
