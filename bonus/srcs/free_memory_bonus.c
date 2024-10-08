/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 11:29:01 by plang             #+#    #+#             */
/*   Updated: 2024/08/23 10:59:35 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	free_check_struct(t_fcheck *check)
{
	int	i;

	i = 0;
	while (i < check->count)
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

void	ft_strfree(char *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
	else
		return ;
}

void	ft_arrfree(char **arr)
{
	if (arr)
	{
		free(arr);
		arr = NULL;
	}
	else
		return ;
}

void	successful_exit(t_map *map, int index)
{
	int	i;

	i = 0;
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
	mlx_delete_image(map->mlx, map->background);
	mlx_delete_image(map->mlx, map->gun1);
	mlx_delete_image(map->mlx, map->gun2);
	mlx_delete_image(map->mlx, map->gun3);
	mlx_delete_image(map->mlx, map->gun4);
	ft_putstr_fd(ENDGAME, 1);
}
