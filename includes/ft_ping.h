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
#include <arpa/inet.h>

typedef struct addrinfo t_addrinfo;
typedef struct sockaddr_in t_sockaddr_in;
typedef struct sockaddr_in6 t_sockaddr_in6;


#define PING_OPT_HELP 0x01
#define PING_OPT_DEBUG 0x02
#define PING_OPT_INET6 0x04
#define PING_OPT_QUIET 0x08
#define PING_OPT_CUSTOM_TTL 0x10

typedef struct	s_ping_options
{
	uint8_t		flags;
	char		*optn_data[8];
}				t_ping_options;

typedef struct	s_ping
{
	t_ping_options	options;
	t_addrinfo		*addrinfo;
}				t_ping;


void                message_exit(char *msg, int status);
void	            message_description_exit(char *identifier, char *msg, int status);

t_addrinfo          *dnslookup(char *host);

// int			        call_function(const char *fname, t_function_map *fmap, void *data);
uint8_t		        is_optionstr(const char *str);

void		    parse(int argc, char **argv);

void				print_buffer(void *buffer_addr, ssize_t len);

#endif
