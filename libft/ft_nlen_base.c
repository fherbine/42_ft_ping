/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nlen_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fherbine <fherbine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 18:58:37 by fherbine          #+#    #+#             */
/*   Updated: 2017/12/25 19:01:32 by fherbine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_nlen_base(uintmax_t n, int base)
{
	size_t	len;

	len = 0;
	while (n >= (uintmax_t)base)
	{
		n = n / base;
		len++;
	}
	len++;
	return (len);
}
