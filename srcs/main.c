#include "../includes/cub3d.h"

#include <stdio.h>

int	ft_check_move(t_map *img, int move)
{
	if (move == 3 && img->mapsave[img->plocation[1] - 1][img->plocation[0]] != '1')
	{
		img->py -= 1;
	}
	else if (move == 4 && img->mapsave[img->plocation[1] + 1][img->plocation[0]] != '1')
	{
		img->py += 1;
	}
	else
		return (0);
	return (1);
}

int checkwallhit(t_map *map, double y, double x)
{
	int yn;
	int xn;

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
	if (map->mapsave[yn + 7][xn - 1] == '1')
		return (1);
	return (0);
}

void	makethewalls(t_map *map)
{
	int length = sqrt(pow(map->cameraposx - map->rayposx, 2) + pow(map->cameraposy - map->rayposy, 2));
	int wall_height;
	if (length > 0)
		wall_height = (20 * screenlength) / length;
	else
		wall_height = (20 * screenlength);
	int	begin;
	int end;
	int y;


	map->fd = 1;


	int i = 0;
	while (i < 20)
	{
		begin = (screenlength / 2) - (wall_height / 3);
 		end = (screenlength / 2) + (wall_height / 3);
		y = begin - 1;
		while  (y < 0)
			y++;
		while (++y < end && y < screenlength)
			mlx_put_pixel(map->background, map->rayamount + i, y, 0XFFFFFF);
		i++;
	}
	//map->lastx = x;
	//map->lasty = y;
}

void shoot_ray(t_map *map)
{
	double yx[2];
	int i = 0;
	yx[1] = map->cameraposy;
	yx[0] = map->cameraposx;
	//printf("y%f x%f | iy%d ix%d\n", yx[1], yx[0], map->player->instances[0].y, map->player->instances[0].x);
	while (!checkwallhit(map, yx[1], yx[0]))
	{
		mlx_put_pixel(map->background, yx[0], yx[1], 0XFFFFFF);
		yx[0] += map->raydirx;
		yx[1] += map->raydiry;
		i++;
	}
	map->rayposx = yx[0];
	map->rayposy = yx[1];
}

void	makethelines(t_map *map)
{
	map->rayamount = screenwidth / 2;
	map->raydiry = map->diry;
	map->raydirx = map->dirx;
	map->raypa = map->pa;


	//shoot_ray(map);
	int i = 0;
	while (i < 60)
	{
		map->rayamount += screenwidth / 120;
		map->raypa += 0.01;
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
	map->raydiry = map->diry;
	map->raydirx = map->dirx;
	map->raypa = map->pa;

	i = 0;
	map->rayamount = screenwidth / 2;
	while (i < 60)
	{
		map->rayamount -= screenwidth / 120;
		map->raypa -= 0.01;
		if (map->raypa < 0)
		{
			map->raypa += 2 * PI;
		}
		map->raydirx = cos(map->raypa);
		map->raydiry = sin(map->raypa);
		shoot_ray(map);
		makethewalls(map);
		i++;
	}
}

void reset(t_map *map)
{
		int abcx = 0;
		int abcy = 0;
		while (abcx <= 1200)
		{
			abcy = 0;
			while (abcy <= 300)
			{
				mlx_put_pixel(map->background, abcx, abcy, 11111111);
				abcy++;
			}
			while (abcy <= 600)
			{
				mlx_put_pixel(map->background, abcx, abcy, 5555555);
				abcy++;
			}
			abcx++;
		}
}

void ft_loop_hook(void *param)
{
	t_map	*map;

	map = param;
	makethelines(map);
	if (mlx_is_key_down(map->mlx, MLX_KEY_W))
	{
		if (ft_check_move(map, 3) == 1)
		{
			//map->player->instances[0].y += map->diry;
			//map->player->instances[0].x += map->dirx;
			map->cameraposy += map->diry;
			map->cameraposx += map->dirx;
			reset(map);
		}
	}
	//else if (mlx_is_key_down(map->mlx, MLX_KEY_S))
	//{
	//   printf("Moving backward: dirx: %f, diry: %f\n", map->dirx, map->diry);
	//	if (ft_check_move(map, 4) == 1)
	//	{
	//		map->player->instances[0].y -= map->diry;
	//		map->player->instances[0].x -= map->dirx;
	//		map->cameraposy -= map->diry;
	//		map->cameraposx -= map->dirx;
	//		reset(map);
	//	}
	//}
	if (mlx_is_key_down(map->mlx, MLX_KEY_LEFT))
	{
		map->pa -= 0.1;
		if (map->pa < 0)
		{
			map->pa += 2 * PI;
		}
		map->dirx = cos(map->pa) * 2;
		map->diry = sin(map->pa) * 2;
		reset(map);

	}
	else if (mlx_is_key_down(map->mlx, MLX_KEY_RIGHT))
	{
		map->pa += 0.1;
		if (map->pa >= 2 * PI)
		{
			map->pa -= 2 * PI;
		}
		map->dirx = cos(map->pa) * 2;
		map->diry = sin(map->pa) * 2;
		reset(map);
	}
}

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_map	*map;

	map = param;

	//double angle = pa / (1.0 + 0.28 * pa * pa);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(map->mlx);
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		{
			reset(map);
		}
}

void	start_window(t_map *map)
{
	map->mlx = mlx_init(screenwidth, screenlength, "Game", false);
	ft_init_textu(map);
	ft_init_img(map->mlx, map);
	reset(map);
	mlx_image_to_window(map->mlx, map->background, 0, 0);
	mlx_put_pixel(map->background, 440, 100, 535353);
	ft_create_wall(map);
	if (map->playerstartpos == 'N')
		map->pa = 0;
	else if (map->playerstartpos == 'S')
		map->pa = -4.8;
	else if (map->playerstartpos == 'E')
		map->pa = 0;
	else if (map->playerstartpos == 'W')
		map->pa = 9.5;
	map->dirx = cos(map->pa) * 3;
	map->diry = sin(map->pa) * 3;
	mlx_key_hook(map->mlx, ft_key_hook, map);
	mlx_loop_hook(map->mlx, ft_loop_hook, map);
//	shoot_ray(map);
	//plot_line(map->cameraposx, map->cameraposy, map->firstray[0] + 20, map->firstray[1], map);
	//plot_line(map->cameraposx, map->cameraposy, map->firstray[0] - 30, map->firstray[1], map);
	//plot_line(map->cameraposx, map->cameraposy, map->firstray[0] + 30, map->firstray[1], map);
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
