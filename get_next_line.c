/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:09:42 by thmeyer           #+#    #+#             */
/*   Updated: 2022/12/08 18:47:20 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define BUFFER_SIZE 10
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
	if (s[i] == '\0')
		return (1);
	return (0);
}

char	*gnl_strcpy(const char *src)
{
	size_t	i;
	char	*dst;

	i = 0;
	dst = malloc(sizeof(char) * ft_strlen(src) + 1);
	if (!dst)
		return (NULL);
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
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
	char		*buffer;
	int			we;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	we = 1;
	while (we != 0)
	{
		we = read(fd, buffer, BUFFER_SIZE);
		printf("%s", buffer);
		// if (gnl_strchr(buffer, '\n') == 1)
		// 	return (stash);
	}
	// while (gnl_strchr(buffer, '\n') == 0)
	// {
		// read(fd, buffer, BUFFER_SIZE);
		// printf("%s\n", buffer);
	// }
	return (stash);
}

int	main(void)
{
	int fd = open("file_test", O_RDONLY);
	get_next_line(fd);
	// get_next_line(fd);
	return (0);
}