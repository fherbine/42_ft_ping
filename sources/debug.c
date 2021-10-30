/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fherbine <fherbine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 13:52:49 by fherbine          #+#    #+#             */
/*   Updated: 2021/10/21 13:52:49 by fherbine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ping.h"

void print_buffer(void *buffer_addr, ssize_t len)
{
	ssize_t count = 0;

	while (count < len)
	{
		if (count % 8 == 0)
			printf("%02ld | " , (len / 8) - (count / 8));

		printf("%02X ", *((uint8_t *)buffer_addr++));

		if ((count + 1) % 8 == 0 && count)
			printf("\n");

		count++;
	}
	printf("\n");
}

void print_ping_struct(t_ping *ping)
{
	char ipstr4[INET6_ADDRSTRLEN] = "";
	char ipstr6[INET6_ADDRSTRLEN] = "";

	if (ping->ipv4)
		inet_ntop(AF_INET, &(ping->ipv4->sin_addr), ipstr4, sizeof(ipstr4));
	
	if (ping->ipv6)
		inet_ntop(AF_INET6, &(ping->ipv6->sin6_addr), ipstr6, sizeof(ipstr6));

	printf("PING struct:\n");
	printf("name_or_service: %s\n", ping->name_or_service);
	printf("options_flags: 0b%08d\n", ft_atoi(ft_itoa_base(ping->options.flags, 2)));
	printf("IPv4: %s\n", ipstr4);
	printf("IPv6: %s\n", ipstr6);
}

