/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 09:26:52 by plang             #+#    #+#             */
/*   Updated: 2024/08/14 16:16:27 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	rgb_free(char **strings)
{
	int	i;

	i = 0;
	while (strings[i])
	{
		free(strings[i]);
		i++;
	}
	free(strings);
}

void	check_int_of_rgb(t_fcheck *check, char **surface)
{
	int	i;
	int	j;

	i = 0;
	while (surface[i] != NULL)
	{
		j = 0;
		clean_from_space_nl(&surface[i]);
		while (surface[i][j] != '\0')
		{
			if (ft_isdigit((int)surface[i][j]) == 0)
				check->error = 1;
			j++;
		}
		if (ft_atoi(surface[i]) < 0 || ft_atoi(surface[i]) > 255)
			check->error = 1;
		if (i++ > 2)
			check->error = 1;
		if (check->error == 1)
			break ;
	}
}

//malloc failed error needed;
void	check_rgb_floor(t_fcheck *check)
{
	char	**floor;
	char	*temp;

	floor = NULL;
	temp = check->ground;
	while (*temp != ' ')
		temp++;
	floor = ft_split(temp, ',');
	if (!floor)
		return ;
	check_int_of_rgb(check, floor);
	rgb_free(floor);
}

//malloc failed error needed;
void	check_rgb_ceiling(t_fcheck *check)
{
	char	**ceiling;
	char	*temp;

	ceiling = NULL;
	temp = check->sky;
	while (*temp != ' ')
		temp++;
	ceiling = ft_split(temp, ',');
	if (!ceiling)
		return ;
	check_int_of_rgb(check, ceiling);
	rgb_free(ceiling);
}
