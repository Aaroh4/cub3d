#include "../includes/cub3d.h"

#include <stdio.h>

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
		arr[count] = get_next_line(map->fd);
		printf(arr[count]);
		count++;
	}
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

int main(int argc, char **argv)
{
	int	fd;
	char	*map_name;
	t_map map;

	map_name = argv[1];
//	ft_memset(&map, 0, sizeof(map));
	read_map(&map, map_name);
	return (0);
}
