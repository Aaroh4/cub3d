#include "../includes/cub3d.h"

#include <stdio.h>

int	ft_check_move(t_map *img, int move)
{
	if (move == 3 && img->mapsave[img->plocation[1] - 1][img->plocation[0]] != '1')
	{
		//img->plocation[1] -= 1;
		//img->player->instances[0].y += img->diry;
		//img->player->instances[0].x += img->dirx;
		img->py -= 1;
	}
	else if (move == 4 && img->mapsave[img->plocation[1] + 1][img->plocation[0]] != '1')
	{
		//img->plocation[1] += 1;
		//img->player->instances[0].y -= img->diry;
		//img->player->instances[0].x -= img->dirx;
		img->py += 1;
	}
	else
		return (0);
	return (1);
}

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_map	*map;

	map = param;

	//double angle = pa / (1.0 + 0.28 * pa * pa);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(map->mlx);
}

int checkwallhit(t_map *map, double y, double x)
{
	int i;
	int yn;
	int xn;

	i = 0;
	yn = 0;
	xn = 0;
	while (x > 0)
	{
		xn++;
		x -= 20;
	}
	while (y > 0)
	{
		yn++;
		y -= 20;
	}
	//printf("abc x:%d y:%d &: %c\n", xn, xy, map->mapcopy[]);
	while (i < map->wallcount)
	{
		if (map->mapcopy[yn + 7][xn - 1] == '1')
			return (printf("asd\n"));
		//if (map->wall->instances[i].x == xn)
		//	return (printf("asd\n"));
		i++;
	}
	return (0);
}

void ft_loop_hook(void *param)
{
	t_map	*map;

	map = param;
	if (mlx_is_key_down(map->mlx, MLX_KEY_W))
		if (ft_check_move(map, 3) == 1)
		{
			map->player->instances[0].y += map->diry + 0.5;
			map->player->instances[0].x += map->dirx + 0.5;
			//map->player->instances[0].y -= 1;
		}
	if (mlx_is_key_down(map->mlx, MLX_KEY_S))
		if (ft_check_move(map, 4) == 1)
		{
			map->player->instances[0].y -= map->diry - 0.5;
			map->player->instances[0].x -= map->dirx - 0.5;
			//map->player->instances[0].y += 1;
		}
	if (mlx_is_key_down(map->mlx, MLX_KEY_LEFT))
	{
		map->pa -= 0.1;
		if (map->pa < 0)
		{
			map->pa += 2 * PI;
		}
		map->dirx = cos(map->pa) * 3;
		map->diry = sin(map->pa) * 3;
		printf("y:%f, x:%f\n", map->diry, map->dirx);
		int i = 0;
		double y = map->player->instances[0].y;
		double x = map->player->instances[0].x;
		while (x > -1 && y > -1 && x < 660 && y < 280 && !checkwallhit(map, y, x))
		{
			mlx_put_pixel(map->background, x, y, 535353);
			i++;
			x += map->dirx;
			y += map->diry;
			x++;
			y++;
		}
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_RIGHT))
	{
		map->pa += 0.1;
		if (map->pa > 2 * PI)
		{
			map->pa -= 2 * PI;
		}
		map->dirx = cos(map->pa) * 3;
		map->diry = sin(map->pa) * 3;
		printf("y:%f, x:%f\n", map->diry, map->dirx);
		int i = 0;
		double y = map->player->instances[0].y;
		double x = map->player->instances[0].x;
		while (x > -1 && y > -1 && x < 660 && y < 280 && !checkwallhit(map, y, x))
		{
			mlx_put_pixel(map->background, x, y, 535353);
			i++;
			x += map->dirx;
			y += map->diry;
			x++;
			y++;
		}
	}
}

void	start_window(t_map *map)
{
	map->mlx = mlx_init(660, 280, "Game", false);
	ft_init_textu(map);
	ft_init_img(map->mlx, map);
	mlx_image_to_window(map->mlx, map->background, 0, 0);
	ft_create_wall(map);
	map->dirx = 0;
	map->dirx = cos(map->pa) * 3;
	map->diry = sin(map->pa) * 3;
	map->pa = 5.0;
	mlx_key_hook(map->mlx, ft_key_hook, map);
	mlx_loop_hook(map->mlx, ft_loop_hook, map);
	mlx_loop(map->mlx);
	mlx_terminate(map->mlx);
}

int main(int argc, char **argv)
{
	if (argc != 2)
		exit(1);
	char	*map_name;
	t_map map;

	map_name = argv[1];
	//ft_memset(&map, 0, sizeof(map));
	read_map(&map, map_name);
	start_window(&map);
	return (0);
}