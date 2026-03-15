/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eonen <eonen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:18:59 by eonen             #+#    #+#             */
/*   Updated: 2025/07/01 17:43:54 by eonen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
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
