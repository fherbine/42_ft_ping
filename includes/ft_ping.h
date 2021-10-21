/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fherbine <fherbine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 16:51:33 by fherbine          #+#    #+#             */
/*   Updated: 2020/12/29 16:51:33 by fherbine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H
# include "../libft/libft.h"

#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

typedef struct addrinfo t_addrinfo;
typedef struct sockaddr_in t_sockaddr_in;

void                message_exit(char *msg, int status);
void	            message_description_exit(char *identifier, char *msg, int status);

t_addrinfo          *dnslookup4(char *host);

// int			        call_function(const char *fname, t_function_map *fmap, void *data);
uint8_t		        is_optionstr(const char *str);

t_params		    parse(int argc, char **argv);

void				print_buffer(void *buffer_addr, ssize_t len);

#endif
