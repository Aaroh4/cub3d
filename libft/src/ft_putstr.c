/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 08:46:51 by plang             #+#    #+#             */
/*   Updated: 2024/02/12 17:02:13 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putstr(char *str, int *ip)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str)
		return (ft_putstr("(null)", ip));
	while (str[i] != '\0')
	{
		count += ft_putchar(str[i], ip);
		i++;
	}
	return (count);
}
