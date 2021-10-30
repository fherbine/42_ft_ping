/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fherbine <fherbine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 16:12:58 by fherbine          #+#    #+#             */
/*   Updated: 2021/10/25 16:12:58 by fherbine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ping.h"

//strerror
#include <string.h>
#include <errno.h>



int prepare_request(t_ping *ping, uint8_t af)
{
	static int seq = 0;
	seq++;

	// NOW
	struct timeval now;
	gettimeofday(&now, NULL);
	ping->rtts = new_rtt(now, ping->rtts);

	if (af == AF_INET)
	{
		struct icmp icmp_request;
		ft_bzero(&icmp_request, sizeof(icmp_request));
		ft_bzero(ping->request_buffer, PACKET_SIZE);
		icmp_request.icmp_type = ICMP_ECHO;
		icmp_request.icmp_code = 0;
		icmp_request.icmp_hun.ih_idseq.icd_id = (uint16_t)getpid();
		icmp_request.icmp_hun.ih_idseq.icd_seq = UINT16_REVERSE_ENDIANESS(seq);
		icmp_request.icmp_dun.id_ts.its_otime = (n_time)now.tv_sec;
		uint16_t cksum =  compile_checksum(&(icmp_request), sizeof(icmp_request));
		icmp_request.icmp_cksum = cksum;
		ft_memcpy(ping->request_buffer, &icmp_request, sizeof(icmp_request));
	}
	else if (af == AF_INET6)
	{
		struct icmp6_hdr h_icmp6;
		ft_bzero(&h_icmp6, sizeof(h_icmp6));
		h_icmp6.icmp6_code = 0;
		h_icmp6.icmp6_type = ICMP6_ECHO_REQUEST;
		h_icmp6.icmp6_id = (uint16_t)getpid();
		h_icmp6.icmp6_seq = UINT16_REVERSE_ENDIANESS(seq);
		uint16_t cksum =  compile_checksum(&(h_icmp6), sizeof(h_icmp6));
		h_icmp6.icmp6_cksum = cksum;
		ft_bzero(ping->request_buffer, PACKET_SIZE);
		ft_memcpy(ping->request_buffer, &h_icmp6, sizeof(h_icmp6));
	}

	return (0);
}

int prepare_reply(t_ping *ping, t_sockaddr target_ip)
{
	struct icmp recvicmp;
	struct icmp6_hdr recvicmp6;
	struct ip recvip;
	struct ip6_hdr recvip6;
	struct iovec *iov = (struct iovec *)malloc(sizeof(struct iovec) * 2);
	ft_bzero(iov, sizeof(struct iovec) * 2);
	struct msghdr msg;

	bzero(ping->reply_buffer, sizeof(*(ping->reply_buffer)));
	bzero(iov, sizeof(struct iovec) * 2);
	bzero(&recvicmp, sizeof(recvicmp));
	bzero(&recvicmp6, sizeof(recvicmp6));
	bzero(&recvip, sizeof(recvip));
	bzero(&recvip6, sizeof(recvip6));
	recvicmp.icmp_type = ICMP_TIME_EXCEEDED;
	recvicmp6.icmp6_type = ICMP6_TIME_EXCEEDED;

	iov[0].iov_base = (target_ip.sa_family == AF_INET) ? (void *)&recvip : (void *)&recvip6;
	iov[0].iov_len = (target_ip.sa_family == AF_INET) ? sizeof(struct ip): sizeof(struct ip6_hdr);
	iov[1].iov_base = (target_ip.sa_family == AF_INET) ? (void *)&recvicmp : (void *)&recvicmp6;
	iov[1].iov_len = (target_ip.sa_family == AF_INET) ? sizeof(struct icmp) : sizeof(struct icmp6_hdr);

	bzero(&msg, sizeof(msg));
	ping->reply_buffer->msg_name = (void *)&target_ip;
	ping->reply_buffer->msg_namelen = sizeof(target_ip);
	ping->reply_buffer->msg_flags = 0;
	ping->reply_buffer->msg_iovlen = 2;
	ping->reply_buffer->msg_iov = iov;
	ping->reply_buffer->msg_control = ping->ctrlbuffer;
	ping->reply_buffer->msg_controllen = sizeof(ping->ctrlbuffer);

	//ping->reply_buffer = &msg;
	return (0);
}

void send_ping_echo(int socket_fd, char *request, t_sockaddr *target)
{
	socklen_t addr_len = (target->sa_family == AF_INET) ? sizeof(t_sockaddr_in) : sizeof(t_sockaddr_in6);
	ssize_t bsent = sendto(socket_fd, (void *)request, PACKET_SIZE, 0, target, addr_len);
	if (bsent == -1)
		{
			if (errno == 101) {
				message_exit("connect: Network is unreachable", EXIT_FAILURE, 0);
			}
			message_exit("Cannot send ping ECHO", EXIT_FAILURE, 0);
		}
	g_ping->summary.transmitted += 1;
}

void get_error(t_ping *ping, int sockfd)
{
	struct icmp orig_icmp;
	struct ip recvip;
	struct iphdr recviph;
	struct msghdr oreply;

	recvip = *((struct ip *)(ping->reply_buffer->msg_iov[0].iov_base));
	recviph = *((struct iphdr *)(ping->reply_buffer->msg_iov[0].iov_base));
	bzero(&orig_icmp, sizeof(orig_icmp));
	bzero(&oreply, sizeof(oreply));

	oreply.msg_control = ping->ctrlbuffer;
	oreply.msg_controllen = sizeof(ping->ctrlbuffer);
	oreply.msg_iovlen = 1;

	struct iovec iov[1];
	iov[0].iov_len = sizeof(orig_icmp);
	iov[0].iov_base = &orig_icmp;
	oreply.msg_iov = iov;

	struct timeval now;
	gettimeofday(&now, NULL);

	ssize_t ret =  recvmsg(sockfd, &oreply, MSG_TRUNC | MSG_ERRQUEUE);
	if (ret == -1)
		message_exit("Cannot get error paquet.", EXIT_FAILURE, 0);

	struct cmsghdr *buf;
	buf = CMSG_FIRSTHDR(&oreply);
	// https://stackoverflow.com/a/11918768/12113451
	struct sock_extended_err *sock_err = (struct sock_extended_err*)CMSG_DATA(buf);
	if (sock_err)
	{
		if (sock_err->ee_origin == SO_EE_ORIGIN_ICMP)
		{
			t_nameinfo info;
			t_sockaddr_in ipsrc;
			ipsrc.sin_addr = recvip.ip_src;
			ipsrc.sin_family = AF_INET;
			reversedns4(&ipsrc, &info);

			if (ping->options.flags & PING_OPT_SHOW_TIMESTAMPS)
				printf("[%ld.%ld] ", now.tv_sec, now.tv_usec);

			printf("From %s (%s) icmp_seq=%u ", info.host,
				inet_ntoa(recvip.ip_src), UINT16_REVERSE_ENDIANESS(orig_icmp.icmp_seq));
			if (ping->options.flags & PING_OPT_DEBUG)
				printf("type=%u code=%u", sock_err->ee_type, sock_err->ee_code);
			else
			{
				if (sock_err->ee_type == ICMP_TIME_EXCEEDED)
					printf("Time to live exceeded");
				else if (sock_err->ee_type == ICMP_DEST_UNREACH)
					printf("Destination Net Unreachable");
				else if (sock_err->ee_type == ICMP_SOURCE_QUENCH)
					printf("Source Quench");
				else if (sock_err->ee_type == ICMP_REDIRECT)
					printf("Redirect (change route)");
			}
			printf("\n");
		}
	}
}

uint8_t get_reply(t_ping *ping, int sfd)
{
	//print_ping_struct(ping);
	struct ip recvip;
	struct icmp recvicmp;
	recvip = *((struct ip *)(ping->reply_buffer->msg_iov[0].iov_base));
	recvicmp = *((struct icmp *)(ping->reply_buffer->msg_iov[1].iov_base));
	
	if (recvicmp.icmp_type != ICMP_ECHOREPLY)
	{
		if (recvicmp.icmp_type == ICMP_ECHO)
		{
			prepare_reply(ping, *((t_sockaddr *)ping->ipv4));
			// pinging localhost
			if (recvmsg(sfd, (ping->reply_buffer), MSG_TRUNC | MSG_WAITALL) > 0)
			{
				uint8_t ret = get_reply(ping, sfd);
				free(ping->reply_buffer->msg_iov);
				ping->reply_buffer->msg_iov = NULL; 
				if (!ret)
					return (0);
				return (1);
			}

		}
		ft_sleep(0.05);
		get_error(ping, sfd);
		ft_sleep(0.95);
		return (0);
	}

	struct timeval now;
	gettimeofday(&now, NULL);
	t_time now_ts = timeval_to_ts(now);

	ping->rtts->received = now_ts;
	ping->rtts->delta = ping->rtts->received - ping->rtts->sent;
	uint16_t len = UINT16_REVERSE_ENDIANESS(recvip.ip_len) - sizeof(struct iphdr);
	ping->summary.received++;

	t_nameinfo info;
	t_sockaddr_in ipsrc;
	ft_bzero(&ipsrc, sizeof(t_sockaddr_in));
	ipsrc.sin_addr = recvip.ip_src;
	ipsrc.sin_family = AF_INET;
	reversedns4(&ipsrc, &info);
	//struct hostent *host = gethostbyaddr(&ipsrc, sizeof(t_sockaddr_in), AF_INET);

	if (ping->options.flags & PING_OPT_QUIET)
		return (1);

	if (ping->options.flags & PING_OPT_AUDIBLE)
		printf("\a");

	if (ping->options.flags & PING_OPT_SHOW_TIMESTAMPS)
		printf("[%ld.%ld] ", now.tv_sec, now.tv_usec);

	printf("%u bytes from %s (%s): icmp_seq=%u ttl=%u time=%.2f ms", len, info.host, \
		inet_ntoa(recvip.ip_src), UINT16_REVERSE_ENDIANESS(recvicmp.icmp_seq), \
		recvip.ip_ttl, ping->rtts->delta);
	
	if (ping->options.flags & PING_OPT_DEBUG)
		printf(" icmp_type=%u icmp_code=%u", recvicmp.icmp_type, recvicmp.icmp_code);

	printf("\n");
	return (1);
}

void summarize(t_ping *ping)
{
	ping->summary.lost = ping->summary.transmitted - ping->summary.received;
	t_time min = (t_time)DBL_MAX, max = 0.0, avg = 0.0, sum = 0.0, v = 0.0;
	unsigned int nrtt = 0;
	t_rtt *prtts = ping->rtts;

	while (prtts)
	{
		sum += prtts->delta;
		if (prtts->delta <= min)
			min = prtts->delta;
		if (prtts->delta >= max)
			max = prtts->delta;
		prtts = prtts->next;
		nrtt++;
	}
	avg = sum / (t_time)nrtt;
	ping->summary.min = min;
	ping->summary.max = max;
	ping->summary.avg = avg;
	prtts = ping->rtts;
	sum = 0.0;
	while (prtts)
	{
		sum += (prtts->delta - avg) * (prtts->delta - avg);
		prtts = prtts->next;
	}
	v = sum / (t_time)nrtt;
	ping->summary.mdev = ft_sqrt(v);

	struct timeval now;
	gettimeofday(&now, NULL);
	t_time now_ts = timeval_to_ts(now);

	ping->summary.end = now_ts;
	ping->summary.total_time =  ping->summary.end - ping->summary.start;
}

void handler(int signal)
{
	if (signal != SIGINT)
		exit(EXIT_FAILURE);

	summarize(g_ping);
	printf("\n--- %s ft_ping statistics ---\n", g_ping->name_or_service);
	printf("%u packets transmitted, %u received, ", g_ping->summary.transmitted, g_ping->summary.received);

	if (g_ping->summary.lost)
		printf("+%u errors, ", g_ping->summary.lost);
	
	uint32_t packet_loss = g_ping->summary.lost / g_ping->summary.transmitted * 100;
	printf("%u%% packet loss, time %ums\n", packet_loss, g_ping->summary.total_time);
	printf("rtt min/avg/max/mdev = %.3f/%.3f/%.3f/%.3f ms\n", g_ping->summary.min, g_ping->summary.avg, g_ping->summary.max, g_ping->summary.mdev);
	proper_exit(EXIT_SUCCESS);
}

void ft_ping(t_ping *ping)
{
	int socket_fd;
	uint8_t is_sent = 0;

	// sockaddr

	t_sockaddr *target_addr = (t_sockaddr *)ping->ipv4;;


	// Création socket
	if ((socket_fd = socket(target_addr->sa_family, SOCK_RAW, IPPROTO_ICMP)) == -1)
		message_exit("Cannot create socket. Are you root ?", EXIT_FAILURE, 0);

	signal(SIGINT, &handler);

	int ttl_val = PING_DEFAULT_TTL;

	if (ping->options.flags & PING_OPT_CUSTOM_TTL)
		ttl_val = ft_atoi(ping->options.optn_data[PING_OPT_CUSTOM_TTL]);
	if (setsockopt(socket_fd, IPPROTO_IP, IP_TTL, &ttl_val, sizeof(ttl_val)) < 0)
		message_exit("cannot set unicast time-to-live: Invalid argument", EXIT_FAILURE, 0);

	int on = 1;
	if (setsockopt(socket_fd, IPPROTO_IP, IP_RECVERR, &on, sizeof(int)) == -1)
		message_exit("Cannot set RECVERR socket option.", EXIT_FAILURE, 0);
	// -----

	// Receive package
	while (1)
	{
		// SND struct
		if (prepare_request(ping, target_addr->sa_family) == -1)
			message_exit("An error occured during request packet creation.", EXIT_FAILURE, 0);
		
		// RCV structs
		prepare_reply(ping, *target_addr);

		//send ICMP
		send_ping_echo(socket_fd, ping->request_buffer, target_addr);

		int total_packet_size = sizeof(struct iphdr) + PACKET_SIZE;
		int payload_size = PACKET_SIZE - sizeof(struct icmphdr);
		char *ipstr = ip2str(target_addr);
		if (!is_sent)
			printf("PING %s (%s) %d(%d) bytes of data.\n", ping->name_or_service, ipstr, payload_size, total_packet_size);
		free(ipstr);
		is_sent = 1;
		ssize_t ret =  recvmsg(socket_fd, (ping->reply_buffer), MSG_TRUNC | MSG_WAITALL);
		if (ret == -1){
			ft_sleep(0.05);
			recvmsg(socket_fd, (ping->reply_buffer), MSG_TRUNC | MSG_WAITALL);
			get_error(ping, socket_fd);
			free(ping->reply_buffer->msg_iov);
			ping->reply_buffer->msg_iov = NULL; 
			ft_sleep(0.95);
			continue;
		}

		uint8_t r = get_reply(ping, socket_fd);
		free(ping->reply_buffer->msg_iov);
		ping->reply_buffer->msg_iov = NULL; 
		if (!r)
			continue ;
		ft_sleep(1);
	}
	
	close(socket_fd);
}