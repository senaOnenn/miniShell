/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eonen <eonen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:02:48 by eonen             #+#    #+#             */
/*   Updated: 2025/08/16 10:32:36 by eonen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s)
{
	int		len;
	char	*dest;
	int		i;

	len = ft_strlen(s);
	dest = malloc(len + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*read_and_add(int fd, char *saved)
{
	char	*buff;
	int		read_count;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	read_count = 1;
	while (!ft_strchr(saved, '\n') && read_count > 0)
	{
		read_count = read(fd, buff, BUFFER_SIZE);
		if (read_count == -1)
		{
			free(buff);
			free(saved);
			return (NULL);
		}
		buff[read_count] = '\0';
		saved = ft_strjoin(saved, buff);
	}
	free(buff);
	return (saved);
}

char	*seperate_line(char *saved)
{
	int		i;
	char	*line;

	if (!saved || !saved[0])
		return (NULL);
	i = 0;
	while (saved[i] != '\0' && saved[i] != '\n')
		i++;
	if (saved[i] == '\n')
		i++;
	line = ft_substr(saved, 0, i);
	return (line);
}

char	*update_saved(char *saved)
{
	int		i;
	char	*new_saved;

	if (!saved)
		return (NULL);
	i = 0;
	while (saved[i] && saved[i] != '\n')
		i++;
	if (!saved[i])
	{
		free(saved);
		return (NULL);
	}
	new_saved = ft_strdup(saved + i + 1);
	free(saved);
	return (new_saved);
}

char	*get_next_line(int fd)
{
	static char	*saved;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!saved)
		saved = ft_strdup("");
	saved = read_and_add(fd, saved);
	if (!saved)
		return (NULL);
	line = seperate_line(saved);
	saved = update_saved(saved);
	return (line);
}
