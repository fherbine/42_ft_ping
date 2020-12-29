/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fherbine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 14:23:20 by fherbine          #+#    #+#             */
/*   Updated: 2017/11/09 16:05:23 by fherbine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	i2;
	size_t	tmp;
	char	*ret;

	i = 0;
	i2 = 0;
	tmp = 0;
	ret = NULL;
	while (haystack[i] != '\0')
	{
		while (haystack[tmp] == needle[i2] && needle[i2] != '\0')
		{
			tmp++;
			i2++;
			if (needle[i2] == '\0')
				return ((char *)&haystack[i]);
		}
		i2 = 0;
		i++;
		tmp = i;
	}
	if (needle[i2] == '\0')
		return ((char *)haystack);
	return (ret);
}
