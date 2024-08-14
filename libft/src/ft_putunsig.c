/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsig.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:31:49 by plang             #+#    #+#             */
/*   Updated: 2024/08/05 14:39:37 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putunsig(unsigned int c, int *ip)
{
	int	count;

	count = 0;
	if (c > 9)
	{
		count += ft_putunsig(c / 10, ip);
		count += ft_putunsig(c % 10, ip);
	}
	else
		count += ft_putchar(c + 48, ip);
	return (count);
}
