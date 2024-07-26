/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_check_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:03:07 by plang             #+#    #+#             */
/*   Updated: 2024/07/26 11:51:58 by plang            ###   ########.fr       */
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
		check->map_start = i;
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
			if (check->file[i] && (check->file[i][0] == '\n' && map_start == 1))
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
	// printf("\n");
	// int	k = 0;
	// while (check.file[k])
	// {
	// 	printf("%s", check.file[k]);
	// 	k++;
	// }
	printf("\n");
	printf("check count: %d\nlinecount: %d\nmap start: %d\ninfo: %d\nnorth: %s\nsouth: %s\nwest: %s\neast: %s\nground: %s\nsky:%s\n", check.count, check.linecount, check.map_start, check.info, check.north, check.south, check.west, check.east, check.ground, check.sky);
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
