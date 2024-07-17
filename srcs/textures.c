/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:36:37 by ahamalai          #+#    #+#             */
/*   Updated: 2024/07/17 13:18:34 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_init_textu(t_map *map)
{
	map->background_txt = mlx_load_png("textures/background.png");
	//if (map->background_txt == NULL)
	//	ft_error_mlx(map);
	map->player_txt = mlx_load_png("textures/ground.png");
	//if (map->player_txt == NULL)
	//	ft_error_mlx(map);
	map->wall_txt = mlx_load_png("textures/wall.png");
	//if (map->player_txt == NULL)
	//	ft_error_mlx(map);
}

void	ft_init_img(mlx_t *mlx, t_map *map)
{
	map->background = mlx_texture_to_image(mlx, map->background_txt);
	//if (map->background == NULL)
	//	ft_error_mlx(map);
	mlx_delete_texture(map->background_txt);
	map->player = mlx_texture_to_image(mlx, map->player_txt);
	//if (map->player == NULL)
	//	ft_error_mlx(map);
	mlx_delete_texture(map->player_txt);
	map->wall = mlx_texture_to_image(mlx, map->wall_txt);
	//if (map->background == NULL)
	//	ft_error_mlx(map);
	mlx_delete_texture(map->wall_txt);
}

#include <stdio.h>

void	ft_create_wall(t_map *img)
{
	int	i;
	int	j;

	i = 8;
	while (i < img->linecount)
	{
		j = 0;
		printf("%s", img->mapsave[i]);
		while (j <= img->lenght && img->mapsave[i][j] != '\0')
		{
			if (img->mapsave[i][j] == 'N' || img->mapsave[i][j] == 'S' 
				|| img->mapsave[i][j] == 'W' || img->mapsave[i][j] == 'E')
			{
				mlx_image_to_window(img->mlx, img->player, 20 * j, 20 * (i - 8));
				img->px = 20 * j;
				img->py = 20 * (i - 8);
			}
			if (img->mapsave[i][j] == '1')
				mlx_image_to_window(img->mlx, img->wall, 20 * j, 20 * (i - 8));
			j++;
		}
		i++;
	}
}
