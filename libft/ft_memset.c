/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fherbine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 11:03:27 by fherbine          #+#    #+#             */
/*   Updated: 2017/11/09 13:03:15 by fherbine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t i;

	i = 0;
	c = (unsigned char)c;
	while (i < len)
	{
		((unsigned char *)b)[i] = c;
		i++;
	}
	return ((void *)b);
}
