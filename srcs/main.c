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
	int i;
	int yn;
	int xn;

	i = 0;
	yn = 0;
	xn = 0;
	while (x >= 0)
	{
		xn++;
		x -= 20;
	}
	while (y >= 0)
	{
		yn++;
		y -= 20;
	}
	while (i < map->wallcount)
	{
		if (map->mapsave[yn + 7][xn - 1] == '1')
			return (1);
		i++;
	}
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

	begin = (screenlength / 2) - (wall_height / 3);
 	end = (screenlength / 2) + (wall_height / 3);
	y = begin - 1;
	while  (y < 0)
		y++;
	while (++y < end && y < screenlength)
		mlx_put_pixel(map->background, map->rayamount * 14, y, 0XFFFFFF);
	//map->lastx = x;
	//map->lasty = y;
}

void plot_line (int x0, int y0, int x1, int y1, t_map *map)
{
  int dx;
  dx = abs (x1 - x0);
  int sx; 
  sx = x0 < x1 ? 1 : -1;
  int dy; 
  dy = -abs (y1 - y0);
  int sy;
  sy = y0 < y1 ? 1 : -1;
  int err;
  err = dx + dy;
  int e2;

  while (!checkwallhit(map, y0, x0))
  {
  // printf("x:%d y:%d\n", x0, y0);
  //mlx_put_pixel(map->background, x0, y0, 535353);
  //  if (x0 == x1 && y0 == y1) 
	//	break;
    e2 = 2 * err;
    if (e2 >= dy) 
	{ 
		err += dy;
		x0 += sx; 
	}
    if (e2 <= dx) 
	{
		err += dx;
		y0 += sy;
	}
  }
  map->rayposy = y0;
  map->rayposx = x0;
}

void shoot_ray(t_map *map)
{
	double yx[2];
	int i = 0;
	yx[1] = map->cameraposy + 10;
	yx[0] = map->cameraposx + 10;
	//printf("y%f x%f | iy%d ix%d\n", yx[1], yx[0], map->player->instances[0].y, map->player->instances[0].x);
	while (!checkwallhit(map, yx[1], yx[0]))
	{
		mlx_put_pixel(map->background, yx[0], yx[1], 0);
		yx[0] += map->dirx - 0.25;
		yx[1] += map->diry;
		i++;
	}
	map->firstray[0] = yx[0];
	map->firstray[1] = yx[1];
}

void	makethelines(t_map *map)
{
	int i = 1;
	map->rayamount = 0;
	while (i++ <= 90)
	{
		map->rayamount += 1;
		if (map->diry > 2 || map->diry < -2)
		{
			if (map->rayamount < 45)
			{
				plot_line(map->cameraposx + 10, map->cameraposy + 10, map->firstray[0] - i, map->firstray[1], map);
				makethewalls(map);
			}
			else if (map->rayamount > 45)
			{
				plot_line(map->cameraposx + 10, map->cameraposy + 10, map->firstray[0] + i, map->firstray[1], map);
				makethewalls(map);
			}
		}
		else
		{
			if (map->rayamount < 45)
			{
				plot_line(map->cameraposx + 10, map->cameraposy + 10, map->firstray[0], map->firstray[1] - i, map);
				makethewalls(map);
			}
			else if (map->rayamount > 45)
			{
				plot_line(map->cameraposx + 10, map->cameraposy + 10, map->firstray[0], map->firstray[1] + i, map);
				makethewalls(map);
			}
		}
	}
	plot_line(map->cameraposx, map->cameraposy, map->firstray[0], map->firstray[1], map);
	map->rayamount = 45;
	makethewalls(map);
}

void reset(t_map *map)
{
		int abcx = 0;
		int abcy = 0;
		while (abcx <= 1200)
		{
			abcy = 0;
			while (abcy <= 600)
			{
				mlx_put_pixel(map->background, abcx, abcy, 535353);
				abcy++;
			}
			abcx++;
		}
}

void ft_loop_hook(void *param)
{
	t_map	*map;

	map = param;
	shoot_ray(map);
	makethelines(map);
	if (mlx_is_key_down(map->mlx, MLX_KEY_W))
		if (ft_check_move(map, 3) == 1)
		{
			map->player->instances[0].y += map->diry + 0.5;
			map->player->instances[0].x += map->dirx + 0.5;
			map->cameraposy += map->diry + 0.5;
			map->cameraposx += map->dirx + 0.5;
			reset(map);
		}
	if (mlx_is_key_down(map->mlx, MLX_KEY_S))
		if (ft_check_move(map, 4) == 1)
		{
			map->player->instances[0].y -= map->diry - 0.5;
			map->player->instances[0].x -= map->dirx - 0.5;
			map->cameraposy -= map->diry - 0.5;
			map->cameraposx -= map->dirx - 0.5;
			reset(map);
		}
	//if (mlx_is_key_down(map->mlx, MLX_KEY_A))
	//	if (ft_check_move(map, 4) == 1)
	//	{
	//		map->player->instances[0].y -= map->diry - 0.5;
	//		map->player->instances[0].x -= map->dirx - 0.5;
	//		//map->cameraposy -= map->diry - 0.5;
	//		//map->cameraposx -= map->dirx - 0.5;
	//		reset(map);
	//	}
	//if (mlx_is_key_down(map->mlx, MLX_KEY_D))
	//	if (ft_check_move(map, 4) == 1)
	//	{
	//		map->player->instances[0].y -= map->diry - 0.5;
	//		map->player->instances[0].x -= map->dirx - 0.5;
	//		map->cameraposy -= map->diry - 0.5;
	//		map->cameraposx -= map->dirx - 0.5;
	//		reset(map);
	//	}
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
		//printf("y:%f, x:%f\n", map->diry, map->dirx);

	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_RIGHT))
	{
		map->pa += 0.1;
		if (map->pa > 2 * PI)
		{
			map->pa -= 2 * PI;
		}
		map->dirx = cos(map->pa) * 2;
		map->diry = sin(map->pa) * 2;
		reset(map);
		//printf("y:%f, x:%f\n", map->diry, map->dirx);
	}
}

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_map	*map;

	map = param;

	//double angle = pa / (1.0 + 0.28 * pa * pa);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(map->mlx);
}

void	start_window(t_map *map)
{
	map->mlx = mlx_init(screenwidth, screenlength, "Game", false);
	ft_init_textu(map);
	ft_init_img(map->mlx, map);
	mlx_image_to_window(map->mlx, map->background, 0, 0);
	mlx_put_pixel(map->background, 440, 100, 535353);
	ft_create_wall(map);
	if (map->playerstartpos == 'N')
		map->pa = 4.8;
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
