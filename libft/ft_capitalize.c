/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_capitalize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fherbine <fherbine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 04:07:27 by fherbine          #+#    #+#             */
/*   Updated: 2018/09/08 04:11:28 by fherbine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_capitalize(char **p_str)
{
	char *str;
	int	i;

	str = *p_str;
	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}
}
