#include "../includes/cub3d.h"

#include <stdio.h>

void getting_index(t_map *map)
{
	if(map->side == 1)
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
//	printf("%f\n", map->wall.x);
}

int calculate_wall(t_map *map)
{
	double length;
	double height;
	if (map->side == 0)
		length = (map->rayposx - map->deltadistx);
	else
		length = (map->rayposy - map->deltadisty);
	double correct = (map->pa - map->raypa);
	getting_index(map);
	if (map->side == 0) 
		map->wallX = map->cameraposy + length * map->raydiry;
	else           
		map->wallX = map->cameraposx + length * map->raydirx;
    map->wallX -= floor((map->wallX));
	length *= cos(correct);
	height = (STEPSIZE * screenlength) / length;
	map->wall.ty_off = 0;
	map->wall.ty_step = map->wall.txt[map->wall.side]->height / height;
	if (height > screenlength)
	{
		map->wall.ty_off = (height - screenlength) / 2;
		height = screenlength;
	}
	map->wall.y = map->wall.ty_off * map->wall.ty_step;
	return (height);
}

void draw_line(int x, int y, t_map *map)
{
	mlx_texture_t	*wall;
	int height = map->wall.txt[map->wall.side]->height;
	int				offset = 0;
	uint32_t		pixel = 0;

	wall = map->wall.txt[map->wall.side];
	offset = (((int)map->wall.y * map->wall.txt[map->wall.side]->height + (int)(map->wallX * map->wall.txt[map->wall.side]->width)))
		* sizeof(uint32_t);
	if (offset < (height * height * 4))
		pixel = (wall->pixels[offset] << 24) | (wall->pixels[offset + 1] << 16)
			| (wall->pixels[offset + 2] << 8) | wall->pixels[offset + 3];
	mlx_put_pixel(map->background, x, y, pixel);
	map->wall.y += map->wall.ty_step;
}

void	makethewalls(t_map *map)
{
	int wall_height = calculate_wall(map);
	int i = 0;
	int untily;
	int drawStart = -wall_height / 2 + screenlength / 2;
    if(drawStart < 0) 
		drawStart = 0;
    int drawEnd = wall_height / 2 + screenlength / 2;
	untily = 0;
	while (i < screenlength)
	{
		if (i < drawStart)
		{
			mlx_put_pixel(map->background, map->rayamount, i, 0xFFFFFFF);
		}
		else if (i >= drawStart && i <= drawEnd)
		{
			draw_line(map->rayamount, i, map);
		}
		else if (i > drawEnd)
		{
			mlx_put_pixel(map->background, map->rayamount, i, 888888888);
		}
		i++;
	}
}

int checkarraysize(char **arr)
{
	int i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

void shoot_ray(t_map *map)
{
	map->mapy = map->cameraposy;
	map->mapx = map->cameraposx;
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
		if (checkarraysize(map->mapsave) <= map->mapy || map->mapy < 0 || map->mapx < 0 || (int)ft_strlen(map->mapsave[map->mapy]) < map->mapx)
		{
			map->rayposx = 2;
			map->rayposy = 2;
			map->deltadisty = 1;
			map->deltadistx = 1;
			break ;
		}
		if (map->mapsave[map->mapy][map->mapx] == '1')
			break ;
	}
}

void	makethelines(t_map *map)
{
	map->rayamount = -1;
	map->raydiry = map->diry;
	map->raydirx = map->dirx;
	map->raypa = map->pa - DEGREE * FOV / 2;

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

	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(map->mlx);
}

void	start_window(t_map *map)
{
	map->mlx = mlx_init(screenwidth, screenlength, "Game", false);
	ft_init_textu(map);
	//reset(map);
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

int	main(int argc, char **argv)
{
	char	*map_name;
	int		count;
	if (argc != 2 || screenwidth > 3000 || screenlength > 1500)
		exit(1);
	t_map map;

	argument_check(argv[1]);
	count = 0;
	map_name = argv[1];
	count = count_file_lines(map_name, count);
	read_file(map_name, count, &map);
	start_window(&map);
	return (0);
}

//int main(int argc, char **argv)
//{
//	if (argc != 2 || screenwidth > 3000 || screenlength > 1500)
//		exit(1);
//	char	*map_name;
//	t_map map;

//	//argument_check(argv[1]);
//	map_name = argv[1];
//	ft_memset(&map, 0, sizeof(map));
//	read_map(&map, map_name);
//	printf("%s\n", map.mapsave[0]);
//	printf("%s\n", map.mapsave[1]);
//	printf("%s\n", map.mapsave[2]);
//	printf("%s\n", map.mapsave[3]);
//	int i = 0;
//	while (map.mapsave[i] != NULL)
//	{
//		printf("%s\n", map.mapsave[i]);
//		i++;
//	}
//	start_window(&map);
//	return (0);
//}


// split up the whole read map, check the file, all the input in the file, is it valid is it not, if ok
// put it to the sturct that we use for the game otehrwise free everything and exit with correct error message!
