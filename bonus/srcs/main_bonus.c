/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:55:36 by ahamalai          #+#    #+#             */
/*   Updated: 2024/08/22 12:28:22 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	process_wait(t_map *map)
{
	if (map->waiting)
	{
		map->gun2->instances[0].enabled = true;
		map->elapsed_time += map->mlx->delta_time;
		if (map->elapsed_time > 0.1)
		{
			map->gun2->instances[0].enabled = false;
			map->gun3->instances[0].enabled = true;
		}
		if (map->elapsed_time > 0.2)
		{
			map->gun3->instances[0].enabled = false;
			map->gun4->instances[0].enabled = true;
		}
		if (map->elapsed_time > 0.3)
		{
			map->gun4->instances[0].enabled = false;
			map->gun1->instances[0].enabled = true;
			map->waiting = false;
		}
	}
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
	if (map->m == 1)
		mlx_set_mouse_pos(map->mlx, (SCREENWIDTH / 2), (SCREENLENGTH / 2));
	process_wait(map);
	makethelines(map);
}

void	ft_key_hook(mlx_key_data_t kd, void *param)
{
	t_map	*map;

	map = param;
	if (kd.key == MLX_KEY_SPACE && kd.action \
		== MLX_PRESS && map->waiting == false)
	{
		map->gun1->instances[0].enabled = false;
		map->wait_stage = 1;
		map->elapsed_time = 0;
		map->waiting = true;
	}
	if (kd.key == MLX_KEY_ESCAPE && kd.action == MLX_PRESS)
		mlx_close_window(map->mlx);
	if (kd.key == MLX_KEY_H && kd.action == MLX_PRESS && map->m == 0)
	{
		mlx_set_cursor_mode(map->mlx, MLX_MOUSE_HIDDEN);
		map->m = 1;
	}
	else if (kd.key == MLX_KEY_H && kd.action == MLX_PRESS && map->m == 1)
	{
		mlx_set_cursor_mode(map->mlx, MLX_MOUSE_NORMAL);
		map->m = 0;
	}
	if (kd.key == MLX_KEY_E && kd.action == MLX_PRESS)
		door_mechanics(map);
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
	gun_texture1(map);
	gun_texture2(map);
	gun_image(map);
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
}

int	main(int argc, char **argv)
{
	char	*map_name;
	int		count;
	t_map	map;

	if (argc != 2 || SCREENWIDTH > 1600 || SCREENLENGTH > 800)
		invalid_input(INVCUB);
	argument_check(argv[1]);
	count = 0;
	map_name = argv[1];
	ft_memset(&map, 0, sizeof(map));
	count = count_file_lines(map_name, count);
	read_file(map_name, count, &map);
	start_window(&map);
	mlx_terminate(map.mlx);
	return (0);
}
