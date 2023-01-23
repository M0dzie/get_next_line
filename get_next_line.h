/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:55:35 by thmeyer           #+#    #+#             */
/*   Updated: 2023/01/05 13:21:44 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 15
# endif

char	*gnl_free_join(char *stash, char *buffer);
char	*gnl_line(char *stash);
char	*gnl_next(char *stash);
char	*get_next_line(int fd);
char	*gnl_read_line(int fd, char *stash);
char	*gnl_strjoin(char *stash, char *buffer);

int		gnl_strchr(const char *s, char c);

size_t	ft_strlen(const char *s);

#endif
