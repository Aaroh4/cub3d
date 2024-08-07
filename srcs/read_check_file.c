/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_check_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:03:07 by plang             #+#    #+#             */
/*   Updated: 2024/08/07 18:07:00 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdio.h>

void	clean_from_space_nl(char **str)
{
	char	*copy;
	char	*start;
	int		i;
	int		space;

	i = 0;
	space = 0;
	while ((*str)[space] == ' ' && (*str)[space])
		space++;
	copy = ft_strdup(*str);
	if (!copy)
		return ;
	start = copy;
	while (*copy)
	{
		if (*copy != ' ' && *copy != '\n')
			(*str)[i++] = *copy;
		copy++;
	}
	(*str)[i] = '\0';
	free(start);
}

void	clean_from_nl(char **str)
{
	char	*copy;
	char	*start;
	int		i;

	i = 0;
	copy = ft_strdup(*str);
	if (!copy)
		return ;
	start = copy;
	while (*copy)
	{
		if (*copy != '\n')
			(*str)[i++] = *copy;
		copy++;
	}
	(*str)[i] = '\0';
	free(start);
}

void	clean_cardinal_directions(char **str)
{
	char	*copy;
	char	*start;
	int		i;

	i = 0;
	copy = ft_strdup(*str);
	if (!copy)
		return ;
	start = copy;
	while (*copy >= 65 && *copy <= 90)
		copy++;
	while (*copy)
	{
		(*str)[i++] = *copy;
		copy++;
	}
	(*str)[i] = '\0';
	free(start);
}

void	argument_check(char *argv)
{
	int		len;
	char	*ber;
	char	*file;

	len = ft_strlen(argv);
	ber = ".cub";
	file = ft_strnstr(argv, ber, len);
	if ((file == NULL) || (argv[0] == '.') || ft_strncmp(file, ber, len))
	{
		ft_putstr_fd("Error\nWe need a .cub file\n", 2);
		exit(1);
	}
}

void	invalid_input(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}

void	error_inside_file(t_fcheck *check)
{
	int	i;

	i = 0;
	while (i < check->linecount)
	{
		free(check->file[i]);
		i++;
	}
	free(check->file);
	free(check->north);
	free(check->south);
	free(check->west);
	free(check->east);
	free(check->ground);
	free(check->sky);
	exit (1);
}

char	*check_and_set_info(char *str, char *info, t_fcheck *check)
{
	while (*str == ' ')
		str++;
	if (!info)
		info = ft_strdup(str);
	else
	{
		ft_putstr_fd("Error\nDuplicate info input\n", 2);
		check->error = 1;
	}
	return (info);
}

int	extract_and_set_info2(char *str, int info_set, t_fcheck *check)
{
	if (str && (ft_strnstr(str, "F", (size_t)ft_strlen(str)) != 0))
	{
		info_set++;
		check->ground = check_and_set_info(str, check->ground, check);
	}
	if (str && (ft_strnstr(str, "C", (size_t)ft_strlen(str)) != 0))
	{
		info_set++;
		check->sky = check_and_set_info(str, check->sky, check);
	}
	return (info_set);
}

int	extract_and_set_info1(char *str, int info_set, t_fcheck *check)
{
	if (str && ((ft_strnstr(str, "NO", (size_t)ft_strlen(str)) != 0)))
	{
		info_set++;
		check->north = check_and_set_info(str, check->north, check);
	}
	if (str && ((ft_strnstr(str, "SO", (size_t)ft_strlen(str)) != 0)))
	{
		info_set++;
		check->south = check_and_set_info(str, check->south, check);
	}
	if (str && ((ft_strnstr(str, "WE", (size_t)ft_strlen(str)) != 0)))
	{
		info_set++;
		check->west = check_and_set_info(str, check->west, check);
	}
	if (str && ((ft_strnstr(str, "EA", (size_t)ft_strlen(str)) != 0)))
	{
		info_set++;
		check->east = check_and_set_info(str, check->east, check);
	}
	info_set = extract_and_set_info2(str, info_set, check);
	return (info_set);
}

void	check_info_flag(t_fcheck *check, int i)
{
	if (check->info == 6)
	{
		check->map_start = i + 1;
		check->info = check->info + 1;
	}
}

void	check_failed_info_flag(t_fcheck *check)
{
	if (check->info < 7)
	{
		ft_putstr_fd("Error\nSome information is missing\n", 2);
		check->error = 1;
	}
}

int	check_rest(t_fcheck *check, int	i)
{
	int	index;

	index = i;
	while (check->file[index])
	{
		if (check->file[index][0] != '\n')
			return (1);
		index++;
	}
	check->linecount--;
	while (check->file[check->linecount][0] == '\n')
		check->linecount--;
	check->linecount++;
	return (0);
}

void	get_map_information(t_fcheck *check)
{
	int		i;
	int		map_start;

	i = -1;
	map_start = 0;
	while (++i <= check->linecount)
	{
		check->info = extract_and_set_info1(check->file[i], check->info, check);
		if (check->info > 6)
		{
			if (check->file[i] && (check->file[i][0] == '\n' && map_start == 0))
				continue ;
			if (check->file[i] && check->file[i][0] != '\n')
				map_start = 1;
			if (check->file[i] && (check->file[i][0] == '\n' && map_start == 1 \
				&& check_rest(check, i)))
			{
				ft_putstr_fd("Error\nMap not complete\n", 2);
				check->error = 1;
				break ;
			}
		}
		check_info_flag(check, i);
	}
	check_failed_info_flag(check);
}

// the white spaces are fucking this up, trim it!

void	check_int_of_rgb(t_fcheck *check, char **ceiling)
{
	int	i;
	int	j;

	i = 0;
	while (ceiling[i] != NULL)
	{
		j = 0;
		clean_from_space_nl(&ceiling[i]);
		while (ceiling[i][j] != '\0')
		{
			if (ft_isdigit((int)ceiling[i][j]) == 0)
				check->error = 1;
			j++;
		}
		if (ft_atoi(ceiling[i]) < 0 || ft_atoi(ceiling[i]) > 255)
			check->error = 1;
		// i++;
		if (i++ > 2)
			check->error = 1;
	}
	if (check->error == 1)
		ft_putstr_fd("Error\nRGB not valid\n", 2);
}

void	check_rgb_floor(t_fcheck *check)
{
	char	**floor;
	char	*temp;
	// int		one;
	// int		two;
	// int		three;

	floor = NULL;
	temp = check->ground;
	while (*temp != ' ')
		temp++;
	floor = ft_split(temp, ',');
	if (!floor)
		return ;//malloc failed
	check_int_of_rgb(check, floor);
	// one = ft_atoi(floor[0]);
	// two = ft_atoi(floor[1]);
	// three = ft_atoi(floor[2]);
	// printf("one: %d\ntwo: %d\nthree: %d\n", one, two, three);
}

void	check_rgb_ceiling(t_fcheck *check)
{
	char	**ceiling;
	char	*temp;
	// int		one;
	// int		two;
	// int		three;

	ceiling = NULL;
	temp = check->sky;
	while (*temp != ' ')
		temp++;
	ceiling = ft_split(temp, ',');
	if (!ceiling)
		return ; //malloc failed
	check_int_of_rgb(check, ceiling);
	// one = ft_atoi(ceiling[0]);
	// two = ft_atoi(ceiling[1]);
	// three = ft_atoi(ceiling[2]);
	// printf("one: %d\ntwo: %d\nthree: %d\n", one, two, three);
}

void	print_check_struct(t_fcheck *check)
{
	printf("linecount: %d\n", check->linecount);
	printf("count: %d\n", check->count);
	printf("map_start: %d\n", check->map_start);
	printf("info: %d\n", check->info);
	printf("error: %d\n", check->error);
	printf("north str: %s\n", check->north);
	printf("south str: %s\n", check->south);
	printf("west str: %s\n", check->west);
	printf("east str: %s\n", check->east);
	printf("ground str: %s\n", check->ground);
	printf("sky str: %s\n", check->sky);
	int	k = 0;
	while (check->mapcpy[k])
	{
		printf("%s\n", check->mapcpy[k]);
		k++;
	}
}

void	clean_input_strings(t_fcheck *check)
{
	clean_from_space_nl(&check->north);
	clean_from_space_nl(&check->south);
	clean_from_space_nl(&check->west);
	clean_from_space_nl(&check->east);
	clean_from_space_nl(&check->ground);
	clean_from_space_nl(&check->sky);
	clean_cardinal_directions(&check->north);
	clean_cardinal_directions(&check->south);
	clean_cardinal_directions(&check->west);
	clean_cardinal_directions(&check->east);
	clean_cardinal_directions(&check->ground);
	clean_cardinal_directions(&check->sky);
}

// int check_num(char c)
// {
// 	char *str;
// 	str = "012";

// 	while (*str)
// 	{
// 		if (c == *str)
// 			return (1);
// 		str++;
// 	}
// 	return (0);
// }

// int	wall_flood_fill(t_fcheck *check, int posy, int posx)
// {
// 	int i;

// 	i = 0;
// 	check->mapcpy[posy][posx] = '2';
// 	if (check->mapcpy[posy - 1] == NULL
// 		|| check_num(check->mapcpy[posy - 1][posx]) == 0 
// 		|| check_num(check->mapcpy[posy + 1][posx]) == 0
// 		|| check_num(check->mapcpy[posy][posx + 1]) == 0
// 		|| check_num(check->mapcpy[posy][posx - 1]) == 0)
// 		return (1);
// 	if (check->mapcpy[posy + 1][posx] == '0' && i == 0)
// 		i = wall_flood_fill(check, posy + 1, posx);
// 	if (check->mapcpy[posy][posx + 1] == '0' && i == 0)
// 		i = wall_flood_fill(check, posy, posx + 1);
// 	if (check->mapcpy[posy - 1][posx] == '0' && i == 0)
// 		i = wall_flood_fill(check, posy - 1, posx);
// 	if (check->mapcpy[posy][posx - 1] == '0' && i == 0)
// 		i = wall_flood_fill(check, posy, posx - 1);
// 	return (i);
// }

void	looptrough(t_fcheck *check, char *str, int count)
{
	static int	player = 0;
	static int	lines = 0;
	int			i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 'N' || str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
		{
			player++;
			check->playerstartpos = str[i];
			check->plocation[0] = i;
			check->plocation[1] = count;
			check->cameraposx = 20 * i;
			check->cameraposy = 20 * (count - 8);
		}
		i++;
	}
	lines++;
	if (player != 1 && ((check->linecount - check->map_start) == (lines + 1)))
	{
		printf("Error\nWrong amount of player\n%d", player);
		exit (1);
	}
}

void	direction_check(t_fcheck *check, int *invalid, int *i, int *j)
{
	if (check->mapcpy[*i][*j + 1] == ' ' || \
		check->mapcpy[*i][*j + 1] == '\0')
		*invalid = 1;
	if (check->mapcpy[*i][0] == '0' \
		|| check->mapcpy[*i][0] == check->playerstartpos)
		*invalid = 1;
	if (check->mapcpy[*i][*j - 1] && check->mapcpy[*i][*j - 1] == ' ')
		*invalid = 1;
	if (check->mapcpy[*i + 1] && check->mapcpy[*i + 1][*j] == ' ')
		*invalid = 1;
	if (*i == 0 && (check->mapcpy[0][*j] == '0' \
		|| check->mapcpy[0][*j] == ' ' \
		|| check->mapcpy[0][*j] == check->playerstartpos))
		*invalid = 1;
	if (*i == check->map_size && (check->mapcpy[check->map_size][*j] == '0' \
		|| check->mapcpy[check->map_size][*j] == ' ' \
		|| check->mapcpy[check->map_size][*j] == check->playerstartpos))
		*invalid = 1;
}

int check_char(char c)
{
	char *str;
	str = "01NSWE ";

	while (*str)
	{
		if (c == *str)
			return (1);
		str++;
	}
	return (0);
}

void	map_boarder_check(t_fcheck *check)
{
	int	i;
	int	j;
	int	invalid;

	i = 0;
	invalid = 0;
	while (check->mapcpy[i] != 0)
	{
		j = 0;
		while (check->mapcpy[i][j] != '\0')
		{
			if (check->mapcpy[i][j] == '0')
				direction_check(check, &invalid, &i, &j);
			if (check->mapcpy[i][j] == check->playerstartpos)
				direction_check(check, &invalid, &i, &j);
			if (check_char(check->mapcpy[i][j]) == 0)
				invalid = 1;
			j++;
		}
		i++;
	}
	if (invalid == 1)
		ft_putstr_fd("Error\nBuilding blocks are invalid\n", 2);
}

void	check_player_and_boarder(t_fcheck *check)
{
	int	i;
	int	j;

	i = 0;
	j = check->map_start;
	while (check->file[j][0] == '\n')
	{
		check->map_start++;
		j++;
	}
	check->map_size = (check->linecount - check->map_start - 1);
	check->mapcpy = malloc((check->map_size + 1) * sizeof(char *));
	// if (!check->mapcpy)
		// error;
	printf("%d\n", check->map_size);
	while (j < check->linecount)
	{
		check->mapcpy[i] = ft_strdup(check->file[j]);
		clean_from_nl(&check->mapcpy[i]);
		looptrough(check, check->mapcpy[i], i);
		j++;
		i++;
	}
	check->mapcpy[i] = 0;
	map_boarder_check(check);
	// if (wall_flood_fill(check, check->plocation[1], check->plocation[0]) == 1)
	// {
	// 	printf("Walls not closed!\n");
	// 	exit(1);
	// }
}

void	read_file(char *map_name, int count)
{
	int			fd;
	int			i;
	t_fcheck	check;

	ft_memset(&check, 0, sizeof(check));
	i = 0;
	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		invalid_input("Error\nFile does not exist\n");
	check.file = malloc((count + 1) * sizeof(char *));
	if (!check.file)
		return ;//malloc fail
	while (check.count < count)
	{
		check.file[i] = get_next_line(fd);
		check.count++;
		i++;
	}
	check.file[i] = 0;
	close(fd);
	check.linecount = check.count;
	get_map_information(&check);
	if (check.error == 1)
		error_inside_file(&check);
	check_rgb_floor(&check);
	check_rgb_ceiling(&check);
	if (check.error == 1)
		error_inside_file(&check);
	check_player_and_boarder(&check);
	// printf("\n");
	// int	k = 0;
	// while (check.file[k])
	// {
	// 	printf("%s", check.file[k]);
	// 	k++;
	// }
	// printf("\n");
	// printf("check count: %d\nlinecount: %d\nmap start: %d\ninfo: %d\nnorth: %s\nsouth: %s\nwest: %s\neast: %s\nground: %s\nsky:%s\n", check.count, check.linecount, check.map_start, check.info, check.north, check.south, check.west, check.east, check.ground, check.sky);
	printf("\n");
	clean_input_strings(&check);
	print_check_struct(&check);
}

int	count_file_lines(char *map_name, int count)
{
	char	*line;
	int		fd;

	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		invalid_input("Error\nFile does not exist\n");
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		count++;
	}
	close(fd);
	return (count);
}

int	main(int argc, char **argv)
{
	char	*map_name;
	int		count;

	if (argc != 2)
		exit(1);
	argument_check(argv[1]);
	count = 0;
	map_name = argv[1];
	count = count_file_lines(map_name, count);
	read_file(map_name, count);
	return (0);
}
