/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 10:31:37 by plang             #+#    #+#             */
/*   Updated: 2024/02/12 17:02:13 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_free_gnl(char *read_lines, char *static_buff, int read_bytes)
{
	if (read_bytes == -1)
		ft_strcpy(static_buff, "");
	free(read_lines);
	return (NULL);
}

char	*ft_strdup_gnl(const char *s1)
{
	char	*ptr;
	int		n;
	int		i;

	i = 0;
	n = ft_strlen(s1);
	ptr = (char *)malloc(n + 1 * sizeof(char));
	if (ptr == 0)
		return (NULL);
	while (i < n)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
