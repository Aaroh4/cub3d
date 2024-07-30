/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapchecker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 09:53:08 by ahamalai          #+#    #+#             */
/*   Updated: 2024/07/30 15:21:04 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#include <stdio.h>

void	loop_trough(t_map *map, char *str, int count)
{
	static int	player;
	int			i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 'N' || str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
		{
			player++;
			map->playerstartpos = str[i];
			map->plocation[0] = i;
			map->plocation[1] = count;
			map->cameraposx = 20 * i + 10;
			map->cameraposy = 20 * (count - 8) + 10;
		}
		if (str[i] == '1')
			map->wallcount++;
		i++;
	}
	if (i > map->lenght)
		map->lenght = i;
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

void	map_save(t_map *map)
{
	int	i;
	int j;

	i = 0;
	map->mapsave = malloc((map->linecount + 1) * (sizeof(char *)));
	//
	//
	while (i < map->linecount)
	{
		map->mapsave[i] = malloc((map->lenght + 1) * (sizeof(char *)));
		//
		//
		j = 0;
		while (j <= map->lenght)
		{
			if (j <= ft_strlen(map->mapcopy[i]))
				map->mapsave[i][j] = map->mapcopy[i][j];
			else
				map->mapsave[i][j] = '0';
			j++;
		}
		i++;
	}	
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
	map_save(map);
	printf("x%d\n y%d\n", map->plocation[0], map->plocation[1]);
	if (wallfloodfill(map, map->plocation[1], map->plocation[0]) == 1)
	{
		printf("Walls not closed!\n");
		exit(1);
	}
	close(fd);
}

void read_map(t_map *map, char *map_name)
{
	char	*line;
	int		count;
	int		fd;

	count = 0;
	map->wallcount = 0;
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
