/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:55:36 by ahamalai          #+#    #+#             */
/*   Updated: 2024/08/20 16:50:56 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	checkarraysize(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

void	ft_loop_hook(void *param)
{
	t_map	*map;

	map = param;
	mlx_get_mouse_pos(map->mlx, &map->mx, &map->my);
	mouse_movement(map);
	map->dirx = cos(map->pa) / 5;
    map->diry = sin(map->pa) / 5;
	if (mlx_is_key_down(map->mlx, MLX_KEY_W)
		|| mlx_is_key_down(map->mlx, MLX_KEY_S))
		playermovement(map);
	if (mlx_is_key_down(map->mlx, MLX_KEY_RIGHT)
		|| mlx_is_key_down(map->mlx, MLX_KEY_LEFT))
		playerrotation(map);
	if (mlx_is_key_down(map->mlx, MLX_KEY_A)
		|| mlx_is_key_down(map->mlx, MLX_KEY_D))
		playerstrafe(map);
	makethelines(map);
	if (map->mouse_enabled == 1)
		mlx_set_mouse_pos(map->mlx, (SCREENWIDTH / 2), (SCREENLENGTH / 2));
}

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	int	i;
	int	y;
	int	x;
	t_map	*map;

	map = param;
	i = 0;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(map->mlx);
	if (keydata.key == MLX_KEY_H && keydata.action == MLX_PRESS && map->mouse_enabled == 0)
	{
		mlx_set_cursor_mode(map->mlx, MLX_MOUSE_HIDDEN);
		map->mouse_enabled = 1;
	}
	else if (keydata.key == MLX_KEY_H && keydata.action == MLX_PRESS && map->mouse_enabled == 1)
	{
		mlx_set_cursor_mode(map->mlx, MLX_MOUSE_NORMAL);
		map->mouse_enabled = 0;
	}
	while (i < 4)
	{
		y = 0;
		x = 0;
		if (i == 0)
			y = 1;
		else if (i == 1)
			y = -1;
		else if (i == 2)
			x = 1;
		else
			x = -1;
		if (keydata.key == MLX_KEY_E && keydata.action == MLX_PRESS && 
			(map->mapsave[(int)map->cameraposy + y][(int)map->cameraposx + x] == '2'))
			map->mapsave[(int)map->cameraposy + y][(int)map->cameraposx + x] = '3';
		else if (keydata.key == MLX_KEY_E && keydata.action == MLX_PRESS && 
		(map->mapsave[(int)map->cameraposy + y][(int)map->cameraposx + x] == '3'))
			map->mapsave[(int)map->cameraposy + y][(int)map->cameraposx + x] = '2';
		i++;
	}
}

void	start_window(t_map *map)
{
	map->mlx = mlx_init(SCREENWIDTH, SCREENLENGTH, "Game", false);
	map->background_txt = mlx_load_png("textures/background.png");
	if (map->background_txt == NULL)
		ft_loadpng_fail2(map, 3, 0);
	map->background = mlx_texture_to_image(map->mlx, map->background_txt);
	if (map->background == NULL)
		ft_loadpng_fail2(map, 3, 1);
	mlx_delete_texture(map->background_txt);
	mlx_image_to_window(map->mlx, map->background, 0, 0);
	mlx_put_pixel(map->background, 440, 100, 535353);
	if (map->playerstartpos == 'N')
		map->pa = 4.71;
	else if (map->playerstartpos == 'S')
		map->pa = -4.71;
	else if (map->playerstartpos == 'E')
		map->pa = 0;
	else if (map->playerstartpos == 'W')
		map->pa = 9.42;
	map->dirx = cos(map->pa) / 5;
	map->diry = sin(map->pa) / 5;
	mlx_key_hook(map->mlx, ft_key_hook, map);
	mlx_loop_hook(map->mlx, ft_loop_hook, map);
	mlx_loop(map->mlx);
	successful_exit(map, 3);
	mlx_terminate(map->mlx);
}

int	main(int argc, char **argv)
{
	char	*map_name;
	int		count;
	t_map	map;

	if (argc != 2 || SCREENWIDTH > 3000 || SCREENLENGTH > 1500)
		exit(1);
	argument_check(argv[1]);
	count = 0;
	map_name = argv[1];
	count = count_file_lines(map_name, count);
	read_file(map_name, count, &map);
	map.size = checkarraysize(map.mapsave);
	start_window(&map);
	return (0);
}
