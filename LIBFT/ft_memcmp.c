/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eonen <eonen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:06:25 by eonen             #+#    #+#             */
/*   Updated: 2025/07/01 17:26:00 by eonen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*first;
	const unsigned char	*second;
	size_t				i;

	first = (const unsigned char *)s1;
	second = (const unsigned char *)s2;
	i = 0;
	while (i < n && first[i] == second[i])
		i++;
	if (i == n)
		return (0);
	return (first[i] - second[i]);
}
