/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fherbine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 11:59:37 by fherbine          #+#    #+#             */
/*   Updated: 2017/11/14 14:44:34 by fherbine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s)
{
	unsigned int	strt;
	size_t			len;
	size_t			end;

	strt = 0;
	if (!s)
		return (NULL);
	len = ft_strlen(s);
	end = len - 1;
	while (s[strt] == ' ' || s[strt] == '\n' || s[strt] == '\t')
		strt++;
	if (strt != len)
	{
		while (s[end] == ' ' || s[end] == '\n' || s[end] == '\t')
			end--;
	}
	else
		return (ft_strnew(0));
	return (ft_strsub(s, strt, end - (size_t)strt + 1));
}
