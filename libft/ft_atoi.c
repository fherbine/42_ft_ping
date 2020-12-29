/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fherbine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 10:27:10 by fherbine          #+#    #+#             */
/*   Updated: 2018/02/27 17:07:52 by fherbine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	size_t	i;
	int		sgn;
	int		res;

	if (!str)
		return (0);
	i = 0;
	sgn = 1;
	res = 0;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n' || str[i] == '\r' \
			|| str[i] == '\t' || str[i] == '\v')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		sgn = (str[i] == '-') ? -1 : 1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		res = str[i] - 48 + 10 * res;
		i++;
	}
	return (res * sgn);
}
