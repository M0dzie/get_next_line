/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin42@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:09:42 by thmeyer           #+#    #+#             */
/*   Updated: 2022/12/13 14:05:03 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_free_join(char *stash, char *buffer)
{
	char	*next;

	next = gnl_strjoin(stash, buffer);
	return (free(stash), stash = NULL, next);
}

char	*gnl_read_line(int fd, char *stash)
{
	char	buffer[BUFFER_SIZE + 1];
	int		i_read;

	if (!stash)
	{
		stash = malloc(1);
		stash[0] = '\0';
	}
	i_read = 1;
	while (i_read != 0)
	{
		i_read = read(fd, buffer, BUFFER_SIZE);
		if (i_read < 0)
			return (NULL);
		buffer[i_read] = '\0';
		stash = gnl_free_join(stash, buffer);
		if (gnl_strchr(buffer, '\n') == 1)
			break ;
	}
	return (stash);
}

char	*gnl_line(char *stash)
{
	char	*line;
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	if (!stash[i])
		return (NULL);
	while (stash[len] && stash[len] != '\n')
		len++;
	if (stash[len] == '\n')
		len++;
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	while (len - i > 0)
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*gnl_next(char *stash)
{
	char	*next_line;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\0')
		return (free(stash), stash = NULL, NULL);
	next_line = malloc(sizeof(char) * ((ft_strlen(stash) - i) + 1));
	if (!next_line)
		return (NULL);
	i++;
	while (stash[i + j])
	{
		next_line[j] = stash[i + j];
		j++;
	}
	next_line[j] = '\0';
	return (free(stash), stash = NULL, next_line);
}

/**
 * @brief write a function that returns a line read from a file descriptor
 * @param fd the file descriptor to read from
 * @return Read line must have a correct behavior or NULL if there is nothing 
 * else to read, or an error occurred
 */
char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
		return (free(stash), stash = NULL, NULL);
	stash = gnl_read_line(fd, stash);
	line = gnl_line(stash);
	stash = gnl_next(stash);
	return (line);
}
