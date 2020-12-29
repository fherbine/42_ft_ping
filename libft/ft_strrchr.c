/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fherbine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 14:16:22 by fherbine          #+#    #+#             */
/*   Updated: 2017/11/11 18:06:54 by fherbine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*ret;

	i = 0;
	ret = NULL;
	while (s[i] != '\0')
	{
		if (c == s[i])
			ret = (char *)&s[i];
		i++;
	}
	if (c == '\0')
		return ((char *)&s[i]);
	return (ret);
}
