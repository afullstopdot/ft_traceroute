#include <traceroute.h>

extern int gotalarm;

/*
** Process ICMPv4 messages
** @return:
**  -3 on timeout
**	-2 on ICMP time exceeded in transit (caller keeps going)
**	-1 on ICMP port unreachable (caller is done)
**	>= 0 return value is some other ICMP unreachable code
*/

int                     recv_v4(int seq, struct timeval *tv)
{
	int				    hlen1;
	int				    hlen2;
	size_t	        	icmplen;
	int				    ret;
	socklen_t		    len;
	ssize_t			    n;
	struct ip		    *ip;
	struct ip		    *hip;
	struct icmp		    *icmp;
	struct udphdr	    *udp;

    /*
    ** Default value
    */

    gotalarm = 0;

    /*
    ** Deliver signal every 3 seconds
    */

    alarm(3);

    /*
    ** Infinit loop
    */

    while (42)
    {

        /*
        ** Check if alarm expired
        */

		if (gotalarm)
            return (-3);

        /*
        ** Set len to sock{} len
        */

        len = g_global->pr->salen;

        /*
        ** recieve message from destination host
        */

		n = recvfrom(g_global->recvfd, g_global->recvbuf, sizeof(g_global->recvbuf), 0, g_global->pr->sarecv, &len);
        if (n < 0)
        {

            /*
            ** Only continues if errno is EINTR
            */

			if (errno == EINTR)
				continue;
			else
                ft_fatal_error("recvfrom error");

		}

        /*
        ** Start of IP header
        */

        ip = (struct ip *) g_global->recvbuf;

        /*
        ** Length of IP header
        */

		hlen1 = ip->ip_hl << 2;
    
        /*
        ** Start of ICMP header
        */

        icmp = (struct icmp *) (g_global->recvbuf + hlen1);

        /*
        ** Check if there is enough to look at ICMP header
        */

		if ((icmplen = n - hlen1) < 8)
			continue;
    
        /*
        **
        */

        if (icmp->icmp_type == ICMP_TIMXCEED && icmp->icmp_code == ICMP_TIMXCEED_INTRANS)
        {

            /*
            ** Not enough data to look at inner IP
            */

			if (icmplen < 8 + sizeof(struct ip))
				continue ;

            /*
            **
            */

            hip = (struct ip *) (g_global->recvbuf + hlen1 + 8);

            /*
            **
            */

            hlen2 = hip->ip_hl << 2;

            /*
            ** Check if there is enough data to look at UDP ports
            */

			if ((int) icmplen < (int) (8 + hlen2 + 4))
				continue ;

            /*
            **
            */

            udp = (struct udphdr *) (g_global->recvbuf + hlen1 + 8 + hlen2);
            
            /*
            **
            */

            if (hip->ip_p == IPPROTO_UDP && udp->uh_sport == htons(g_global->sport) && udp->uh_dport == htons(g_global->dport + seq))
            {

                /*
                ** We hit an intermediate router
                */

				ret = -2;
				break;
            
            }

        }
        else if (icmp->icmp_type == ICMP_UNREACH)
        {
            
            /*
            ** Check if enough data to look at inner IP
            */

			if (icmplen < 8 + sizeof(struct ip))
				continue ;

            /*
            **
            */

            hip = (struct ip *) (g_global->recvbuf + hlen1 + 8);
            
            /*
            **
            */

            hlen2 = hip->ip_hl << 2;
            
            /*
            ** Check if there is enough data to look at the UDP ports
            */

			if ((int) icmplen < (int) (8 + hlen2 + 4))
				continue ;

            /*
            **
            */

            udp = (struct udphdr *) (g_global->recvbuf + hlen1 + 8 + hlen2);
            
            /*
            **
            */

            if (hip->ip_p == IPPROTO_UDP && udp->uh_sport == htons(g_global->sport) && udp->uh_dport == htons(g_global->dport + seq))
            {

                /*
                ** Check we have reached destinations
                */

				if (icmp->icmp_code == ICMP_UNREACH_PORT)
					ret = -1;
				else
					ret = icmp->icmp_code;
                break;

            }

        }

        /*
        ** If verbose, print output
        */

        if (g_global->env->verbose)
        {

            /*
            ** dump
            */

			printf(" (from %s: type = %d, code = %d)\n", ft_sock_ntop_host(g_global->pr->sarecv, g_global->pr->salen), icmp->icmp_type, icmp->icmp_code);
        }
        
        /*
        ** Some other ICMP error, recvfrom() again
        */

    }

    /*
    ** Dont leave alarm running
    */

    alarm(0);

    /*
    ** Get time of packet arrival
    */

    ft_gettimeofday(tv, NULL);

    /*
    **
    */

	return (ret);
}

/*
** Process ICMPv6 messages
** @return:
**  -3 on timeout
**	-2 on ICMP time exceeded in transit (caller keeps going)
**	-1 on ICMP port unreachable (caller is done)
**	>= 0 return value is some other ICMP unreachable code
*/

int                     recv_v6(int seq, struct timeval *tv)
{
	int					hlen2;
	unsigned int		icmp6len;
	int					ret;
	ssize_t				n;
	socklen_t			len;
	struct ip6_hdr		*hip6;
	struct icmp6_hdr	*icmp6;
	struct udphdr		*udp;

    /*
    ** Default value
    */

    gotalarm = 0;

    /*
    ** Deliver signal every 3 seconds
    */

    alarm(3);

    /*
    ** Infinity
    */

    while (42)
    {

        /*
        ** Check if alarm expired
        */

		if (gotalarm)
            return (-3);

        /*
        ** Set len to sock{} len
        */

        len = g_global->pr->salen;
        
        /*
        ** recieve message from destination host
        */
        
		n = recvfrom(g_global->recvfd, g_global->recvbuf, sizeof(g_global->recvbuf), 0, g_global->pr->sarecv, &len);
        if (n < 0)
        {

            /*
            ** Only continue if the error was of type EINTR
            */

			if (errno == EINTR)
				continue;
			else
                ft_fatal_error("recvfrom error");

		}

        /*
        ** ICMP header
        */

        icmp6 = (struct icmp6_hdr *) g_global->recvbuf;

        /*
        ** Check if there is enough to look at ICMP header
        */

		if ((icmp6len = n) < 8)
			continue ;
    
        /*
        **
        */

        if (icmp6->icmp6_type == ICMP6_TIME_EXCEEDED && icmp6->icmp6_code == ICMP6_TIME_EXCEED_TRANSIT)
        {

            /*
            ** Check if there is enough data to look at inner header
            */
        
			if (icmp6len < 8 + sizeof(struct ip6_hdr) + 4)
				continue ;

            /*
            ** ip6 header
            */

            hip6 = (struct ip6_hdr *) (g_global->recvbuf + 8);

            /*
            ** Size of header
            */

            hlen2 = sizeof(struct ip6_hdr);

            /*
            ** udp header
            */

            udp = (struct udphdr *) (g_global->recvbuf + 8 + hlen2);

            /*
            ** Check if we hit an intermediate router
            */
    
			if (hip6->ip6_nxt == IPPROTO_UDP && udp->uh_sport == htons(g_global->sport) && udp->uh_dport == htons(g_global->dport + seq))
				ret = -2;
            break;

        }
        else if (icmp6->icmp6_type == ICMP6_DST_UNREACH)
        {

            /*
            ** Check if enough data to look at inner header
            */

			if (icmp6len < 8 + sizeof(struct ip6_hdr) + 4)
				continue ;

            /*
            ** ip6 header
            */

            hip6 = (struct ip6_hdr *) (g_global->recvbuf + 8);
            
            /*
            ** ip6 header size
            */

            hlen2 = sizeof(struct ip6_hdr);
            
            /*
            ** UDP header
            */

			udp = (struct udphdr *) (g_global->recvbuf + 8 + hlen2);
            if (hip6->ip6_nxt == IPPROTO_UDP && udp->uh_sport == htons(g_global->sport) && udp->uh_dport == htons(g_global->dport + seq))
            {

                /*
                ** Check if we reached destination
                */

				if (icmp6->icmp6_code == ICMP6_DST_UNREACH_NOPORT)
					ret = -1;
				else
					ret = icmp6->icmp6_code;
                break;

			}
        }
        else if (g_global->env->verbose)
        {

            /*
            **
            */

			printf(" (from %s: type = %d, code = %d)\n", ft_sock_ntop_host(g_global->pr->sarecv, g_global->pr->salen), icmp6->icmp6_type, icmp6->icmp6_code);
        
        }
        
        /*
        ** Some other ICMP error, recvfrom() again
        */
    
    }

    /*
    ** DOnt leave alarm running
    */

    alarm(0);
    
    /*
    ** get time of packet arrival
    */

    ft_gettimeofday(tv, NULL);

    /*
    ** return
    */

	return (ret);
}