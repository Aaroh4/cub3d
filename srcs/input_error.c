/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 09:26:29 by plang             #+#    #+#             */
/*   Updated: 2024/08/15 14:13:46 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_strfree(char *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
	else
		return ;
}

void	ft_arrfree(char **arr)
{
	if (arr)
	{
		free(arr);
		arr = NULL;
	}
	else
		return ;
}

void	invalid_input(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}

void	error_inside_file(t_fcheck *check, char *str)
{
	int	i;

	i = 0;
	ft_putstr_fd(str, 2);
	while (i < check->linecount)
	{
		ft_strfree(check->file[i]);
		i++;
	}
	ft_arrfree(check->file);
	i = 0;
	while (i < check->map_size)
	{
		ft_strfree(check->mapcpy[i]);
		i++;
	}
	ft_arrfree(check->mapcpy);
	ft_strfree(check->north);
	ft_strfree(check->south);
	ft_strfree(check->west);
	ft_strfree(check->east);
	ft_strfree(check->ground);
	ft_strfree(check->sky);
	exit (1);
}
