/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsevigen <bsevigen@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 18:53:24 by bsevigen          #+#    #+#             */
/*   Updated: 2025/09/10 18:28:19 by bsevigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	if (s == NULL)
		return (0);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (0);
}

static char	*read_line(int fd, char *str)
{
	t_gnl_read	x;

	x.buffer = malloc(BUFFER_SIZE + 1);
	if (!x.buffer)
		return (NULL);
	x.bytes = 1;
	while (x.bytes > 0 && !ft_strchr(str, '\n'))
	{
		x.bytes = read(fd, x.buffer, BUFFER_SIZE);
		if (x.bytes < 0)
		{
			free(x.buffer);
			if (str)
				free(str);
			return (NULL);
		}
		if (x.bytes)
		{
			x.buffer[x.bytes] = '\0';
			str = ft_strjoin(str, x.buffer);
		}
	}
	free(x.buffer);
	return (str);
}

static char	*get_remain_line(char *str)
{
	char	*newline;
	char	*remain;

	if (!str)
		return (NULL);
	newline = ft_strchr(str, '\n');
	if (!newline)
	{
		free(str);
		return (NULL);
	}
	remain = ft_strdup(newline + 1);
	free(str);
	return (remain);
}

static char	*get_single_line(char *str)
{
	char	*line;
	int		count;

	count = 0;
	if (!str)
		return (NULL);
	while (str[count] != '\n' && str[count] != '\0')
		count++;
	line = ft_substr_new(str, 0, count);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(str), NULL);
	if (!str)
		str = NULL;
	str = read_line(fd, str);
	if (!str)
		return (NULL);
	line = get_single_line(str);
	if (!line)
		return (NULL);
	str = get_remain_line(str);
	return (line);
}
