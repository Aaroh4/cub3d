/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 09:25:58 by plang             #+#    #+#             */
/*   Updated: 2024/08/15 14:37:14 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	count_file_lines(char *map_name, int count)
{
	char	*line;
	int		fd;

	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		invalid_input(INVFILE);
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

void	read_file(char *map_name, int count, t_map *map)
{
	int			fd;
	int			i;
	t_fcheck	check;

	ft_memset(&check, 0, sizeof(check));
	i = 0;
	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		invalid_input(INVFILE);
	check.file = malloc((count + 1) * sizeof(char *));
	if (!check.file)
		invalid_input(MALLOCFAIL);
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
		error_inside_file(&check, INVTXTMAP);
	check_rgb_floor(&check);
	if (check.error == 1)
		error_inside_file(&check, INVRGB);
	check_rgb_ceiling(&check);
	if (check.error == 1)
		error_inside_file(&check, INVRGB);
	check_player_and_boarder(&check);
	clean_input_strings(&check);
	map->mapsave = check.mapcpy;
	map->cameraposx = check.cameraposx;
	map->cameraposy = check.cameraposy;
	map->playerstartpos = check.playerstartpos;
	map->floor = check.bottom;
	map->ceiling = check.top;

}
//print_check_struct(&check);
//error_inside_file(&check);

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
				check->error = 1;
				break ;
			}
		}
		check_info_flag(check, i);
	}
	check_failed_info_flag(check);
}

int	check_rest(t_fcheck *check, int i)
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

void	argument_check(char *argv)
{
	int		len;
	char	*ber;
	char	*file;

	len = ft_strlen(argv);
	ber = ".cub";
	file = ft_strnstr(argv, ber, len);
	if ((file == NULL) || (argv[0] == '.') || ft_strncmp(file, ber, len))
		invalid_input(INVCUB);
}
