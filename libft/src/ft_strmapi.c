/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 10:41:13 by plang             #+#    #+#             */
/*   Updated: 2024/08/05 14:39:37 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		len;
	char	*newstr;
	int		i;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	i = 0;
	newstr = malloc(len + 1);
	if (newstr == 0)
		return (NULL);
	while (i < len)
	{
		newstr[i] = (*f)(i, s[i]);
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}
