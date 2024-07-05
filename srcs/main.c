#include "../includes/cub3d.h"

#include <stdio.h>

void	loop_trough(t_map *map, char *str, int count)
{
	static int	player;
	int			i;

	i = 0;
	while(str[i] != '\0')
	{
		if (str[i] == 'N' || str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
		{
			player++;
			map->plocation[0] = i;
			map->plocation[1] = count;
		}
		i++;
	}
	if (player != 1 && i - 1 == map->linecount)
	{
		printf("Wrong amount of player\n");
		exit (1);
	}
}

int check_num(char c)
{
	char *str;
	str = "012";

	while (*str)
	{
		if (c == *str)
			return (1);
		str++;
	}
	return (0);
}

int	wallfloodfill(t_map *map, int posy, int posx)
{
	int i;

	i = 0;
	map->mapcopy[posy][posx] = '2';
	if (map->mapcopy[posy - 1] == NULL
		|| check_num(map->mapcopy[posy - 1][posx]) == 0 
		|| check_num(map->mapcopy[posy + 1][posx]) == 0
		|| check_num(map->mapcopy[posy][posx + 1]) == 0
		|| check_num(map->mapcopy[posy][posx - 1]) == 0)
		return (1);
	if (map->mapcopy[posy + 1][posx] == '0' && i == 0)
		i = wallfloodfill(map, posy + 1, posx);
	if (map->mapcopy[posy][posx + 1] == '0' && i == 0)
		i = wallfloodfill(map, posy, posx + 1);
	if (map->mapcopy[posy - 1][posx] == '0' && i == 0)
		i = wallfloodfill(map, posy - 1, posx);
	if (map->mapcopy[posy][posx - 1] == '0' && i == 0)
		i = wallfloodfill(map, posy, posx - 1);
	return (i);
}

void	save_map(t_map *map, char *map_name)
{
	char	**arr;
	int		fd;
	int		count;

	count = 0;
	fd = open(map_name, O_RDONLY);
	arr = malloc((map->linecount + 1) * sizeof(char *));
	while (count != map->linecount)
	{
		arr[count] = get_next_line(fd);
		if (count > 7)
			loop_trough(map, arr[count], count);
		count++;
	}
	arr[count] = 0;
	map->mapcopy = arr;
	map->mapsave = arr;
	if (wallfloodfill(map, map->plocation[1], map->plocation[0]) == 1)
	{
		printf("Walls not closed!\n");
		//exit(1);
	}
	count = 0;
	close(fd);
}

void read_map(t_map *map, char *map_name)
{
	char	*line;
	int		count;
	int		fd;

	count = 0;
	fd = open(map_name, O_RDONLY);
    line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		count++;
	}
	close(fd);
	map->linecount = count;
	save_map(map, map_name);
}

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_map	*map;

	map = param;
	int y;
	int x;
	y = 0;
	x = 0;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(map->mlx);
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
	{
		map->player->instances[0].x -= 20;
		map->px -= 20;
	}
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
	{
		map->player->instances[0].x += 20;
		map->px += 20;
	}
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
	{
		map->player->instances[0].y -= 20;
		map->py -= 20;
	}
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
	{
		map->player->instances[0].y += 20;
		map->py += 20;
	}
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
	{
		ft_printf("x:%dy:%d", map->py, map->px);
		x = map->px;
		y = map->py;
		while (y < 1000 && x < 2000 && y > -1 && x > -1)
		{
			mlx_put_pixel(map->background, x, y, 828282);
			y--;
			//x++;
		}
	}
	//if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
	//{
	//	ft_printf("x:%dy:%d", map->py, map->px);
	//	x = map->px;
	//	y = map->py;
	//	while (y < 1000 && x < 2000 && y > -1 && x > -1)
	//	{
	//		mlx_put_pixel(map->background, x, y, 828282);
	//		y--;
	//		//x++;
	//	}
	//}
	//if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
	//		map->player->instances[0].x += 20;
	//if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
	//		map->player->instances[0].y -= 20;
	//if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
	//		map->player->instances[0].y += 20;
}

void	start_window(t_map *map)
{
	map->mlx = mlx_init(2000, 1000, "Game", false);
	ft_init_textu(map);
	ft_init_img(map->mlx, map);
	mlx_image_to_window(map->mlx, map->background, 0, 0);
	mlx_image_to_window(map->mlx, map->player, 1000, 500);
	map->px = 1000 + 10;
	map->py = 500;
	map->dirx = -1;
	map->diry = 0;
	mlx_key_hook(map->mlx, ft_key_hook, map);
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
