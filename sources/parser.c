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

void		parse(int argc, char **argv)
{

	if (argc < 2)
		message_description_exit("usage error", \
								 "Destination address required", EXIT_FAILURE);

	int i = 0;
	while (i < argc){
		printf("%s\n", argv[i]);
		i++;
	}
}
