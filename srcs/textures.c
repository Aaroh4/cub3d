/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:36:37 by ahamalai          #+#    #+#             */
/*   Updated: 2024/07/04 17:00:58 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_init_textu(t_map *map)
{
	map->player_txt = mlx_load_png("textures/wall.png");
	//if (map->player_txt == NULL)
	//	ft_error_mlx(map);
}

void	ft_init_img(mlx_t *mlx, t_map *map)
{
	map->player = mlx_texture_to_image(mlx, map->player_txt);
	//if (map->player == NULL)
	//	ft_error_mlx(map);
	mlx_delete_texture(map->player_txt);
}
