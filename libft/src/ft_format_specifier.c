/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_specifier.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:01:03 by plang             #+#    #+#             */
/*   Updated: 2024/02/12 17:02:13 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_format_specifier(char specifier, va_list args, int *ip)
{
	int	count;

	count = 0;
	if (specifier == 'c')
		count += ft_putchar(va_arg(args, int), ip);
	else if (specifier == 's')
		count += ft_putstr(va_arg(args, char *), ip);
	else if (specifier == 'p')
		count += ft_putpointer(va_arg(args, unsigned long), ip);
	else if (specifier == 'd' || specifier == 'i')
		count += ft_putint_base(va_arg(args, int), ip);
	else if (specifier == 'u')
		count += ft_putunsig(va_arg(args, unsigned int), ip);
	else if (specifier == 'x')
		count += ft_puthex_base(va_arg(args, unsigned int), 0, ip);
	else if (specifier == 'X')
		count += ft_puthex_base(va_arg(args, unsigned int), 1, ip);
	else if (specifier == '%')
		count += ft_putchar('%', ip);
	else
		count += ft_putchar(specifier, ip);
	return (count);
}
