/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fherbine <fherbine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 19:50:18 by fherbine          #+#    #+#             */
/*   Updated: 2020/12/30 19:50:18 by fherbine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ping.h"

void	message_description_exit(char *identifier, char *msg, int status)
{
	dprintf((!status) ? STDOUT : STDERR, "ft_ping: %s: %s\n", identifier, msg);
	exit(status);
}

void	message_exit(char *msg, int status)
{
	dprintf((!status) ? STDOUT : STDERR, "ft_ping: %s\n", msg);
	exit(status);
}
