/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:16:55 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/28 13:07:56 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	i = 0;

	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *stash, char *buffer)
{
	char *join;
	int i = 0, j = 0, size = 0;

	if (!stash && !buffer)
		return (NULL);
	size = ft_strlen(stash) + ft_strlen(buffer);
	join = malloc(sizeof(char) * (size + 1));
	if (!join)
		return (free(stash), NULL);
	if (stash)
	{
		while (stash[i])
			join[j++] = stash[i++];
		i = 0;
	}
	while (buffer[i])
		join[j++] = buffer[i++];
	join[size] = '\0';
	return (free(stash), join);
}

char	*get_line(char *stash)
{
	int i = 0;
	char *line;

	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		line[i] = '\n';
		line[i + 1] = '\0';
		return (line);
	}
	line[i] = '\0';
	return (line);
}

char	*get_next(char *stash)
{
	int i = 0, j = 0;
	char *next;

	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
		return (free(stash), NULL);
	next = malloc(sizeof(char) * (ft_strlen(stash) -i + 1));
	if (!next)
		return (NULL);
	i++;
	while (stash[i])
		next[j++] = stash[i++];
	next[j] = '\0';
	return (free(stash), next);
}

int	find_endl(char *line)
{
	int i = 0;

	while (line[i])
	{
		if (line[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	char buffer[BUFFER_SIZE + 1];
	buffer[0] = '\0';
	static char *stash;
	char *line;
	int rd = 1;

	if (fd < 0 || read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)
		return (free(stash), NULL);
	while (rd != 0)
	{
		if ((rd = read(fd, buffer, BUFFER_SIZE)) == -1)
			return (NULL);
		buffer[rd] = '\0';
		stash = ft_strjoin(stash, buffer);
		if (find_endl(buffer))
			break ;
	}
	line = get_line(stash);
	stash = get_next(stash);
	if (line[0] == '\0')
		return (free(line), NULL);
	return (line);
}

#include <stdio.h>
#include <fcntl.h>

int main(void)
{
	int fd = open("test", O_RDONLY);

	for (int i = 0; i < 10; i++)
		printf("%s", get_next_line(fd));
	return (0);
}
