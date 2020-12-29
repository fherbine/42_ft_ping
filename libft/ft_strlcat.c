/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fherbine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 13:33:46 by fherbine          #+#    #+#             */
/*   Updated: 2017/11/12 22:00:30 by fherbine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;
	size_t	j;
	size_t	ret;

	i = 0;
	j = 0;
	ret = ft_strlen(dst);
	len = size - 1;
	if (size > ret)
	{
		while (dst[i] != '\0')
			i++;
		while (src[j] != '\0' && j + i < len)
		{
			dst[i + j] = src[j];
			j++;
		}
		dst[i + j] = '\0';
		return (ret + ft_strlen(src));
	}
	return (ft_strlen(src) + size);
}
