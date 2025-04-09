/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-mngu <thi-mngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 17:08:18 by thi-mngu          #+#    #+#             */
/*   Updated: 2025/04/08 17:31:29 by thi-mngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_free(char **buffer)
{
	free(*buffer);
	*buffer = NULL;
	return (NULL);
}

static char	*get_single_line(const char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = malloc((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	ft_memcpy_gnl(line, buffer, i);
	line[i] = '\0';
	return (line);
}

static char	*remaining_buffer(char *buffer)
{
	int		i;
	char	*new_buffer;

	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\n')
		i++;
	if (!buffer[i])
	{
		ft_free(&buffer);
		return (NULL);
	}
	new_buffer = ft_strdup_gnl(buffer + i);
	free(buffer);
	return (new_buffer);
}

static char	*get_buffer(char *buffer, char *temp_buffer, int readbytes, int fd)
{
	char	*temp;

	while (readbytes)
	{
		readbytes = read(fd, temp_buffer, BUFFER_SIZE);
		if (readbytes < 0)
		{
			free(temp_buffer);
			return (ft_free(&buffer));
		}
		temp_buffer[readbytes] = '\0';
		temp = buffer;
		buffer = ft_strjoin_gnl(buffer, temp_buffer);
		if (!buffer)
		{
			free(temp_buffer);
			return (ft_free(&temp));
		}
		if (ft_strchr_gnl(buffer, '\n'))
			break ;
	}
	free(temp_buffer);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*temp_buffer;
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temp_buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!temp_buffer)
		return (ft_free(&buffer));
	if (!buffer)
		buffer = ft_strdup_gnl("");
	buffer = get_buffer(buffer, temp_buffer, 1, fd);
	if (!buffer)
		return (NULL);
	line = get_single_line(buffer);
	if (!line)
		ft_free(&buffer);
	buffer = remaining_buffer(buffer);
	return (line);
}
