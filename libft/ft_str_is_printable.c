/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_printable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fherbine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 15:50:45 by fherbine          #+#    #+#             */
/*   Updated: 2017/11/14 21:15:51 by fherbine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_str_is_printable(char *str)
{
	size_t i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isprint((int)str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
