/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 09:46:44 by plang             #+#    #+#             */
/*   Updated: 2024/02/12 17:02:13 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_puthex_base(unsigned long c, int caps, int *ip)
{
	int			count;

	count = 0;
	if (c >= 16)
	{
		count += ft_puthex_base(c / 16, caps, ip);
		count += ft_puthex_base(c % 16, caps, ip);
	}
	if (caps == 0 && c >= 10 && c <= 15)
		count += ft_putchar(c + 87, ip);
	if (caps == 1 && c >= 10 && c <= 15)
		count += ft_putchar(c + 55, ip);
	if (c < 10)
		count += ft_putint_base(c, ip);
	return (count);
}
