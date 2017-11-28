/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traceroute.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 15:11:14 by amarquez          #+#    #+#             */
/*   Updated: 2017/07/11 15:12:08 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACEROUTE_H
# define TRACEROUTE_H

# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <libft.h>
# include <sys/time.h>
# include <netinet/in_systm.h>
# include <netinet/in.h>
# include <netinet/ip.h>
# include <netinet/ip_icmp.h>
# include <netinet/udp.h>
# include <arpa/inet.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <errno.h>
# include <netinet/ip6.h>
# include <netinet/icmp6.h>

/*
** TRUE / FALSE constants
*/

# define TRUE 1
# define FALSE 0

/*
** Default BUFFSIZE
*/

# define BUFSIZE 1500

/*
** Handled options
*/

# define A_VERBOSE "-v"
# define A_HELP "-h"
# define A_TTL "-m"

/*
** Colors
*/

# define C_RED "\x1B[31m"
# define C_GRN "\x1B[32m"
# define C_YEL "\x1B[33m"
# define C_BLU "\x1B[34m"
# define C_MAG "\x1B[35m"
# define C_CYN "\x1B[36m"
# define C_WHT "\x1B[37m"
# define C_RST "\x1B[0m"

/*
** ROOT UID value
*/

# define ROOT_UID 0

/*
** program options, currently - [v, h, m] are handled
*/

typedef struct      s_env
{
    
    /*
    ** Verbose output
    */
    
    unsigned int    verbose;

    /*
    ** display usage
    */

    unsigned int    help;

    /*
    ** The maximum TTL or hop limit (defaults to 30)
    */

    unsigned int    ttl;

    /*
    ** Host to ping, can be DNS or IP address
    */

    char            *host;

}                   t_env;

/*
** Values of outgoing UDP datagram
*/

typedef struct      s_rec
{

    /*
    ** Sequence number
    */

    u_short         rec_seq;

    /*
    ** TTL the packet was sent with
    */

    u_short         rec_ttl;

    /*
    ** Time the packet was sent
    */

    struct timeval  rec_tv;

}                   t_rec;

/*
** t_proto structure is used to handle the difference between IPv4 and IPv6
*/

typedef struct      s_proto
{

    /*
    ** 
    */

    const char      *(*icmpcode) (int);

    /*
    **
    */

    int             (*recv) (int, struct timeval *);

    /*
    ** sockaddr{} for send, from getaddrinfo
    */

    struct sockaddr *sasend;

    /*
    ** sockaddr{} for receiving
    */

    struct sockaddr *sarecv;

    /*
    ** last sockaddr{} for receiving
    */

    struct sockaddr *salast;

    /*
    ** sockaddr{} for binding source port
    */

    struct sockaddr *sabind;

    /*
    ** lengtj of sockaddr{}s
    */

    socklen_t       salen;

    /*
    ** IPPROTO_xxx value for ICMP
    */

    int             icmpproto;

    /*
    ** setsockopt {} level to set TTL
    */

    int             ttllevel;

    /*
    ** setsockopt {} name to set TTL
    */

    int             ttloptname;

}                   t_proto;

/*
** t_env, t_proto and some values that will be needed/updated globally
*/

typedef struct      s_global
{
    /*
    ** 
    */

    char            recvbuf[BUFSIZE];
    
    /*
    **
    */

    char            sendbuf[BUFSIZE];

    /*
    ** # bytes of data following the ICMP header
    */

    int             datalen;

    /*
    **
    */

    u_short         sport;

    /*
    **
    */

    u_short         dport;

    /*
    ** # of packets sent
    */

    int             nsent;

    /*
    ** our PID
    */

    pid_t           pid;

    /*
    **
    */

    int             probe;

    /*
    **
    */

    int             nprobes;

    /*
    ** UDP socket fd (we send from here)
    */

    int             sendfd;

    /*
    ** ICMP fd (we read from here)
    */

    int             recvfd;

    /*
    ** TTL (Time To Live)
    */

    int             ttl;

    /*
    **
    */

    int             max_ttl;

    /*
    ** program env (args to run traceroute with)
    */

    t_env           *env;

    /*
    ** proto struct (either IPv4 or IPv6)
    */

    t_proto         *pr;

    /*
    **
    */

    t_rec           *rec;

}                   t_global;

/*
** Global variable
*/

extern t_global     *g_global;

/*
** interpreter functions
*/

int                 init_env(int argc, char **argv, t_env *env);

/*
** error funcions
*/

void                dump_usage(void);
void                ft_fatal_error(char *msg);


/*
** Socket functions
*/

char                *ft_sock_ntop_host(const struct sockaddr *sa, socklen_t salen);
void                ft_tv_subtract(struct timeval *out, struct timeval *in);

/*
** ICMP functions
*/

int                 recv_v4(int seq, struct timeval *tv);
int                 recv_v6(int seq, struct timeval *tv);
const char          *icmpcode_v4(int code);
const char          *icmpcode_v6(int code);
void                traceloop(void);

/*
** Init proto
*/

void                ft_init_proto_ipv4(t_proto *proto_v4);
void                ft_init_proto_ipv6(t_proto *proto_v6);

/*
** privilege functions
*/

void                ft_set_superuser(void);

/*
** Wrapper functions
*/

void                ft_gettimeofday(struct timeval *tv, void *foo);
void                *ft_calloc(size_t n, size_t size);

/*
** Signals
*/

void                sig_alrm(int signo);
void                sig_int(int signo);

/*
** Wrappers
*/

struct addrinfo     *ft_host_serv(const char *host, const char *serv, int family, int socktype);
void	            ft_bind(int fd, const struct sockaddr *sa, socklen_t salen);
void	            sock_set_port(struct sockaddr *sa, socklen_t salen, int port);
void	            ft_sendto(int fd, const void *ptr, size_t nbytes, int flags, const struct sockaddr *sa, socklen_t salen);
void                ft_tv_subtract(struct timeval *out, struct timeval *in);
int                 sock_cmp_addr(const struct sockaddr *sa1, const struct sockaddr *sa2, socklen_t salen);
int	                ft_socket(int domain, int type, int protocol);
#endif