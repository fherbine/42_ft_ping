/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fherbine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 17:05:30 by fherbine          #+#    #+#             */
/*   Updated: 2018/01/16 15:54:18 by fherbine         ###   ########.fr       */
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

static size_t	ft_nlen(uintmax_t *nb, int *neg, intmax_t n)
{
	size_t		len;
	uintmax_t	tmp;

	len = 0;
	if (n < 0)
	{
		len++;
		*nb = (uintmax_t)n * -1;
		*neg = 1;
	}
	else
		*nb = n;
	tmp = *nb;
	while (tmp >= 10)
	{
		tmp = tmp / 10;
		len++;
	}
	len++;
	return (len);
}

char			*ft_itoa(intmax_t n)
{
	char		*ret;
	int			neg;
	size_t		len;
	size_t		i;
	uintmax_t	nb;

	nb = 0;
	neg = 0;
	i = 0;
	len = ft_nlen(&nb, &neg, n);
	if ((ret = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	while (nb >= 10)
	{
		ret[i] = nb % 10 + 48;
		i++;
		nb = nb / 10;
	}
	ret[i] = nb + 48;
	if (neg == 1)
		ret[i + 1] = '-';
	ret[len] = '\0';
	if (len > 1)
		ft_strrev(ret);
	return (ret);
}
