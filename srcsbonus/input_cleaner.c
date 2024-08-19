/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_cleaner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 09:26:11 by plang             #+#    #+#             */
/*   Updated: 2024/08/19 14:01:51 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3dbonus.h"

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
