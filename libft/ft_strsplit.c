/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fherbine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 17:42:14 by fherbine          #+#    #+#             */
/*   Updated: 2017/11/14 13:13:13 by fherbine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_w(const char *s, char c)
{
	size_t		i;
	size_t		n;

	i = 0;
	n = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			n++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		if (s[i] == '\0')
			i--;
		i++;
	}
	return (n);
}

static	size_t	ft_l(const char *s, char c)
{
	size_t		i;
	size_t		n;

	i = 0;
	n = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
			n++;
		i++;
	}
	return (n);
}

static	void	ft_fill_str(size_t *n, char *str, size_t tmp, const char *s)
{
	size_t		c;

	c = 0;
	while (c < *n)
	{
		str[c] = s[tmp];
		c++;
		tmp++;
	}
	str[c] = '\0';
	*n = 0;
}

static	size_t	ft_search_str(size_t *i, char c, size_t *n, const char *s)
{
	size_t		tmp;

	tmp = 0;
	while (s[*i] == c && s[*i] != '\0')
		*i = *i + 1;
	if (s[*i] != c && s[*i] != '\0')
		tmp = *i;
	while (s[*i] != c && s[*i] != '\0')
	{
		*i = *i + 1;
		*n = *n + 1;
	}
	return (tmp);
}

char			**ft_strsplit(const char *s, char c)
{
	char		**tab;
	size_t		i;
	size_t		i2;
	size_t		n;
	size_t		tmp;

	i = 0;
	i2 = 0;
	n = 0;
	tmp = 0;
	if (!(s))
		return (NULL);
	if (!(tab = (char **)malloc(sizeof(char) * ft_l(s, c) * (ft_w(s, c) + 2))))
		return (NULL);
	while (i < ft_w(s, c))
	{
		tmp = ft_search_str(&i2, c, &n, s);
		if ((tab[i] = (char *)malloc(sizeof(char) * (n + 1))) == NULL)
			return (NULL);
		ft_fill_str(&n, tab[i], tmp, s);
		tmp = 0;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
