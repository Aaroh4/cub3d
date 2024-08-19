/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:55:36 by ahamalai          #+#    #+#             */
/*   Updated: 2024/08/19 12:23:11 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	getting_index(t_map *map, double length)
{
	if (map->side == 1)
	{
		if (map->raydiry > 0)
			map->wall.side = 0;
		else
			map->wall.side = 1;
	}
	else
	{
		if (map->raydirx > 0)
			map->wall.side = 2;
		else
			map->wall.side = 3;
	}
	if (map->side == 0)
		map->wallx = map->cameraposy + length * map->raydiry;
	else
		map->wallx = map->cameraposx + length * map->raydirx;
}

int	calculate_wall(t_map *map)
{
	double	length;
	double	height;
	double	correct;

	if (map->side == 0)
		length = (map->rayposx - map->deltadistx);
	else
		length = (map->rayposy - map->deltadisty);
	correct = (map->pa - map->raypa);
	getting_index(map, length);
	map->wallx -= floor((map->wallx));
	length *= cos(correct);
	height = (STEPSIZE * SCREENLENGTH) / length;
	map->wall.ty_off = 0;
	map->wall.ty_step = map->wall.txt[map->wall.side]->height / height;
	if (height > SCREENLENGTH)
	{
		map->wall.ty_off = (height - SCREENLENGTH) / 2;
		height = SCREENLENGTH;
	}
	map->wall.y = map->wall.ty_off * map->wall.ty_step;
	return (height);
}

void	draw_line(int x, int y, t_map *map)
{
	mlx_texture_t	*wall;
	int				offset;
	uint32_t		pixel;

	offset = 0;
	pixel = 0;
	wall = map->wall.txt[map->wall.side];
	if (map->wall.side == 0 || map->wall.side == 3)
	{
		if (map->wallx < 0.015)
			offset = (((int)(map->wall.y) * wall->height + (int)(map->wallx
							* (wall->width + 1) * -1))) * sizeof(uint32_t);
		else
			offset = (((int)(map->wall.y + 1) * wall->height + (int)(map->wallx
							* (wall->width + 1) * -1))) * sizeof(uint32_t);
	}
	else
		offset = (((int)map->wall.y * wall->height
					+ (int)(map->wallx * wall->width))) * sizeof(uint32_t);
	if (offset < (int)(wall->width * wall->height * sizeof(uint32_t)))
		pixel = (wall->pixels[offset] << 24) | (wall->pixels[offset + 1] << 16)
			| (wall->pixels[offset + 2] << 8) | wall->pixels[offset + 3];
	mlx_put_pixel(map->background, x, y, pixel);
	map->wall.y += map->wall.ty_step;
}

void	makethewalls(t_map *map)
{
	int	wall_height;
	int	i;
	int	untily;
	int	drawstart;
	int	drawend;

	wall_height = calculate_wall(map);
	i = 0;
	drawstart = -wall_height / 2 + SCREENLENGTH / 2;
	if (drawstart < 0)
		drawstart = 0;
	drawend = wall_height / 2 + SCREENLENGTH / 2;
	untily = 0;
	while (i < SCREENLENGTH)
	{
		if (i < drawstart)
			mlx_put_pixel(map->background, map->rayamount, i, map->ceiling);
		else if (i >= drawstart && i <= drawend)
			draw_line(map->rayamount, i, map);
		else if (i > drawend)
			mlx_put_pixel(map->background, map->rayamount, i, map->floor);
		i++;
	}
}

int	checkarraysize(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

void	rayposition(t_map *map)
{
	if (map->raydirx < 0)
	{
		map->stepx = -1;
		map->rayposx = (map->cameraposx - map->mapx) * map->deltadistx;
	}
	else
	{
		map->stepx = 1;
		map->rayposx = (map->mapx + 1.0 - map->cameraposx) * map->deltadistx;
	}
	if (map->raydiry < 0)
	{
		map->stepy = -1;
		map->rayposy = (map->cameraposy - map->mapy) * map->deltadisty;
	}
	else
	{
		map->stepy = 1;
		map->rayposy = (map->mapy + 1.0 - map->cameraposy) * map->deltadisty;
	}
}

int	ray_loop(t_map *map)
{
	while (1)
	{
		if (map->rayposx < map->rayposy)
		{
			map->rayposx += map->deltadistx;
			map->mapx += map->stepx;
			map->side = 0;
		}
		else
		{
			map->rayposy += map->deltadisty;
			map->mapy += map->stepy;
			map->side = 1;
		}
		if (map->size <= map->mapy || map->mapy < 0 || map->mapx < 0
			|| (int)ft_strlen(map->mapsave[map->mapy]) < map->mapx)
			return (1);
		if (map->mapsave[map->mapy][map->mapx] == '1')
			return (0);
	}
}

void	shoot_ray(t_map *map)
{
	map->mapy = map->cameraposy;
	map->mapx = map->cameraposx;
	map->deltadistx = sqrt(1 + (map->raydiry * map->raydiry)
			/ (map->raydirx * map->raydirx));
	map->deltadisty = sqrt(1 + (map->raydirx * map->raydirx)
			/ (map->raydiry * map->raydiry));
	rayposition(map);
	if (ray_loop(map))
	{
		map->rayposx = 5;
		map->rayposy = 5;
		map->deltadisty = 1;
		map->deltadistx = 1;
	}
}

void	makethelines(t_map *map)
{
	int	i;

	i = 0;
	map->rayamount = -1;
	map->raydiry = map->diry;
	map->raydirx = map->dirx;
	map->raypa = map->pa - DEGREE * FOV / 2;
	while (i < SCREENWIDTH)
	{
		map->rayamount += 1;
		map->raypa += DEGREE / (double)(SCREENWIDTH / FOV);
		if (map->raypa > 2 * PI)
		{
			map->raypa -= 2 * PI;
		}
		map->raydirx = cos(map->raypa);
		map->raydiry = sin(map->raypa);
		shoot_ray(map);
		makethewalls(map);
		i++;
	}
}

void	playermovement(t_map *map)
{
	if (mlx_is_key_down(map->mlx, MLX_KEY_W))
	{
		map->cameraposy += map->diry / 2;
		map->cameraposx += map->dirx / 2;
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_S))
	{
		map->cameraposy -= map->diry / 2;
		map->cameraposx -= map->dirx / 2;
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_A))
	{
		map->cameraposy -= map->dirx / 3;
		map->cameraposx -= -map->diry / 3;
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_D))
	{
		map->cameraposy += map->dirx / 3;
		map->cameraposx += -map->diry / 3;
	}
}

void	playerrotation(t_map *map)
{
	if (mlx_is_key_down(map->mlx, MLX_KEY_LEFT))
	{
		map->pa -= 0.05;
		if (map->pa < 0)
			map->pa += 2 * PI;
	}
	else if (mlx_is_key_down(map->mlx, MLX_KEY_RIGHT))
	{
		map->pa += 0.05;
		if (map->pa >= 2 * PI)
			map->pa -= 2 * PI;
	}
	map->dirx = cos(map->pa) / 5;
	map->diry = sin(map->pa) / 5;
}

void	ft_loop_hook(void *param)
{
	t_map	*map;

	map = param;
	makethelines(map);
	if (mlx_is_key_down(map->mlx, MLX_KEY_W)
		|| mlx_is_key_down(map->mlx, MLX_KEY_S)
		|| mlx_is_key_down(map->mlx, MLX_KEY_A)
		|| mlx_is_key_down(map->mlx, MLX_KEY_D))
		playermovement(map);
	if (mlx_is_key_down(map->mlx, MLX_KEY_RIGHT)
		|| mlx_is_key_down(map->mlx, MLX_KEY_LEFT))
		playerrotation(map);
}

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_map	*map;

	map = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(map->mlx);
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
