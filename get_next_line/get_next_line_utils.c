/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsevigen <bsevigen@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 18:53:29 by bsevigen          #+#    #+#             */
/*   Updated: 2025/09/10 18:11:42 by bsevigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	int		i;
	int		j;
	char	*temp_str;

	temp_str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (temp_str == NULL)
		return (NULL);
	i = 0;
	if (s1 != NULL)
	{
		while (s1[i] != '\0')
		{
			temp_str[i] = s1[i];
			i++;
		}
		free(s1);
	}
	j = 0;
	while (s2[j] != '\0')
	{
		temp_str[i + j] = s2[j];
		j++;
	}
	temp_str[i + j] = '\0';
	return (temp_str);
}

char	*ft_strdup(const char *s)
{
	char	*tmp;
	int		i;

	if (!ft_strlen(s))
		return (NULL);
	tmp = malloc(ft_strlen (s) + 1);
	if (!tmp)
		return (NULL);
	i = 0;
	while (s[i])
	{
		tmp [i] = s[i];
		i++;
	}
	tmp [i] = '\0';
	return (tmp);
}

static size_t	get_substr_len(const char *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	new_len;

	s_len = ft_strlen(s);
	if (start >= s_len)
		return (0);
	new_len = s_len - start;
	if (len > new_len)
		return (new_len);
	return (len);
}

char	*ft_substr_new(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	copy_len;

	if (!s)
		return (NULL);
	copy_len = get_substr_len(s, start, len);
	substr = malloc(copy_len + 2);
	if (!substr)
		return (NULL);
	i = -1;
	while (++i < copy_len)
		substr[i] = s[start + i];
	if (s[start + i] == '\n')
	{
		substr[i] = '\n';
		substr[i + 1] = '\0';
	}
	else
		substr[i] = '\0';
	return (substr);
}
