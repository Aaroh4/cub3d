/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:58:30 by plang             #+#    #+#             */
/*   Updated: 2023/11/15 16:58:09 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static	int	ft_conversion(const char *str, int negative, long result, long prev)
{
	while (*str >= 48 && *str <= 57)
	{
		prev = result;
		result = result * 10 + *str - '0';
		str++;
		if (result < prev || (result % 100) / 10 != prev % 10)
		{
			if (negative == 1)
				return (-1);
			return (0);
		}
	}
	return (result * negative);
}

int	ft_atoi(const char *str)
{
	int		negative;
	long	result;
	long	prev;

	negative = 1;
	result = 0;
	prev = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == 45)
	{
		negative = -1;
		str++;
	}
	else if (*str == 43)
		str++;
	return (ft_conversion(str, negative, result, prev));
}
