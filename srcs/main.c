#include "../includes/cub3d.h"

#include <stdio.h>

int	ft_check_move(t_map *img, int move)
{
	if (move == 1 && img->mapsave[img->plocation[1]][img->plocation[0] - 1] != '1')
	{
		//img->plocation[0] -= 1;
		img->px -= 1;
	}
	else if (move == 2 && img->mapsave[img->plocation[1]][img->plocation[0] + 1] != '1')
	{
		//img->plocation[0] += 1;
		img->px += 1;
	}
	else if (move == 3 && img->mapsave[img->plocation[1] - 1][img->plocation[0]] != '1')
	{
		//img->plocation[1] -= 1;
		img->py -= 1;
	}
	else if (move == 4 && img->mapsave[img->plocation[1] + 1][img->plocation[0]] != '1')
	{
		//img->plocation[1] += 1;
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

void ft_loop_hook(void *param)
{
	t_map	*map;

	map = param;
	double pa = 0.0;
	if (mlx_is_key_down(map->mlx, MLX_KEY_A))
		if (ft_check_move(map, 1) == 1)
			map->player->instances[0].x -= 1;
	if (mlx_is_key_down(map->mlx, MLX_KEY_D))
		if (ft_check_move(map, 2) == 1)
			map->player->instances[0].x += 1;
	if (mlx_is_key_down(map->mlx, MLX_KEY_W))
		if (ft_check_move(map, 3) == 1)
			map->player->instances[0].y -= 1;
	if (mlx_is_key_down(map->mlx, MLX_KEY_S))
		if (ft_check_move(map, 4) == 1)
			map->player->instances[0].y += 1;
	if (mlx_is_key_down(map->mlx, MLX_KEY_LEFT))
	{
		pa -= 0.1;
		if (pa < 0)
		{
			pa += 2 * PI;
			map->dirx = cos(pa) * 5;
			map->diry = sin(pa) * 5;
		}
		int i = 0;
		while (i < 200)
		{
			mlx_put_pixel(map->background, map->dirx, map->diry, 535353);
			i++;
			map->dirx++;
			map->diry++;
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
	map->diry = 0;
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