/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 11:29:01 by plang             #+#    #+#             */
/*   Updated: 2024/08/16 16:08:12 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
	mlx_delete_image(map->mlx, map->background);
}
