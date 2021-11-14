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

void get_error(struct msghdr msg)
{
	struct icmp *orig_icmp = NULL;
	struct ip *recvip;
	struct msghdr oreply;
	t_sockaddr_in remote;

	recvip = msg.msg_iov->iov_base;
	char ctrlbuffer[CMSG_SPACE(sizeof(uint8_t))];
	char buff[sizeof(struct icmp) + sizeof(struct iphdr)];

	ft_bzero(&oreply, sizeof(oreply));

	oreply.msg_control = ctrlbuffer;
	oreply.msg_controllen = sizeof(ctrlbuffer);
	oreply.msg_iovlen = 1;
	oreply.msg_namelen = sizeof(remote);
	oreply.msg_name = &remote;

	struct iovec iov;
	iov.iov_len = sizeof(struct icmp) + sizeof(struct iphdr);
	iov.iov_base = buff;
	oreply.msg_iov = &iov;

	struct timeval now;
	gettimeofday(&now, NULL);

	ssize_t ret =  recvmsg(g_ping->sockfd, &msg, MSG_DONTWAIT);
	ret =  recvmsg(g_ping->sockfd, &oreply, MSG_ERRQUEUE);
	if (ret == -1)
	{
		printf("%s ", strerror(errno));
		message_exit("Cannot get error paquet.", EXIT_FAILURE, 0);
	}

	struct cmsghdr *buf;
	for (buf = CMSG_FIRSTHDR(&oreply); buf != NULL; buf = CMSG_NXTHDR(&oreply, buf)){
	// https://stackoverflow.com/a/11918768/12113451
		struct sock_extended_err *sock_err = (struct sock_extended_err*)CMSG_DATA(buf);

		if (sock_err)
		{
			if (sock_err->ee_origin == SO_EE_ORIGIN_ICMP)
			{
				char host[NI_MAXHOST] = "";
				if (getnameinfo(((t_sockaddr *)msg.msg_name), sizeof(t_sockaddr_in), host, NI_MAXHOST, NULL, 0, 0))
					exit(EXIT_FAILURE);

				orig_icmp = oreply.msg_iov->iov_base;

				if (g_ping->options.flags & PING_OPT_QUIET)
					continue ;

				if (g_ping->options.flags & PING_OPT_SHOW_TIMESTAMPS)
					printf("[%ld.%ld] ", now.tv_sec, now.tv_usec);

				printf("From %s (%s) icmp_seq=%u ", host,
					inet_ntoa(((t_sockaddr_in *)msg.msg_name)->sin_addr), UINT16_REVERSE_ENDIANESS(orig_icmp->icmp_seq));
				if (g_ping->options.flags & PING_OPT_DEBUG)
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

void signal_handler(int signal)
{
	if (signal != SIGINT)
		exit(EXIT_FAILURE);

	close(g_ping->sockfd);

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

uint8_t get_icmp(struct msghdr msg)
{
	void *buffer = msg.msg_iov->iov_base;
	struct ip *recvip;
	struct icmp *recvicmp;
	recvip = buffer;
	recvicmp = buffer + sizeof(struct ip);

	if (recvicmp->icmp_type != ICMP_ECHOREPLY)
		{
			if (recvmsg(g_ping->sockfd, &msg, MSG_DONTWAIT) >= 0)
				get_icmp(msg);
			return (0);
		}

	struct timeval now;
	gettimeofday(&now, NULL);
	t_time now_ts = timeval_to_ts(now);

	g_ping->rtts->received = now_ts;
	g_ping->rtts->delta = g_ping->rtts->received - g_ping->rtts->sent;
	uint16_t len = UINT16_REVERSE_ENDIANESS(recvip->ip_len) - sizeof(struct iphdr);
	g_ping->summary.received++;

	t_nameinfo info;
	t_sockaddr_in ipsrc;
	ft_bzero(&ipsrc, sizeof(t_sockaddr_in));
	ipsrc.sin_addr = recvip->ip_src;
	ipsrc.sin_family = AF_INET;
	reversedns4(&ipsrc, &info);
	
	if (g_ping->options.flags & PING_OPT_QUIET)
		return (1);

	if (g_ping->options.flags & PING_OPT_AUDIBLE)
		printf("\a");

	if (g_ping->options.flags & PING_OPT_SHOW_TIMESTAMPS)
		printf("[%ld.%ld] ", now.tv_sec, now.tv_usec);

	printf("%u bytes from %s (%s): icmp_seq=%u ttl=%u time=%.2f ms", len, info.host, \
		inet_ntoa(recvip->ip_src), UINT16_REVERSE_ENDIANESS(recvicmp->icmp_seq), \
		recvip->ip_ttl, g_ping->rtts->delta);
	
	if (g_ping->options.flags & PING_OPT_DEBUG)
		printf(" icmp_type=%u icmp_code=%u", recvicmp->icmp_type, recvicmp->icmp_code);

	printf("\n");
	return (1);
}

void ft_ping(void)
{
	uint8_t is_sent = 0;
	char reply_buffer[sizeof(struct iphdr) + PACKET_SIZE];

	// sockaddr

	t_sockaddr *target_addr = (t_sockaddr *)g_ping->ipv4;

	// Création socket
	if ((g_ping->sockfd = socket(target_addr->sa_family, SOCK_RAW, IPPROTO_ICMP)) == -1)
		message_exit("Cannot create socket. Are you root ?", EXIT_FAILURE, 0);

	signal(SIGINT, &signal_handler);

	int ttl_val = PING_DEFAULT_TTL;

	if (g_ping->options.flags & PING_OPT_CUSTOM_TTL)
		ttl_val = ft_atoi(g_ping->options.optn_data[PING_OPT_CUSTOM_TTL]);
	if (setsockopt(g_ping->sockfd, IPPROTO_IP, IP_TTL, &ttl_val, sizeof(ttl_val)) < 0)
		message_exit("cannot set unicast time-to-live: Invalid argument", EXIT_FAILURE, 0);

	int on = 1;
	if (setsockopt(g_ping->sockfd, IPPROTO_IP, IP_RECVERR, &on, sizeof(int)) == -1)
		message_exit("Cannot set RECVERR socket option.", EXIT_FAILURE, 0);
	// -----

	while(1)
	{
		if (prepare_request(g_ping, target_addr->sa_family) == -1)
			message_exit("An error occured during request packet creation.", EXIT_FAILURE, 0);
		
		// prepare reply
		struct msghdr msg;
		struct iovec iov;
		t_sockaddr_in remote;
		ft_memset(&remote, 0, sizeof(remote));
		ft_memset(reply_buffer, 0, sizeof(struct iphdr) + PACKET_SIZE);

		iov.iov_base = reply_buffer;
		iov.iov_len = sizeof(reply_buffer);

		msg.msg_control = NULL;
		msg.msg_controllen = 0;
		msg.msg_flags = 0;
		msg.msg_name = &remote;
		msg.msg_namelen = sizeof(remote);
		msg.msg_iov = &iov;
		msg.msg_iovlen = 1;
		// ----

		//send ICMP
		send_ping_echo(g_ping->sockfd, g_ping->request_buffer, target_addr);

		int total_packet_size = sizeof(struct iphdr) + PACKET_SIZE;
		int payload_size = PACKET_SIZE - sizeof(struct icmphdr);
		char *ipstr = ip2str(target_addr);
		if (!is_sent)
			printf("PING %s (%s) %d(%d) bytes of data.\n", g_ping->name_or_service, ipstr, payload_size, total_packet_size);
		free(ipstr);
		is_sent = 1;

		ft_sleep(0.05);

		ssize_t ret =  recvmsg(g_ping->sockfd, &msg, MSG_TRUNC | MSG_WAITALL);
		if (ret > 0)
			get_icmp(msg);
		else
			get_error(msg);
		ft_sleep(0.95);
	}
}