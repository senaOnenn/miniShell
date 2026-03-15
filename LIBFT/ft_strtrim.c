/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eonen <eonen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:22:25 by eonen             #+#    #+#             */
/*   Updated: 2025/07/02 12:09:26 by eonen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*find_start(char const *s1, char const *set)
{
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	return ((char *)s1);
}

static char	*find_end(char const *s1, char const *set)
{
	char	*end;

	end = (char *)s1 + ft_strlen(s1) - 1;
	while (end > s1 && ft_strchr(set, *end))
		end--;
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*start;
	char	*end;
	char	*trimmedstr;
	size_t	copylen;

	if (!s1 || !set)
		return (NULL);
	start = find_start(s1, set);
	if (*start == '\0')
		end = start - 1;
	else
		end = find_end(start, set);
	copylen = (end >= start) ? (size_t)(end - start + 1) : 0;
	trimmedstr = (char *)malloc(copylen + 1);
	if (!trimmedstr)
		return (NULL);
	ft_memcpy(trimmedstr, start, copylen);
	trimmedstr[copylen] = '\0';
	return (trimmedstr);
}