/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 09:26:29 by plang             #+#    #+#             */
/*   Updated: 2024/08/13 16:00:31 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
	i = 0;
	while (i < check->map_size)
	{
		free(check->mapcpy[i]);
		i++;
	}
	free(check->mapcpy);
	free(check->north);
	free(check->south);
	free(check->west);
	free(check->east);
	free(check->ground);
	free(check->sky);
	exit (1);
}
