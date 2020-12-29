/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nlen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fherbine <fherbine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 12:42:58 by fherbine          #+#    #+#             */
/*   Updated: 2018/01/02 10:35:52 by fherbine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int						ft_nlen_10(intmax_t n)
{
	size_t				len;
	unsigned long long	t;

	t = 0;
	len = 0;
	if (n < 0)
	{
		len++;
		t = (unsigned long long)(n * -1);
	}
	else
		t = (unsigned long long)n;
	while (t >= 10)
	{
		t = t / 10;
		len++;
	}
	len++;
	return (len);
}
