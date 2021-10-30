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

static void		display_option(char *letter, char *description, char *placeholder)
{
	printf("  %s %-16s%s\n", letter, placeholder, description);
}

void		proper_exit(int status)
{
	if (!g_ping->reply_buffer->msg_iov)
		free(g_ping->reply_buffer->msg_iov);
	if (g_ping->addrinfo)
		freeaddrinfo(g_ping->addrinfo);
	free(g_ping->reply_buffer);
	free_rtt(g_ping->rtts);
	free(g_ping);
	exit(status);
}

void		display_help(int status)
{
	printf("\nUsage\n");
	printf("  ping [options] <destination>\n");
	printf("\nOptions:\n");
	display_option("", "  dns name or ip address", "<destination>");
	display_option("-a", "use audible ping", "");
	display_option("-D", "print timestamps", "");
	display_option("-h", "print help and exit", "");
	display_option("-q", "quiet output", "");
	display_option("-t", "define time to live", "<ttl>");
	display_option("-v", "output ICMP type & code of ECHO REPLY", "");
	proper_exit(status);
}

void	message_description_exit(char *identifier, char *msg, int status)
{
	dprintf((!status) ? STDOUT : STDERR, "ft_ping: %s: %s\n", identifier, msg);
	proper_exit(status);
}

void	invalid_option(char option_char)
{
	dprintf(STDERR, "ft_ping: invalid option -- '%c'\n", option_char);
	display_help(EXIT_FAILURE);
}

void	message_exit(char *msg, int status, uint8_t with_help)
{
	dprintf((!status) ? STDOUT : STDERR, "ft_ping: %s\n", msg);
	if (with_help)
		display_help(status);
	proper_exit(status);
}
