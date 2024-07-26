/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 10:31:15 by plang             #+#    #+#             */
/*   Updated: 2024/02/12 17:02:13 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_join(char *read_lines, char *static_buff)
{
	char	*temp;

	temp = ft_strjoin(read_lines, static_buff);
	if (!temp)
	{
		free(read_lines);
		return (NULL);
	}
	free(read_lines);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	static_buff[BUFFER_SIZE + 1];
	char		*read_lines;
	int			read_bytes;
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_lines = ft_strdup_gnl(static_buff);
	read_bytes = BUFFER_SIZE;
	while (read_bytes == BUFFER_SIZE && ((ft_strchr(static_buff, '\n')) == 0))
	{
		read_bytes = read(fd, static_buff, BUFFER_SIZE);
		if (read_bytes == -1)
			return (ft_free_gnl(read_lines, static_buff, read_bytes));
		static_buff[read_bytes] = '\0';
		read_lines = ft_join(read_lines, static_buff);
	}
	if (read_lines == 0 || read_lines[0] == '\0')
		return (ft_free_gnl(read_lines, static_buff, read_bytes));
	line = ft_get_line(read_lines);
	temp = ft_get_remainder(read_lines);
	ft_strcpy(static_buff, temp);
	free(temp);
	return (line);
}

void	ft_strcpy(char *static_buff, char *temp)
{
	int	i;

	i = 0;
	while (temp[i] != '\0')
	{
		static_buff[i] = temp[i];
		i++;
	}
	static_buff[i] = '\0';
}

char	*ft_get_line(char *read_lines)
{
	char	*line;
	int		i;
	int		nl;

	nl = 0;
	i = 0;
	while (read_lines[nl] != '\n' && read_lines[nl] != '\0')
		nl++;
	if (ft_strchr(read_lines, '\n') != 0)
		nl++;
	line = malloc(nl + 1 * sizeof(char));
	if (!line)
		return (NULL);
	while (i < nl)
	{
		line[i] = read_lines[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_get_remainder(char *read_lines)
{
	char	*remainder;
	int		i;
	int		j;

	i = 0;
	remainder = read_lines;
	while (read_lines[i] != '\n' && read_lines[i] != '\0')
		i++;
	if (read_lines[i] != '\0')
		i++;
	j = 0;
	while (read_lines[i] != '\0')
	{
		remainder[j] = read_lines[i];
		j++;
		i++;
	}
	remainder[j] = '\0';
	return (remainder);
}
