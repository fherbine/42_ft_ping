/*
 * ft_ping 42 project POC.
 *
 * Date: 2021-10-21
 * 
 * How to compile:
 * 	clang -Wall -Wextra -Werror path/to/this/script.c
 * 
 * How to run:
 *  ./a.out <ip adress>
 * 
*/

// socket(...), sendto, getpid
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

// gettimeoday
#include <sys/time.h>
#include <netinet/in_systm.h>

// printf
#include <stdio.h>

// exit 
#include <stdlib.h>

//ICMP struct
#include <netinet/ip_icmp.h>

//ICMP struct
#include <netinet/ip.h>


// sockaddr_in
#include <netinet/in.h>

// ----- libft ??? ----

// close
#include <unistd.h>


//strerror
#include <string.h>
#include <errno.h>

// bzero
#include <string.h>

//timeval
#include <sys/time.h>

// inet_aton
#include <arpa/inet.h>

// sock_ext_err

#define SO_EE_ORIGIN_NONE    0
#define SO_EE_ORIGIN_LOCAL   1
#define SO_EE_ORIGIN_ICMP    2
#define SO_EE_ORIGIN_ICMP6   3

struct sock_extended_err {
    uint32_t ee_errno;       /* numéro d'erreur */
    uint8_t  ee_origin;      /* origine de l'erreur */
    uint8_t  ee_type;        /* type */
    uint8_t  ee_code;        /* code */
    uint8_t  ee_pad;         /* remplissage */
    uint32_t ee_info;        /* données supplémentaires */
    uint32_t ee_data;        /* autres données */
    /* Des données supplémentaires peuvent suivrent */
};

#define PING_TTL 1
#define PACKET_SIZE 64
#define CTRL_BUFFER_SIZE 1024
char ctrlbuffer[CTRL_BUFFER_SIZE];


#define UINT16_REVERSE_ENDIANESS(x) (uint16_t)(x << 8 | x >> 8)
typedef	double t_time;

t_time	timeval_to_ts(struct timeval dt)
{
	t_time ts;
	ts = ((double)dt.tv_sec * 1000) + ((double)dt.tv_usec / 1000);
	return (ts);
}

typedef struct		s_rtt {
	t_time			sent;
	t_time			received;
	t_time  		delta;
	struct s_rtt	*next;
}					t_rtt;

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
	while (rtt)
	{
		free(rtt);
		rtt = rtt->next;
	}
	
}

void exit_with_msg(char *msg)
{
	printf("%s", msg);
	exit(EXIT_FAILURE);
}

uint16_t compile_checksum(void *addr, ssize_t count)
{
	/* Inspired by RFC1141 */
	uint32_t sum = 0;

	while( count > 1 )  {
		/*  This is the inner loop */
			sum += *(uint16_t *)(addr);
			addr += 2;
			count -= 2;
	}

		/*  Add left-over byte, if any */
	if( count > 0 )
			sum += *(uint8_t *)addr;

		/*  Fold 32-bit sum to 16 bits */
	while (sum>>16)
		sum = (sum & 0xffff) + (sum >> 16);

	return(~sum);
}

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

int prepare_request(char **packet_ptr, t_rtt **rtts)
{
	char *packet;
	static int seq = 0;
	seq++;

	if (!(packet = (char *)malloc(sizeof(char) * (PACKET_SIZE + 1))))
		return (-1);

	// NOW
	struct timeval now;
	gettimeofday(&now, NULL);
	*rtts = new_rtt(now, *rtts);

	struct icmp icmp_request;
	bzero(&icmp_request, sizeof(icmp_request));
	bzero(packet, PACKET_SIZE);
	icmp_request.icmp_type = ICMP_ECHO;
	icmp_request.icmp_code = 0;
	icmp_request.icmp_hun.ih_idseq.icd_id = (uint16_t)getpid();
	icmp_request.icmp_hun.ih_idseq.icd_seq = UINT16_REVERSE_ENDIANESS(seq);
	icmp_request.icmp_dun.id_ts.its_otime = (n_time)now.tv_sec;
	uint16_t cksum =  compile_checksum(&(icmp_request), sizeof(icmp_request));
	icmp_request.icmp_cksum = cksum;
	memcpy(packet, &icmp_request, sizeof(icmp_request));

	*packet_ptr = packet;
	return (0);
}

void close_request(char **packet_ptr)
{
	free(*packet_ptr);
}

int prepare_reply(struct msghdr *msg_ptr, struct sockaddr_in target_ip)
{
	struct icmp recvicmp;
	struct ip recvip;
	struct iovec iov[2];
	struct msghdr msg;

	bzero(&recvicmp, sizeof(recvicmp));
	bzero(&recvip, sizeof(recvip));
	recvicmp.icmp_type = ICMP_TIME_EXCEEDED;

	iov[0].iov_base = &recvip;
	iov[0].iov_len = sizeof(struct ip);
	iov[1].iov_base = &recvicmp;
	iov[1].iov_len = sizeof(struct icmp);

	bzero(&msg, sizeof(msg));
	msg.msg_name = (void *)&target_ip.sin_addr;
	msg.msg_namelen = sizeof(target_ip.sin_addr);
	msg.msg_flags = 0;
	msg.msg_iovlen = 2;
	msg.msg_iov = iov;
	msg.msg_control = ctrlbuffer;
	msg.msg_controllen = sizeof(ctrlbuffer);

	*msg_ptr = msg;
	return (0);
}

void send_ping_echo(int socket_fd, char *request, struct sockaddr_in target)
{
	ssize_t bsent = sendto(socket_fd, (void *)request, PACKET_SIZE, 0, (struct sockaddr *)&target, sizeof(target));
	if (bsent == -1)
		printf("sendto %s\n", strerror(errno));
}

void get_error(struct ip *recvip, int sockfd)
{
	struct icmp orig_icmp;
	struct msghdr oreply;

	bzero(&orig_icmp, sizeof(orig_icmp));
	bzero(&oreply, sizeof(oreply));

	oreply.msg_control = ctrlbuffer;
	oreply.msg_controllen = sizeof(ctrlbuffer);
	oreply.msg_iovlen = 1;

	struct iovec iov[1];
	iov[0].iov_len = sizeof(orig_icmp);
	iov[0].iov_base = &orig_icmp;
	oreply.msg_iov = iov;

	ssize_t ret =  recvmsg(sockfd, &oreply, MSG_TRUNC | MSG_ERRQUEUE);
	if (ret == -1)
		printf("recv2 err %s  ", strerror(errno));

	struct cmsghdr *buf;
	buf = CMSG_FIRSTHDR(&oreply);
	// https://stackoverflow.com/a/11918768/12113451
	struct sock_extended_err *sock_err = (struct sock_extended_err*)CMSG_DATA(buf);
	if (sock_err)
	{
		if (sock_err->ee_origin == SO_EE_ORIGIN_ICMP && sock_err->ee_type == ICMP_DEST_UNREACH) 
		{
			/* Handle ICMP destination unreachable error codes */
			switch (sock_err->ee_code) 
			{
				case ICMP_NET_UNREACH:
					/* Handle this error */
					printf("Network Unreachable Error\n");
					break;
				case ICMP_HOST_UNREACH:
					/* Handle this error */
					printf("Host Unreachable Error\n");
					break;
				/* Handle all other cases. Find more errors :
					* http://lxr.linux.no/linux+v3.5/include/linux/icmp.h#L39
					*/

			}
		}
		else if (sock_err->ee_origin == SO_EE_ORIGIN_ICMP)
		{
			printf("X bytes from %s: seq=%u type=%u code=%u\n", 
				inet_ntoa(recvip->ip_src), UINT16_REVERSE_ENDIANESS(orig_icmp.icmp_seq),
				sock_err->ee_type, sock_err->ee_code
				);
			}
	}
}

void get_reply(struct msghdr *reply, t_rtt **rtts, int sfd)
{
	struct ip recvip;
	struct icmp recvicmp;
	recvip = *((struct ip *)(reply->msg_iov[0].iov_base));
	recvicmp = *((struct icmp *)(reply->msg_iov[1].iov_base));
	
	if (recvicmp.icmp_type != ICMP_ECHOREPLY)
	{
		get_error(&recvip, sfd);
		return ;
	}

	struct timeval now;
	gettimeofday(&now, NULL);
	t_time now_ts = timeval_to_ts(now);

	(*rtts)->received = now_ts;
	(*rtts)->delta = (*rtts)->received - (*rtts)->sent;
	uint16_t len = UINT16_REVERSE_ENDIANESS(recvip.ip_len) - sizeof(struct iphdr);

	//printf("(type=%u code=%u) ", recvicmp.icmp_type, recvicmp.icmp_code);

	printf("%u bytes from %s : icmp_seq=%u ttl=%u time=%.2f ms\n", len, \
		inet_ntoa(recvip.ip_src), UINT16_REVERSE_ENDIANESS(recvicmp.icmp_seq), \
		recvip.ip_ttl, (*rtts)->delta);
}

void ft_ping_poc(char *target_ip)
{
	int socket_fd;
	t_rtt *rtts = NULL;
	uint8_t is_sent = 0;

	// sockaddr
	struct sockaddr_in myaddr;
	myaddr.sin_family = AF_INET;
	bzero((void *)&myaddr, sizeof(myaddr));
	inet_aton(target_ip, &myaddr.sin_addr); // unauth

	// Création socket
	if ((socket_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) == -1){
		printf("%s\n", strerror(errno));
		exit_with_msg("KO -- cannot create socket");
	}

	int ttl_val = PING_TTL;
	if (setsockopt(socket_fd, IPPROTO_IP, IP_TTL,&ttl_val, sizeof(ttl_val)) < 0)
		printf("TTL %s\n", strerror(errno));

	int on = 1;
	if (setsockopt(socket_fd, IPPROTO_IP, IP_RECVERR, &on, sizeof(int)) == -1)
		printf("setsockopt -- RECVERR %s\n", strerror(errno));
	// -----

	// Receive package
	int i = 10;
	while (i)
	{
		i--;
		// SND struct 
		char *request;
		if (prepare_request(&request, &rtts) == -1)
			exit_with_msg("An error occured during request packet creation.");
		
		// RCV structs
		struct msghdr msg;
		prepare_reply(&msg, myaddr);

		//send ICMP
		send_ping_echo(socket_fd, request, myaddr);

		int total_packet_size = sizeof(struct iphdr) + PACKET_SIZE;
		int payload_size = PACKET_SIZE - sizeof(struct icmphdr);
		if (!is_sent)
			printf("PING %s (%s) %d(%d) bytes of data.\n", target_ip, target_ip, payload_size, total_packet_size);
		is_sent = 1;

		ssize_t ret =  recvmsg(socket_fd, &msg, MSG_TRUNC | MSG_WAITALL);
		if (ret == -1){
			printf("err %s\n", strerror(errno));
			continue;
		}

		get_reply(&msg, &rtts, socket_fd);
		sleep(1);
	}
	
	// Fermeture du socket
	close(socket_fd);
}

int	main(int argc, char **argv){
	(void)argc;
	ft_ping_poc(argv[1]);
	return(0);
}