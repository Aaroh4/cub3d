/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:14:20 by plang             #+#    #+#             */
/*   Updated: 2024/07/25 16:04:44 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*get_next_line_fd(int fd)
{
	static char	s_buffer[2000][BUFFER_SIZE + 1];
	char		*read_lines;
	int			read_bytes;
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_lines = ft_strdup_gnl(s_buffer[fd]);
	read_bytes = BUFFER_SIZE;
	while (read_bytes == BUFFER_SIZE && ((ft_strchr(s_buffer[fd], '\n')) == 0))
	{
		read_bytes = read(fd, s_buffer[fd], BUFFER_SIZE);
		if (read_bytes == -1)
			return (ft_free_gnl(read_lines, s_buffer[fd], read_bytes));
		s_buffer[fd][read_bytes] = '\0';
		read_lines = ft_join(read_lines, s_buffer[fd]);
	}
	if (read_lines == 0 || read_lines[0] == 0)
		return (ft_free_gnl(read_lines, s_buffer[fd], read_bytes));
	line = ft_get_line(read_lines);
	temp = ft_get_remainder(read_lines);
	ft_strcpy(s_buffer[fd], temp);
	free(temp);
	return (line);
}
