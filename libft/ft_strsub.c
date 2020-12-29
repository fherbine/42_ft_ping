/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fherbine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 10:29:12 by fherbine          #+#    #+#             */
/*   Updated: 2017/11/14 11:50:13 by fherbine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(const char *s, unsigned int start, size_t len)
{
	char			*cpy;
	unsigned int	i;

	i = 0;
	if (!(s))
		return (NULL);
	if ((cpy = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	while ((size_t)i < len)
	{
		cpy[i] = s[start];
		start++;
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
