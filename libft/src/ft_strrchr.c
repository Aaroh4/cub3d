/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 11:32:34 by plang             #+#    #+#             */
/*   Updated: 2024/02/12 17:02:13 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *s, int c)

{
	char	chr;
	int		i;
	char	*temp;

	temp = 0;
	chr = (char) c;
	i = 0;
	if (chr == '\0')
		return ((char *)s + ft_strlen(s));
	while (s[i] != '\0')
	{
		if (s[i] == chr)
		{
			temp = (char *)&s[i];
		}
		i++;
	}
	return ((char *)temp);
}
