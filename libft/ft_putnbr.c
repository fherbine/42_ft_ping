/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fherbine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 17:39:40 by fherbine          #+#    #+#             */
/*   Updated: 2018/01/02 10:37:21 by fherbine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr_recv(intmax_t n)
{
	if (n >= 10)
	{
		ft_putnbr_recv(n / 10);
		ft_putnbr_recv(n % 10);
	}
	else
		ft_putchar(n + 48);
}

void		ft_putnbr(intmax_t n)
{
	if (n < 0)
	{
		ft_putchar('-');
		ft_putnbr_recv(n * -1);
	}
	else
		ft_putnbr_recv(n);
}
