/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapchecker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 09:53:08 by ahamalai          #+#    #+#             */
/*   Updated: 2024/08/14 15:29:30 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../includes/cub3d.h"

//#include <stdio.h>

//void	invalid_input(char *str)
//{
//	ft_putstr_fd(str, 2);
//	exit(1);
//}

//void	loop_trough(t_map *map, char *str, int count)
//{
//	static int	player;
//	int			i;

//	i = 0;
//	while (str[i] != '\0')
//	{
//		if (str[i] == 'N' || str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
//		{
//			player++;
//			map->playerstartpos = str[i];
//			map->plocation[0] = i;
//			map->plocation[1] = count;
//			map->cameraposx = i + 0.5;
//			map->cameraposy = (count - 8) + 0.5;
//		}
//		if (str[i] == '1')
//			map->wallcount++;
//		i++;
//	}
//	if (i > map->lenght)
//		map->lenght = i;
//	if (player != 1 && i - 1 == map->linecount)
//	{
//		printf("Error\nWrong amount of player\n");
//		exit (1);
//	}
//}

//int check_num(char c)
//{
//	char *str;
//	str = "012";

//	while (*str)
//	{
//		if (c == *str)
//			return (1);
//		str++;
//	}
//	return (0);
//}

//int	wallfloodfill(t_map *map, int posy, int posx)
//{
//	int i;

//	i = 0;
//	map->mapcopy[posy][posx] = '2';
//	if (map->mapcopy[posy - 1] == NULL
//		|| check_num(map->mapcopy[posy - 1][posx]) == 0 
//		|| check_num(map->mapcopy[posy + 1][posx]) == 0
//		|| check_num(map->mapcopy[posy][posx + 1]) == 0
//		|| check_num(map->mapcopy[posy][posx - 1]) == 0)
//		return (1);
//	if (map->mapcopy[posy + 1][posx] == '0' && i == 0)
//		i = wallfloodfill(map, posy + 1, posx);
//	if (map->mapcopy[posy][posx + 1] == '0' && i == 0)
//		i = wallfloodfill(map, posy, posx + 1);
//	if (map->mapcopy[posy - 1][posx] == '0' && i == 0)
//		i = wallfloodfill(map, posy - 1, posx);
//	if (map->mapcopy[posy][posx - 1] == '0' && i == 0)
//		i = wallfloodfill(map, posy, posx - 1);
//	return (i);
//}

//void	map_save(t_map *map)
//{
//	int	i;
//	int j;

//	i = map->map_start;
//	map->mapsave = malloc((map->linecount + 1) * (sizeof(char *)));
//	//
//	//
//	while (i < map->linecount)
//	{
//		map->mapsave[i] = malloc((map->lenght + 1) * (sizeof(char *)));
//		//
//		//
//		j = 0;
//		while (j <= map->lenght)
//		{
//			if (j <= (int)ft_strlen(map->mapcopy[i]))
//				map->mapsave[i][j] = map->mapcopy[i][j];
//			// else
//			// 	map->mapsave[i][j] = '0';
//			j++;
//		}
//		i++;
//	}	
//} 

//char	*ft_strduping(const char *src)
//{
//	char	*str;
//	int		i;
//	int		ai;

//	i = 0;
//	ai = 0;
//	while (src[ai])
//	{
//		ai++;
//	}
//	ai++;
//	str = malloc(sizeof(char) * ai);
//	ai--;
//	if (str == 0)
//		return (0);
//	while (src[i] != '\0')
//	{
//		str[i] = src[i];
//		i++;
//	}
//	str[i] = '\0';
//	return (str);
//}

//char	*check_and_set_info(char *str, char *info)
//{
//	// while (*str == ' ')
//	// 	str++;
//	if (!info)
//		info = ft_strduping(str);
//	else
//	{
//		ft_putstr_fd("duplicate input\n", 2);
//		exit (1);
//	}
//	return (info);
//}

//int	extract_and_set_info(char *str, int info_set, t_map	*map)
//{
//	if (str && ((ft_strnstr(str, "NO", (size_t)ft_strlen(str)) != 0)))
//	{
//	 	info_set++;
//		map->north = check_and_set_info(str, map->north);
//		// map->north = malloc((ft_strlen(str) + 1));
//		// ft_strlcpy(map->north, str, ft_strlen(str));
// 	}
//	if (str && ((ft_strnstr(str, "SO", (size_t)ft_strlen(str)) != 0)))
//	{
//		info_set++;
//		map->south = check_and_set_info(str, map->south);
//		// map->south = malloc((ft_strlen(str) + 1));
//		// ft_strlcpy(map->south, str, ft_strlen(str));
//	}
//	if (str && ((ft_strnstr(str, "WE", (size_t)ft_strlen(str)) != 0)))
//	{
//		info_set++;
//		map->west = check_and_set_info(str, map->west);
//		// map->west = malloc((ft_strlen(str) + 1));
//		// ft_strlcpy(map->west, str, ft_strlen(str));
//	}
//	if (str && ((ft_strnstr(str, "EA", (size_t)ft_strlen(str)) != 0)))
//	{
//		info_set++;
//		map->east = check_and_set_info(str, map->east);
//		// map->east = malloc((ft_strlen(str) + 1));
//		// ft_strlcpy(map->east, str, ft_strlen(str));
//	}
//	if (str && (ft_strnstr(str, "F", (size_t)ft_strlen(str)) != 0))
//	{
//		info_set++;
//		map->surface = check_and_set_info(str, map->surface);
//		// map->surface = malloc((ft_strlen(str) + 1));
//		// ft_strlcpy(map->surface, str, ft_strlen(str));
//	}
//	if (str && (ft_strnstr(str, "C", (size_t)ft_strlen(str)) != 0))
//	{
//		info_set++;
//		map->sky = check_and_set_info(str, map->sky);
//		// map->sky = malloc((ft_strlen(str) + 1));
//		// ft_strlcpy(map->sky, str, ft_strlen(str));
//	}
//	return (info_set);
//}

//void	get_map_information(t_map *map, char *map_name)
//{
//	int		i;
//	char	*info;
//	int		fd1;
//	int		info_set;
//	int		map_reached;

//	i = 0;
//	info_set = 0;
//	map_reached = 0;
//	info = NULL;
//	fd1 = open(map_name, O_RDONLY);
//	while (i <= map->linecount)
//	{
//	 	info = get_next_line(fd1);
//	 	info_set = extract_and_set_info(info, info_set, map);
//		if (info_set > 6)
//		{
//			if(info && (info[0] == '\n' && map_reached == 0))
//			{
//				free(info);
//				i++;
//				continue;
//			}
//			if (info && info[0] != '\n')
//				map_reached = 1;
//			if (info && (info[0] == '\n' && map_reached == 1))
//			{
//				free(info);
//				invalid_input("Error\nMap not complete\n");
//			}
//		}
//		free(info);
//	 	i++;
//		if (info_set == 6)
//		{
//			map->map_start = i;
//			info_set = info_set + 1;
//		}
//	}
//	close(fd1);
//}

//void	save_map(t_map *map, char *map_name)
//{
//	char	**arr;
//	int		fd;
//	int		count;

//	count = 0;
//	arr = malloc((map->linecount + 1) * sizeof(char *));
//	get_map_information(map, map_name);
//	fd = open(map_name, O_RDONLY);
//	while (count < map->linecount)
//	{
//		arr[count] = get_next_line(fd);
//		if (count > map->map_start)
//		{
//			// printf("count: %d test:%s\n",count, arr[count]);
//			loop_trough(map, arr[count], count);
//		}
//		count++;
//	}
//	arr[count] = 0;
//	map->mapcopy = arr;
//	map_save(map);
//	if (wallfloodfill(map, map->plocation[1], map->plocation[0]) == 1)
//	{
//		printf("Walls not closed!\n");
//		exit(1);
//	}
//	// printf("\n");
//	// int	k = 0;
//	// while (arr[k])
//	// {
//	// 	printf("%s", arr[k]);
//	// 	k++;
//	// }
//	close(fd);
//}

//void read_map(t_map *map, char *map_name)
//{
//	char	*line;
//	int		count;
//	int		fd;

//	count = 0;
//	map->wallcount = 0;
//	fd = open(map_name, O_RDONLY);
//	if (fd == -1)
//		invalid_input("Error\nFile does not exist\n");
//    line = get_next_line(fd);
//	while (line != NULL)
//	{
//		free(line);
//		line = get_next_line(fd);
//		count++;
//	}
//	close(fd);
//	map->linecount = count;
//	save_map(map, map_name);
//}
