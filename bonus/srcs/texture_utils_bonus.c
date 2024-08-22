/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:02:23 by plang             #+#    #+#             */
/*   Updated: 2024/08/22 12:29:14 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	gun_texture1(t_map *map)
{
	map->gun1_txt = mlx_load_png("textures/sprites/correct1.png");
	if (map->gun1_txt == NULL)
		ft_loadpng_fail2(map, 3, 0);
	map->gun1 = mlx_texture_to_image(map->mlx, map->gun1_txt);
	if (map->gun1 == NULL)
		ft_loadimage_fail(map, 1);
	mlx_delete_texture(map->gun1_txt);
	map->gun2_txt = mlx_load_png("textures/sprites/correct2.png");
	if (map->gun2_txt == NULL)
		ft_loadpng_fail2(map, 3, 0);
	map->gun2 = mlx_texture_to_image(map->mlx, map->gun2_txt);
	if (map->gun2 == NULL)
		ft_loadimage_fail(map, 2);
	mlx_delete_texture(map->gun2_txt);
}

void	gun_texture2(t_map *map)
{
	map->gun3_txt = mlx_load_png("textures/sprites/correct3.png");
	if (map->gun3_txt == NULL)
		ft_loadpng_fail2(map, 3, 0);
	map->gun3 = mlx_texture_to_image(map->mlx, map->gun3_txt);
	if (map->gun3 == NULL)
		ft_loadimage_fail(map, 3);
	mlx_delete_texture(map->gun3_txt);
	map->gun4_txt = mlx_load_png("textures/sprites/correct4.png");
	if (map->gun4_txt == NULL)
		ft_loadpng_fail2(map, 3, 0);
	map->gun4 = mlx_texture_to_image(map->mlx, map->gun4_txt);
	if (map->gun4 == NULL)
		ft_loadimage_fail(map, 4);
	mlx_delete_texture(map->gun4_txt);
}

void	gun_image(t_map *map)
{
	if (mlx_image_to_window(map->mlx, map->background, 0, 0) == -1)
		ft_loadpng_fail2(map, 3, 2);
	if (mlx_image_to_window(map->mlx, map->gun1 \
		, SCREENWIDTH / 2, SCREENLENGTH / 2) == -1)
		ft_loadpng_fail2(map, 3, 2);
	if (mlx_image_to_window(map->mlx, map->gun2 \
		, SCREENWIDTH / 2, SCREENLENGTH / 2) == -1)
		ft_loadpng_fail2(map, 3, 2);
	if (mlx_image_to_window(map->mlx, map->gun3 \
		, SCREENWIDTH / 2, SCREENLENGTH / 2) == -1)
		ft_loadpng_fail2(map, 3, 2);
	if (mlx_image_to_window(map->mlx, map->gun4 \
		, SCREENWIDTH / 2, SCREENLENGTH / 2) == -1)
		ft_loadpng_fail2(map, 3, 2);
	map->gun2->instances[0].enabled = false;
	map->gun3->instances[0].enabled = false;
	map->gun4->instances[0].enabled = false;
}
