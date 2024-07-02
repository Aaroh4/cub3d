#include "../includes/cub3d.h"

void	save_map(t_map *map)
{
	map->mapsave = malloc((map->linecount + 1) * sizeof(char *));
    *map->mapsave = get_next_line(map->fd);
	while (*map->mapsave != NULL)
	{
		map->mapsave++;
		*map->mapsave = get_next_line(map->fd);
	}
}

void read_map(t_map *map)
{
	char	*line;
	int		count;

    line = get_next_line(map->fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(map->fd);
		count++;
	}
	map->linecount = count;
	save_map(map);
}

int main(int argc, char **argv)
{
	int	fd;
	t_map map;

	ft_memset(&map, 0, sizeof(map));
	map.fd = open(argv[1], O_RDONLY);
	read_map(&map);
	return (0);
}
