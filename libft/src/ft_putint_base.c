/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putint_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 09:23:42 by plang             #+#    #+#             */
/*   Updated: 2024/02/12 17:02:13 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putint_base(int c, int *ip)

{
	int	count;

	count = 0;
	if (c == -2147483648)
	{
		count += ft_putstr("-2147483648", ip);
	}
	else if (c < 0)
	{
		count += ft_putchar('-', ip);
		count += ft_putint_base(c * -1, ip);
	}
	else if (c > 9)
	{
		count += ft_putint_base(c / 10, ip);
		count += ft_putint_base(c % 10, ip);
	}
	else
		count += ft_putchar(c + 48, ip);
	return (count);
}
