/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eonen <eonen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:02:41 by eonen             #+#    #+#             */
/*   Updated: 2025/08/16 10:33:06 by eonen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

char	*ft_strjoin(char *s1, const char *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*news;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	news = (char *)malloc(s1len + s2len + 1);
	if (!news)
	{
		free(s1);
		return (NULL);
	}
	ft_memcpy(news, s1, s1len);
	ft_memcpy(news + s1len, s2, s2len);
	news[s1len + s2len] = '\0';
	free(s1);
	return (news);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	slen;
	size_t	actuallen;

	if (s == NULL)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
		actuallen = 0;
	else
	{
		if (len + start > slen)
			actuallen = slen - start;
		else
			actuallen = len;
	}
	substr = (char *)malloc(actuallen + 1);
	if (substr == NULL)
		return (NULL);
	ft_memcpy(substr, s + start, actuallen);
	substr[actuallen] = '\0';
	return (substr);
}
