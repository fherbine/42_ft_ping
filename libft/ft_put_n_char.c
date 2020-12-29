/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_n_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fherbine <fherbine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 16:47:36 by fherbine          #+#    #+#             */
/*   Updated: 2018/01/16 16:53:49 by fherbine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_put_n_char(int n, int c)
{
	char	*str;
	int		i;

	i = 0;
	if (!(str = (char *)malloc(sizeof(char) * (n + 1))))
		exit(EXIT_FAILURE);
	while (i < n)
	{
		str[i] = (char)c;
		i++;
	}
	str[i] = '\0';
	ft_putstr(str);
	free(str);
}
