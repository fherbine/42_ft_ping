/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fherbine <fherbine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 08:50:59 by fherbine          #+#    #+#             */
/*   Updated: 2021/10/30 08:50:59 by fherbine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ping.h"

t_rtt	*new_rtt(struct timeval sent, t_rtt *next)
{
	t_rtt *node;

	if (!(node = (t_rtt *)malloc(sizeof(t_rtt))))
		return (NULL);
	
	if (!next)
		node->next = NULL;
	else
		node->next = next;
	
	node->sent = timeval_to_ts(sent);
	node->received = 0;
	node->delta = 0;
	return (node);
}

void free_rtt(t_rtt *rtt)
{
	t_rtt *nxt;
	while (rtt)
	{
		nxt = rtt->next;
		free(rtt);
		rtt = nxt;
	}
	
}

