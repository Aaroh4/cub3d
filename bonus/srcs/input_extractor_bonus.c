/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_extractor_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 09:26:39 by plang             #+#    #+#             */
/*   Updated: 2024/08/20 14:03:45 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

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

int	extract_and_set_info2(char *str, int info_set, t_fcheck *check)
{
	if (str && (ft_strnstr(str, "F", (size_t)ft_strlen("F")) != 0))
	{
		info_set++;
		check->ground = check_and_set_info(str, check->ground, check);
	}
	if (str && (ft_strnstr(str, "C", (size_t)ft_strlen("C")) != 0))
	{
		info_set++;
		check->sky = check_and_set_info(str, check->sky, check);
	}
	return (info_set);
}

char	*check_and_set_info(char *str, char *info, t_fcheck *check)
{
	while (*str == ' ')
		str++;
	if (!info)
		info = ft_strdup(str);
	else
		check->error = 1;
	return (info);
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
		check->error = 1;
}
