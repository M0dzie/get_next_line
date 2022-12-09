/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:09:42 by thmeyer           #+#    #+#             */
/*   Updated: 2022/12/09 14:44:55 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

int	gnl_strchr(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*gnl_strjoin(char *stash, char *buffer)
{
	size_t	i;
	size_t	j;
	char	*join;

	i = 0;
	j = 0;
	join = malloc(sizeof(char) * ((ft_strlen(stash) + ft_strlen(buffer)) + 1));
	if (!join)
		return (NULL);
	while (stash[i])
		join[i++] = stash[j++];
	j = 0;
	while (buffer[j])
		join[i++] = buffer[j++];
	join[i] = '\0';
	return (join);
}

char	*gnl_free_join(char *stash, char *buffer)
{
	char	*next;

	next = gnl_strjoin(stash, buffer);
	return (free(stash), next);
}

char	*gnl_read_line(int fd, char *stash)
{
	char	*buffer;
	int		i_read;

	if (!stash)
		stash = malloc(1);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	i_read = 1;
	while (i_read != 0)
	{
		i_read = read(fd, buffer, BUFFER_SIZE);
		if (i_read < 0)
			return (free(buffer), NULL);
		buffer[i_read] = '\0';
		stash = gnl_free_join(stash, buffer);
		if (gnl_strchr(buffer, '\n') == 1)
			return (free(buffer), stash);
	}
	return (free(buffer), stash);
}

char	*gnl_line(char *stash)
{
	char	*line;
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (stash[len] && stash[len] != '\n')
		len++;
	line = malloc(sizeof(char) * (len + 1));
	while (len - i > 0)
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		line[i] = '\n';
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
		return (free(stash), NULL);
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
	return (free(stash), next_line);
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

	if (fd < 0 || BUFFER_SIZE < 0 || read(1, 0, 0) < 0)
		return (NULL);
	stash = gnl_read_line(fd, stash);
	printf("stash = %s\n", stash);
	line = gnl_line(stash);
	printf("line = %s\n", line);
	stash = gnl_next(stash);
	printf("next_line = %s\n", stash);
	return (line);
}

int	main(void)
{
	int fd = open("file_test", O_RDONLY);
	printf("\nNew function :\n");
	printf("real : %s\n", get_next_line(fd));
	printf("\nNew function :\n");
	printf("real : %s\n", get_next_line(fd));
	printf("\nNew function :\n");
	printf("real : %s\n", get_next_line(fd));
	return (0);
}