/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fherbine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 10:44:54 by fherbine          #+#    #+#             */
/*   Updated: 2017/11/09 13:00:47 by fherbine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t i;

	i = 0;
	c = (unsigned char)c;
	while (i < n)
	{
		if (c == ((unsigned char *)s)[i])
			return ((void *)(&s)[i]);
		i++;
	}
	return (NULL);
}
