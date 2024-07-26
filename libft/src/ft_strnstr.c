/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:29:51 by plang             #+#    #+#             */
/*   Updated: 2024/02/12 17:02:13 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*hay;
	size_t	i;
	size_t	j;

	hay = (char *)haystack;
	i = 0;
	j = 0;
	if (*needle == 0)
		return (hay);
	if (hay == 0 && len == 0)
		return (NULL);
	while (hay[i] != '\0' && i < len)
	{
		while (hay[i + j] == needle[j] && j < len - i)
		{
			j++;
			if (needle[j] == '\0')
				return (&hay[i]);
		}
		j = 0;
		i++;
	}
	return (NULL);
}
