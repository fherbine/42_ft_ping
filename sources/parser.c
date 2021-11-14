/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fherbine <fherbine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 20:15:10 by fherbine          #+#    #+#             */
/*   Updated: 2020/12/30 20:15:10 by fherbine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ping.h"


static uint8_t	is_str_digit(char *s)
{
	for (size_t i = (s[0] == '-') ? 1 : 0; i < ft_strlen(s); i++)
	{
		if (!ft_isdigit(s[i]))
			return (0);
	}
	return (1);
}

static 	uint8_t is_str_ip_bit(char *s)
{
	if (!is_str_digit(s) || ft_strlen(s) != 3)
		return (0);
	return (1);
}

uint8_t		is_str_is_ipv4(char *s)
{
	char **tab;
	int c = 0;
	tab = ft_strsplit(s, '.');

	for (int i = 0; tab[i] != NULL; i++)
	{
		if (is_str_ip_bit(tab[i]))
			c++;
		else
			return (0);
	}
	ft_free_tab(tab);

	if (c != 4)
		return (0);

	return (1);
}

void		init_ping_struct(t_ping *ping)
{
	ft_bzero(ping, sizeof(*ping));
	ping->name_or_service = NULL;
	ping->addrinfo = NULL;
	ping->rtts = NULL;

	ping->summary.min = 0.0;
	ping->summary.max = 0.0;
	ping->summary.avg = 0.0;
	ping->summary.mdev = 0.0;
	ping->summary.transmitted = 0;
	ping->summary.received = 0;
	ping->summary.lost = 0;
	ping->summary.total_time = 0;

	struct timeval now;
	gettimeofday(&now, NULL);
	t_time now_ts = timeval_to_ts(now);

	ping->summary.start = now_ts;
	ping->summary.end = now_ts;
}

void	check_optn_data(uint8_t flag, void *data)
{
	if ((flag & PING_OPT_CUSTOM_TTL) && (!is_str_digit((char *)data)))
		message_description_exit("invalid argument", (char *)data, EXIT_FAILURE);
	if ((flag & PING_OPT_CUSTOM_TTL) && (ft_atoi((char *)data) < 0 || ft_atoi((char *)data) > 255))
	{
		dprintf(STDERR, "ft_ping: invalid argument '%s': out of range: 0 <= value <= 255\n", (char *)data);
		proper_exit(EXIT_FAILURE);
	}
}

void	get_args(int start, int end, char **tab, t_ping **ping)
{
	int i = start;
	int i2 = 1;
	uint8_t option_value = 0;

	while (i < end)
	{
		if (tab[i][0] != '-' && !option_value)
		{
			if ((*ping)->name_or_service == NULL)
			{
				(*ping)->name_or_service = tab[i];
				i++;
				continue;
			}
			else
				display_help(EXIT_FAILURE);
		}
		else if (option_value)
		{
			check_optn_data(option_value, tab[i]);
			(*ping)->options.optn_data[option_value] = tab[i];
			option_value = 0;
			i++;
			continue;
		}
		
		i2 = 1;
		while (tab[i][i2])
		{   
			char option = tab[i][i2];

			if (option == 'h')
				(*ping)->options.flags |= PING_OPT_HELP;
			else if (option == 'a')
				(*ping)->options.flags |= PING_OPT_AUDIBLE;
			else if (option == 'v')
				(*ping)->options.flags |= PING_OPT_DEBUG;
			else if (option == 'q')
				(*ping)->options.flags |= PING_OPT_QUIET;
			else if (option == 'D')
				(*ping)->options.flags |= PING_OPT_SHOW_TIMESTAMPS;
			else if (option == 't')
			{
				(*ping)->options.flags |= PING_OPT_CUSTOM_TTL;
				option_value = PING_OPT_CUSTOM_TTL;
				
			}
			else
				invalid_option(option);
			i2++;
		}
		i++;
	}
}

void		parse(int argc, char **argv, t_ping *ping)
{
	if (argc < 2)
		message_description_exit("usage error", \
								 "Destination address required", EXIT_FAILURE);
	get_args(1, argc, argv, &ping);

	if (ping->options.flags & PING_OPT_HELP)
		display_help(EXIT_SUCCESS);
}
