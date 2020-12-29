/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fherbine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 17:41:16 by fherbine          #+#    #+#             */
/*   Updated: 2017/11/11 17:41:19 by fherbine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr_recv(int n, int fd)
{
	if (n >= 10)
	{
		ft_putnbr_recv(n / 10, fd);
		ft_putnbr_recv(n % 10, fd);
	}
	else
		ft_putchar_fd(n + 48, fd);
}

void		ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		if (n == -2147483648)
		{
			ft_putnbr_fd(214748364, fd);
			ft_putchar_fd('8', fd);
		}
		else
			ft_putnbr_recv(n * -1, fd);
	}
	else
		ft_putnbr_recv(n, fd);
}
