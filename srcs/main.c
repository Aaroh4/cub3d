#include "../includes/cub3d.h"

#include <stdio.h>

void draw_line(int x, int y, t_map *map)
{
	if(map->side == 0 && map->raydirx > 0)
	{
		if (map->mapy % 2 == 0)
				mlx_put_pixel(map->background, x, y, 0XFFFFFFFF);
		else
				mlx_put_pixel(map->background, x, y, 00000000);
	}
	else if(map->side == 1 && map->raydiry < 0)
	{
		if (map->mapx % 2 == 0)
				mlx_put_pixel(map->background, x, y, 3333333333);
		else
				mlx_put_pixel(map->background, x, y, 00000000);
	}
	else if (map->side == 1 && map->raydiry > 0)
	{
		if (map->mapx % 2 == 0)
			mlx_put_pixel(map->background, x, y, 66666666);
		else
			mlx_put_pixel(map->background, x, y, 00000000);
	}
	else
	{
		if (map->mapy % 2 == 0)
			mlx_put_pixel(map->background, x, y, 6666666666);
		else
			mlx_put_pixel(map->background, x, y, 00000000);
	}
}

void	makethewalls(t_map *map)
{
	double lengtha;
	if (map->side == 0)
		lengtha = (map->rayposx - map->deltadistx);
	else
		lengtha = (map->rayposy - map->deltadisty);
	double correct = (map->pa - map->raypa);
	lengtha *= cos(correct);
	int wall_height = screenlength / lengtha;
	int i = 0;
	int untily;
	int drawStart = -wall_height / 2 + screenlength / 2;
    if(drawStart < 0) drawStart = 0;
    int drawEnd = wall_height / 2 + screenlength / 2;
    if(drawEnd >= screenlength) drawEnd = screenlength - 1;
	untily = 0;
	while (i < screenlength)
	{
		if (i < drawStart)
			mlx_put_pixel(map->background, map->rayamount, i, 11111111);
		else if (i >= drawStart && i <= drawEnd)
		{
			draw_line(map->rayamount, i, map);
		}
		else if (i > drawEnd)
			mlx_put_pixel(map->background, map->rayamount, i, 00000000);
		i++;
	}
}

void shoot_ray(t_map *map)
{
	//int yx[2];
	int i = 0;
	//yx[1] = (int)map->cameraposy;
	//yx[0] = (int)map->cameraposx;

	map->mapy = map->cameraposy;
	map->mapx = map->cameraposx;
	//printf("y%d x%d\n", map->mapy, map->mapx);
	map->deltadistx = sqrt(1 + (map->raydiry * map->raydiry) / (map->raydirx * map->raydirx));
	map->deltadisty = sqrt(1 + (map->raydirx * map->raydirx) / (map->raydiry * map->raydiry));

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
	//if (map->cameraposy < 1 || map->cameraposy > map->linecount - 8 || map->cameraposx < 1)
	//{
	//	map->rayposx = -1;
	//	map->rayposy = -1;
	//	return ;
	//}
	while (1)
	{
		//mlx_put_pixel(map->background, map->rayposx, map->rayposy, 0XFFFFFF);
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
		//if (map->mapx < ft_strlen(map->mapsave[map->mapy + 8]) - 1)
		//{
		//	map->rayposx = -1;
		//	map->rayposy = -1;
		//	return ;
		//}
		if (map->mapsave[map->mapy + 8][map->mapx] == '1')
			break ;
	}
}

void	makethelines(t_map *map)
{
	map->rayamount = 0;
	map->raydiry = map->diry;
	map->raydirx = map->dirx;
	map->raypa = map->pa - DEGREE * FOV / 2;

	//shoot_ray(map);
	//makethewalls(map);
	//shoot_ray(map);
	
	int i = 0;
	while (i < screenwidth)
	{
		map->rayamount += 1;
		map->raypa += DEGREE / (double)(screenwidth / FOV);
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
				mlx_put_pixel(map->background, abcx, abcy, 00000000);
				abcy++;
			}
			abcx++;
		}
}

void ft_loop_hook(void *param)
{
	t_map	*map;

	map = param;
	//printf("posy%d\n", map->cameraposx);
	makethelines(map);
	if (mlx_is_key_down(map->mlx, MLX_KEY_W))
	{
		map->cameraposy += map->diry / 2;
		map->cameraposx += map->dirx / 2;
	//	reset(map);
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_S))
	{
		map->cameraposy -= map->diry / 2;
		map->cameraposx -= map->dirx / 2;
	//	reset(map);
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_A))
	{
		map->cameraposy -= map->dirx / 3;
		map->cameraposx -= -map->diry / 3;
	//	reset(map);
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_D))
	{
		map->cameraposy += map->dirx / 3;
		map->cameraposx += -map->diry / 3;
	//	reset(map);
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_LEFT))
	{
		map->pa -= 0.05;
		if (map->pa < 0)
		{
			map->pa += 2 * PI;
		}
		map->dirx = cos(map->pa) / 5;
		map->diry = sin(map->pa) / 5;
	//	reset(map);
	}
	else if (mlx_is_key_down(map->mlx, MLX_KEY_RIGHT))
	{
		map->pa += 0.05;
		if (map->pa >= 2 * PI)
		{
			map->pa -= 2 * PI;
		}
		map->dirx = cos(map->pa) / 5;
		map->diry = sin(map->pa) / 5;
	//	reset(map);
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
	//ft_create_wall(map);
	if (map->playerstartpos == 'N')
		map->pa = 4.74;
	else if (map->playerstartpos == 'S')
		map->pa = -4.74;
	else if (map->playerstartpos == 'E')
		map->pa = 0;
	else if (map->playerstartpos == 'W')
		map->pa = 9.5;
	map->dirx = cos(map->pa) / 5;
	map->diry = sin(map->pa) / 5;
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
