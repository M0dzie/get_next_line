/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_one_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:24:20 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/13 10:25:53 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 5
#endif

int	ft_strlen(char *str)
{
	int	i = 0;

	while (str[i])
		i++;
	return (i);
}

char	*get_next_line(int fd)
{
	char	line[1000000];
	char	buffer;
	int	i = 0;
	int	rd;

	rd = read(fd, &buffer, 1);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0 || rd == 0)
		return (NULL);
	while (rd)
	{
		line[i++] = buffer;
		if (buffer == '\n')
			break ;
		else
			rd = read(fd, &buffer, 1);
	}
	line[i++] = '\0';
	char	*s;
	int	len = ft_strlen(line);
	s = malloc(sizeof(char) * len + 1);
	while (len--)
		s[len] = line[len];
	return (s);
}
