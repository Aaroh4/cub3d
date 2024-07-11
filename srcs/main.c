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
	while (i < map->wallcount)
	{
		if (map->mapcopy[yn + 7][xn - 1] == '1')
			return (1);
		i++;
	}
	return (0);
}

void ft_loop_hook(void *param)
{
	t_map	*map;

	map = param;
	double test = 2.5;
	int i2 = 0;
	if (mlx_is_key_down(map->mlx, MLX_KEY_W))
		if (ft_check_move(map, 3) == 1)
		{
			map->player->instances[0].y += map->diry + 0.5;
			map->player->instances[0].x += map->dirx + 0.5;
			//map->player->instances[0].y -= 1;
			//int	i2 = 0;
			//double test = 0.1;
			while (map->lasti >= 0)
			{
				printf("last: y:%f x:%f\n", map->lasty, map->lastx);
				i2 = 0;
				while (i2 < 10)
				{
					mlx_put_pixel(map->background, map->lastx + test * i2, map->lasty + test * i2, 0xFFFFFFFF);
					i2++;
				}
				map->lastx -= map->lastdirx;
				map->lasty -= map->lastdiry;
				map->lasti--;
			}
			int i = 0;
			//int booltest[20];
			double y = map->player->instances[0].y;
			double x = map->player->instances[0].x;
			while (x > -1 && y > -1 && x < 660 && y < 280)
			{
				printf("real: y:%f x:%f\n", y, x);
				//while (i2 < 1)
				//{
				//mlx_put_pixel(map->background, x, y, 535353);
				i2 = 0;
				while (i2 < 10)
				{
					//if (booltest[i2] == 0 &&!checkwallhit(map, y + test * i2, x + test * i2) )
					mlx_put_pixel(map->background, x + test * i2, y + test * i2, 535353);
					//else
					//	booltest[i2] = 1;
					i2++;
				}
				//	i2++;
				//}
				map->lastx = x;
				map->lasty = y;
				map->lastdirx = map->dirx;
				map->lastdiry = map->diry;
				map->lasti = i;
				i++;
				x += map->dirx;
				y += map->diry;
			}
		}
	if (mlx_is_key_down(map->mlx, MLX_KEY_S))
		if (ft_check_move(map, 4) == 1)
		{
			map->player->instances[0].y -= map->diry - 0.5;
			map->player->instances[0].x -= map->dirx - 0.5;
			//map->player->instances[0].y += 1;
			while (map->lasti >= 0)
			{
				printf("last: y:%f x:%f\n", map->lasty, map->lastx);
				i2 = 0;
				while (i2 < 20)
				{
					mlx_put_pixel(map->background, map->lastx + test * i2, map->lasty + test * i2, 0xFFFFFFFF);
					i2++;
				}
				map->lastx -= map->lastdirx;
				map->lasty -= map->lastdiry;
				map->lasti--;
			}
			int i = 0;
		//	double ytest;
		//	double xtest;
			double y = map->player->instances[0].y;
			double x = map->player->instances[0].x;
			while (x > -1 && y > -1 && x < 660 && y < 280 && !checkwallhit(map, y, x))
			{
				printf("real: y:%f x:%f\n", y, x);
				//while (i2 < 1)
				//{
				//mlx_put_pixel(map->background, x, y, 535353);
				i2 = 0;
				while (!checkwallhit(map, y + test * i2, x + test * i2) && i2 < 20)
				{
					mlx_put_pixel(map->background, x + test * i2, y + test * i2, 535353);
					i2++;
				}
				//	i2++;
				//}
				map->lastx = x;
				map->lasty = y;
				map->lastdirx = map->dirx;
				map->lastdiry = map->diry;
				map->lasti = i;
				i++;
				x += map->dirx;
				y += map->diry;
			}
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
			while (map->lasti >= 0)
			{
				printf("last: y:%f x:%f\n", map->lasty, map->lastx);
				i2 = 0;
				while (i2 < 20)
				{
					mlx_put_pixel(map->background, map->lastx + test * i2, map->lasty + test * i2, 0xFFFFFFFF);
					i2++;
				}
				map->lastx -= map->lastdirx;
				map->lasty -= map->lastdiry;
				map->lasti--;
			}
			int i = 0;
		//	double ytest;
		//	double xtest;
			double y = map->player->instances[0].y;
			double x = map->player->instances[0].x;
			while (x > -1 && y > -1 && x < 660 && y < 280 && !checkwallhit(map, y, x))
			{
				printf("real: y:%f x:%f\n", y, x);
				//while (i2 < 1)
				//{
				//mlx_put_pixel(map->background, x, y, 535353);
				i2 = 0;
				while (!checkwallhit(map, y + test * i2, x + test * i2) && i2 < 20)
				{
					mlx_put_pixel(map->background, x + test * i2, y + test * i2, 535353);
					i2++;
				}
				//	i2++;
				//}
				map->lastx = x;
				map->lasty = y;
				map->lastdirx = map->dirx;
				map->lastdiry = map->diry;
				map->lasti = i;
				i++;
				x += map->dirx;
				y += map->diry;
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
			while (map->lasti >= 0)
			{
				printf("last: y:%f x:%f\n", map->lasty, map->lastx);
				i2 = 0;
				while (i2 < 10)
				{
					mlx_put_pixel(map->background, map->lastx + test * i2, map->lasty + test * i2, 0xFFFFFFFF);
					i2++;
				}
				map->lastx -= map->lastdirx;
				map->lasty -= map->lastdiry;
				map->lasti--;
			}
			int i = 0;
			//int booltest[20];
			double y = map->player->instances[0].y;
			double x = map->player->instances[0].x;
			while (x > -1 && y > -1 && x < 660 && y < 280)
			{
				printf("real: y:%f x:%f\n", y, x);
				//while (i2 < 1)
				//{
				//mlx_put_pixel(map->background, x, y, 535353);
				i2 = 0;
				while (i2 < 10)
				{
					//if (booltest[i2] == 0 &&!checkwallhit(map, y + test * i2, x + test * i2) )
						mlx_put_pixel(map->background, x + test * i2, y + test * i2, 535353);
					//else
					//	booltest[i2] = 1;
					i2++;
				}
				//	i2++;
				//}
				map->lastx = x;
				map->lasty = y;
				map->lastdirx = map->dirx;
				map->lastdiry = map->diry;
				map->lasti = i;
				i++;
				x += map->dirx;
				y += map->diry;
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
	ft_memset(&map, 0, sizeof(map));
	read_map(&map, map_name);
	start_window(&map);
	return (0);
}