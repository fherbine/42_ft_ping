/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fherbine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 17:05:30 by fherbine          #+#    #+#             */
/*   Updated: 2018/01/16 15:55:37 by fherbine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_strrev(char *str)
{
	size_t	s;
	size_t	e;
	char	tmp;

	s = 0;
	e = ft_strlen(str) - 1;
	while (s <= e)
	{
		tmp = str[s];
		str[s] = str[e];
		str[e] = tmp;
		s++;
		e--;
	}
	return (str);
}

static size_t	ft_nlen(uintmax_t *nb, uintmax_t n, uintmax_t base)
{
	size_t		len;
	uintmax_t	tmp;

	len = 0;
	*nb = n;
	tmp = *nb;
	while (tmp >= base)
	{
		tmp = tmp / base;
		len++;
	}
	len++;
	return (len);
}

char			*ft_itoa_base(uintmax_t n, uintmax_t base)
{
	char		*ret;
	char		*b;
	size_t		len;
	size_t		i;
	uintmax_t	nb;

	nb = 0;
	b = ft_strdup("0123456789abcdef");
	i = 0;
	len = ft_nlen(&nb, n, base);
	if ((ret = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	while (nb >= base)
	{
		ret[i] = b[nb % base];
		i++;
		nb = nb / base;
	}
	ret[i] = b[nb];
	ret[len] = '\0';
	if (len > 1)
		ft_strrev(ret);
	free(b);
	return (ret);
}
