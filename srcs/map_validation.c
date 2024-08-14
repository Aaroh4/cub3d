/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 09:26:46 by plang             #+#    #+#             */
/*   Updated: 2024/08/14 13:24:54 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
			if (player == 1)
			{
				check->playerstartpos = str[i];
				check->plocation[0] = i;
				check->plocation[1] = count;
				check->cameraposx = 20 * i;
				check->cameraposy = 20 * (count - 8);
			}
		}
		i++;
	}
	lines++;
	if (player != 1 && ((check->map_size) == (lines)))
	{
		ft_putstr_fd("Error\nWrong count of players\n", 2);
		error_inside_file(check);
	}
}

void	direction_check(t_fcheck *check, int *invalid, int *i, int *j)
{
	if (*i == 0 && (check->mapcpy[0][*j] == '0' || check->mapcpy[0][*j] == ' ' \
		|| check->mapcpy[0][*j] == check->playerstartpos))
		*invalid = 1;
	else if (check->mapcpy[*i][*j + 1] == ' ' || \
		check->mapcpy[*i][*j + 1] == '\0')
		*invalid = 1;
	else if (check->mapcpy[*i][0] == '0' \
		|| check->mapcpy[*i][0] == check->playerstartpos)
		*invalid = 1;
	else if (check->mapcpy[*i][*j - 1] && check->mapcpy[*i][*j - 1] == ' ')
		*invalid = 1;
	else if (((check->mapcpy[*i + 1] && ((int)ft_strlen(check->mapcpy[*i + 1]) \
		< *j)) || (check->mapcpy[*i + 1] && check->mapcpy[*i + 1][*j] == '\0') \
		|| (check->mapcpy[*i + 1][*j] && check->mapcpy[*i + 1][*j] == ' ')))
		*invalid = 1;
	else if (((check->mapcpy[*i - 1] && ((int)ft_strlen(check->mapcpy[*i - 1]) \
		< *j)) || (check->mapcpy[*i - 1] && check->mapcpy[*i - 1][*j] == '\0') \
		|| (check->mapcpy[*i - 1][*j] && check->mapcpy[*i - 1][*j] == ' ')))
		*invalid = 1;
	else if (*i == check->map_size && (check->mapcpy[check->map_size][*j] \
		== '0' || check->mapcpy[check->map_size][*j] == ' ' \
		|| check->mapcpy[check->map_size][*j] == check->playerstartpos))
		*invalid = 1;
}

int	check_char(char c)
{
	char	*str;

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

// malloc fail error needed;
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
	check->map_size = (check->linecount - check->map_start);
	check->mapcpy = malloc((check->map_size + 1) * sizeof(char *));
	if (!check->mapcpy)
		return ;
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
}
