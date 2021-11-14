/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fherbine <fherbine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 10:57:48 by fherbine          #+#    #+#             */
/*   Updated: 2020/12/29 16:52:59 by fherbine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ping.h"

t_ping 	*g_ping;

t_ping	*get_ping_struct(void){
	if (!(g_ping = (t_ping *)malloc(sizeof(t_ping))))
		exit(EXIT_FAILURE);
	init_ping_struct(g_ping);
	return (g_ping);
}

int	main(int argc, char **argv)
{
	g_ping = get_ping_struct();
	parse(argc, argv, g_ping);
	dnslookup(g_ping->name_or_service, g_ping);
	ft_ping();
	return (0);
}
