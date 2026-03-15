/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eonen <eonen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:22:17 by eonen             #+#    #+#             */
/*   Updated: 2025/07/01 17:45:41 by eonen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*news;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	news = (char *)malloc(s1len + s2len + 1);
	if (news == NULL)
		return (NULL);
	ft_memcpy(news, s1, s1len);
	ft_memcpy(news + s1len, s2, s2len);
	news[s1len + s2len] = '\0';
	return (news);
}
