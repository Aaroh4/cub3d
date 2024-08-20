/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:55:36 by ahamalai          #+#    #+#             */
/*   Updated: 2024/08/20 16:21:06 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3dbonus.h"

int	checkarraysize(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

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
	makethelines(map);
	if (mlx_is_key_down(map->mlx, MLX_KEY_W)
		|| mlx_is_key_down(map->mlx, MLX_KEY_S))
		playermovement(map);
	if (mlx_is_key_down(map->mlx, MLX_KEY_RIGHT)
		|| mlx_is_key_down(map->mlx, MLX_KEY_LEFT))
		playerrotation(map);
	if (mlx_is_key_down(map->mlx, MLX_KEY_A)
		|| mlx_is_key_down(map->mlx, MLX_KEY_D))
		playerstrafe(map);
	process_wait(map);
}

void	wait_frame(t_map *game, float limit)
{
	double	frame;

	frame = 0;
	while (frame < limit * 1000)
		frame += game->mlx->delta_time;
}

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	int	i;
	int	y;
	int	x;
	t_map	*map;
	int		time;

	map = param;
	i = 0;
	time = 0;
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS && map->waiting == false)
	{
		map->gun1->instances[0].enabled = false;

		map->wait_stage = 1;
		map->elapsed_time = 0;
		map->waiting = true;
	}
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(map->mlx);
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


	
	map->gun1_txt = mlx_load_png("textures/sprites/correct1.png");
	if (map->gun1_txt == NULL)
		ft_loadpng_fail2(map, 3, 0);
	map->gun1 = mlx_texture_to_image(map->mlx, map->gun1_txt);
	if (map->gun1 == NULL)
		ft_loadpng_fail2(map, 3, 1);
	mlx_delete_texture(map->gun1_txt);
	
	map->gun2_txt = mlx_load_png("textures/sprites/correct2.png");
	if (map->gun2_txt == NULL)
		ft_loadpng_fail2(map, 3, 0);
	map->gun2 = mlx_texture_to_image(map->mlx, map->gun2_txt);
	if (map->gun2 == NULL)
		ft_loadpng_fail2(map, 3, 1);
	mlx_delete_texture(map->gun2_txt);

	map->gun3_txt = mlx_load_png("textures/sprites/correct3.png");
	if (map->gun3_txt == NULL)
		ft_loadpng_fail2(map, 3, 0);
	map->gun3 = mlx_texture_to_image(map->mlx, map->gun3_txt);
	if (map->gun3 == NULL)
		ft_loadpng_fail2(map, 3, 1);
	mlx_delete_texture(map->gun3_txt);
	
		map->gun4_txt = mlx_load_png("textures/sprites/correct4.png");
	if (map->gun4_txt == NULL)
		ft_loadpng_fail2(map, 3, 0);
	map->gun4 = mlx_texture_to_image(map->mlx, map->gun4_txt);
	if (map->gun4 == NULL)
		ft_loadpng_fail2(map, 3, 1);
	mlx_delete_texture(map->gun4_txt);


	mlx_image_to_window(map->mlx, map->background, 0, 0);
	mlx_image_to_window(map->mlx, map->gun1, SCREENWIDTH / 2, SCREENLENGTH / 1.5);
	mlx_image_to_window(map->mlx, map->gun2, SCREENWIDTH / 2, SCREENLENGTH / 1.5);
	mlx_image_to_window(map->mlx, map->gun3, SCREENWIDTH / 2, SCREENLENGTH / 1.5);
	mlx_image_to_window(map->mlx, map->gun4, SCREENWIDTH / 2, SCREENLENGTH / 1.5);

	map->gun2->instances[0].enabled = 0;
	map->gun3->instances[0].enabled = 0;
	map->gun4->instances[0].enabled = 0;
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
