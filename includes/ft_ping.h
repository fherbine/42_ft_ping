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
#include <unistd.h>
#include <sys/time.h>
#include <netinet/in_systm.h>
#include <stdlib.h>
#include <netinet/ip_icmp.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <signal.h>
#include <float.h>

#include <netinet/icmp6.h>
#include <netinet/ip6.h>


typedef struct addrinfo t_addrinfo;
typedef struct sockaddr t_sockaddr;
typedef struct sockaddr_in t_sockaddr_in;
typedef struct sockaddr_in6 t_sockaddr_in6;
typedef struct msghdr t_msghdr;


#define PING_OPT_HELP 0x01
#define PING_OPT_DEBUG 0x02
#define PING_OPT_INET4 0x04
#define PING_OPT_INET6 0x08
#define PING_OPT_QUIET 0x10
#define PING_OPT_CUSTOM_TTL 0x20
#define PING_OPT_SHOW_TIMESTAMPS 0x40
#define PING_OPT_AUDIBLE 0x80

#define UINT16_REVERSE_ENDIANESS(x) (uint16_t)(x << 8 | x >> 8)

#define PING_DEFAULT_TTL 64
#define PACKET_SIZE 64
#define CTRL_BUFFER_SIZE 1024

typedef	double t_time;

// sock_ext_err
#define SO_EE_ORIGIN_NONE    0
#define SO_EE_ORIGIN_LOCAL   1
#define SO_EE_ORIGIN_ICMP    2
#define SO_EE_ORIGIN_ICMP6   3

struct sock_extended_err {
    uint32_t ee_errno;
    uint8_t  ee_origin;
    uint8_t  ee_type;
    uint8_t  ee_code;
    uint8_t  ee_pad;
    uint32_t ee_info;
    uint32_t ee_data;
};
//---------------

typedef struct		s_rtt {
	t_time			sent;
	t_time			received;
	t_time  		delta;
	struct s_rtt	*next;
}					t_rtt;

typedef struct	s_ping_options
{
	uint8_t		flags;
	char		*optn_data[256];
}				t_ping_options;

typedef struct s_ping_summary
{
	t_time		min;
	t_time		avg;
	t_time		max;
	t_time		mdev;
	t_time		start;
	t_time		end;
	uint32_t	total_time;
	uint32_t	transmitted;
	uint32_t	received;
	uint32_t	lost;
}				t_ping_summary;

typedef struct	s_ping
{
	char			*name_or_service;
	t_addrinfo		*addrinfo;
	t_ping_options	options;
	t_sockaddr_in	*ipv4;
	t_sockaddr_in6	*ipv6;
	t_rtt			*rtts;
	t_ping_summary	summary;
	char			request_buffer[PACKET_SIZE];
	int				sockfd;
}				t_ping;

extern t_ping	*g_ping;

typedef struct	s_nameinfo
{
	char		server[NI_MAXSERV];
	char		host[NI_MAXHOST];
}				t_nameinfo;

void                message_exit(char *msg, int status, uint8_t with_help);
void	            message_description_exit(char *identifier, char *msg, int status);
void				display_help(int status);
void				proper_exit(int status);

void				dnslookup(char *host, t_ping *ping);
void				reversedns4(t_sockaddr_in *addr, t_nameinfo *info);

void		    	parse(int argc, char **argv, t_ping *ping);

void				print_buffer(void *buffer_addr, ssize_t len);
void				print_ping_struct(t_ping *ping);

void				invalid_option(char option_char);
void				init_ping_struct(t_ping *ping);

uint16_t 			compile_checksum(void *addr, ssize_t count);
char				*ip4tostr(struct in_addr ip4);
char				*ip6tostr(struct in6_addr ip6);
char 				*ip2str(t_sockaddr *addr);
t_time				timeval_to_ts(struct timeval dt);
void				ft_sleep(double sec);

void 				ft_ping(void);

void 				free_rtt(t_rtt *rtt);
t_rtt				*new_rtt(struct timeval sent, t_rtt *next);

#endif
