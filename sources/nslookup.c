/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nslookup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fherbine <fherbine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 16:55:25 by fherbine          #+#    #+#             */
/*   Updated: 2020/12/29 16:55:25 by fherbine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ping.h"


t_addrinfo			*dnslookup(char *host)
{
	t_addrinfo		hints;
	t_addrinfo		*first_info;

	ft_bzero(&hints, sizeof(t_addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags |= AI_CANONNAME;
	if (getaddrinfo(host, NULL, &hints, &first_info))
		message_description_exit(host, \
								 "Name or service not known", EXIT_FAILURE);
	
	if (!first_info)
		return (NULL);

	return (first_info);
}
