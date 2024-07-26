/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:07:33 by plang             #+#    #+#             */
/*   Updated: 2024/02/12 17:03:47 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static	int	int_count(int n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	if (n == 0)
		i++;
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		len;
	int		i;

	result = 0;
	len = int_count(n);
	i = len;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	result = malloc(len * sizeof(char) + 1);
	if (result == 0)
		return (NULL);
	if (n < 0)
		n *= -1;
	while (0 < len)
	{
		result[len-- - 1] = n % 10 + '0';
		n /= 10;
	}
	if (result[0] == '0')
		result[0] = '-';
	result[i] = '\0';
	return (result);
}
