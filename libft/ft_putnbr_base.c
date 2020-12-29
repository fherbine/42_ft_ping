/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fherbine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 19:58:27 by fherbine          #+#    #+#             */
/*   Updated: 2018/01/02 10:37:51 by fherbine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_putnbr_base_recv(uintmax_t n, char *base, uintmax_t b)
{
	if (n >= b)
	{
		ft_putnbr_base_recv(n / b, base, b);
		ft_putnbr_base_recv(n % b, base, b);
	}
	else
		ft_putchar(base[n]);
}

void			ft_putnbr_base(uintmax_t n, char *base)
{
	uintmax_t	b;

	b = (uintmax_t)ft_strlen(base);
	ft_putnbr_base_recv(n, base, b);
}
