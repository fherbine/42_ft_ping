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

