/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:07:45 by thmeyer           #+#    #+#             */
/*   Updated: 2022/12/12 15:59:45 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
