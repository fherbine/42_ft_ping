/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fherbine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 11:31:15 by fherbine          #+#    #+#             */
/*   Updated: 2017/11/11 17:56:54 by fherbine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	*ft_memrcpy(void *dst, const void *src, size_t n)
{
	while (n > 0)
	{
		n--;
		((char *)dst)[n] = ((char *)src)[n];
	}
	return ((void *)dst);
}

void			*ft_memmove(void *dst, const void *src, size_t len)
{
	if (src > dst)
		dst = (char *)ft_memcpy(dst, src, len);
	else
		dst = (char *)ft_memrcpy(dst, src, len);
	return ((void *)dst);
}
