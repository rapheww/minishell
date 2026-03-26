/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchambos <lchambos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:21:59 by lchambos          #+#    #+#             */
/*   Updated: 2026/03/26 16:52:53 by lchambos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*stock_remain(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (free(buffer), NULL);
	line = malloc(sizeof(char) * (ft_strlen2(buffer) - i + 1));
	if (!line)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i])
		line[j++] = buffer[i++];
	line[j] = '\0';
	free(buffer);
	return (line);
}

char	*read_lines(int fd, char *buffer)
{
	char	*line;
	int		bytes_read;

	line = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!line)
		return (NULL);
	bytes_read = 1;
	line[0] = '\0';
	while (bytes_read && !(ft_strchr2(line, '\n')))
	{
		bytes_read = read(fd, line, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (free(line), NULL);
		}
		line[bytes_read] = '\0';
		buffer = ft_strjoin2(buffer, line);
	}
	free(line);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	int			i;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buffer = read_lines(fd, buffer);
	if (!buffer)
		return (NULL);
	i = 0;
	line = NULL;
	if (*buffer)
	{
		while (buffer[i] && buffer[i] != '\n')
			i++;
		line = malloc(sizeof(char) * (i + 2));
		if (!line)
			return (NULL);
		line = ft_strcpy2(line, buffer);
	}
	buffer = stock_remain(buffer);
	return (line);
}
