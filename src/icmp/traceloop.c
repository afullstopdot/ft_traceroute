#include <traceroute.h>

/*
** Main processing loop
*/

void                traceloop(void)
{

    int             seq;
    int             code;
    int             done;
    double          rtt;
    t_rec           *rec;
    struct timeval  tvrecv;

    /*
    ** Silence compiler
    */

    rec = NULL;

    /*
    ** Check if SU
    */

    ft_set_superuser();

    /*
    ** Raw socket on which we read all returned ICMP messages
    */

    g_global->recvfd = ft_socket(g_global->pr->sasend->sa_family, SOCK_RAW, g_global->pr->icmpproto);

    /*
    ** Reset our effective user ID
    */

    setuid(getuid());

    /*
    ** If we are tracing a route to an IPv6 address and verbose is on, we install a filter
    ** that blocks all ICMP message types except the ones we expect to reduce # of packets recieved on the socket
    */

    if (g_global->pr->sasend->sa_family == AF_INET6 && g_global->env->verbose == 0)
    {

        /*
        ** icmp filter {}
        */

        struct icmp6_filter myfilt;

        /*
        ** Block all ICMP messages
        */

        ICMP6_FILTER_SETBLOCKALL(&myfilt);

        /*
        ** Allow Time exceeded (TTL dropped)
        */

        ICMP6_FILTER_SETPASS(ICMP6_TIME_EXCEEDED, &myfilt);

        /*
        ** Allowed Destination Unreachable (we have hit the end)
        */

        ICMP6_FILTER_SETPASS(ICMP6_DST_UNREACH, &myfilt);

        /*
        ** Apply socket options to our Raw socket (icmp sock)
        */

        setsockopt(g_global->recvfd, IPPROTO_IPV6, ICMP6_FILTER, &myfilt, sizeof (myfilt));

    }

    /*
    ** Set the socket of the destination where we send our UDP datagrams
    */

    g_global->sendfd = ft_socket(g_global->pr->sasend->sa_family, SOCK_DGRAM, 0);

    /*
    ** Set the protocol
    */

    g_global->pr->sabind->sa_family = g_global->pr->sasend->sa_family;

    /*
    ** Our source UDP port #
    ** We achieve a unique port number by taking the 16 least significant bits
    ** of our programs PID and setting the most significant of them to 1.
    ** This port number is automatically entered into the UDP header of each datagram
    */

    g_global->sport = (getpid() & 0xffff) | 0x8000;

    /*
    ** Set the socket options
    */

    sock_set_port(g_global->pr->sabind, g_global->pr->salen, htons(g_global->sport));

    /*
    ** We bind the source port to the UDP socket that is used for sending.
    ** We do this to determine if a recieved ICMP message was generated in response
    ** to one of our datagrams, or in response to a datagram sent by another copy
    ** of the program. We use the source port in the UDP header to identify the
    ** sending process because the returned ICMP message is required to include
    ** the UDP header from the datagram that caused the ICMP error
    */

    ft_bind(g_global->sendfd, g_global->pr->sabind, g_global->pr->salen);

    /*
    ** We send a UDP datagram, we wait 3 seconds for an ICMP message ebfore sending
    ** the next probe
    */

    sig_alrm(SIGALRM);

    /*
    **
    */

    seq = 0;

    /*
    **
    */

    done = 0;

    /*
    ** Start the TTL or hop limit at 1
    */

    for (g_global->ttl = g_global->env->ttl_start; g_global->ttl <= g_global->max_ttl && done == 0; g_global->ttl++)
    {

        /*
        ** Set the socket options for the UDP socket we are sending the datagrams to
        */

        setsockopt(g_global->sendfd, g_global->pr->ttllevel, g_global->pr->ttloptname, &g_global->ttl, sizeof(int));

        /*
        ** Initialized the socket address {} to 0. The structure will be compared to the socket address structure returned
        ** by recvfrom when the ICMP message is read, and if the two structures are different, the IP address
        ** from the new structure will be printed. Using this technique, the IP address corresponding to the first
        ** probe for each TTL is printed, and should the IP address change for a given value of the TTL
        ** (say a route changes while we are running the program), the new IP address will be printed
        */

        bzero(g_global->pr->salast, g_global->pr->salen);

        /*
        ** Dump the current hop
        */

        printf("%2d ", g_global->ttl);

        /*
        ** Flush stdout
        */

        fflush(stdout);

        /*
        ** Send 3 probes (UDP datagrams) to the destination
        */

        for (g_global->probe = 0; g_global->probe < g_global->nprobes; g_global->probe++)
        {

            /*
            ** UDP data to be sent with the datagram (buff)
            */

            rec = (t_rec *) g_global->sendbuf;

            /*
            ** The sequence
            */

            rec->rec_seq = ++seq;

            /*
            ** The hop
            */

            rec->rec_ttl = g_global->ttl;

            /*
            ** Andd the time the UDP datagram was sent
            */

            ft_gettimeofday(&rec->rec_tv, NULL);

            /*
            ** Each time a probe is sent, the destination port in the sasend socket address {}
            ** us changed by calling our sock_set_port function. The reason for changing the port
            ** for each probe is that when we reach the final destination, all three probes are
            ** sent to a diff port, and hopefully at least one of the ports is not in use
            */

            sock_set_port(g_global->pr->sasend, g_global->pr->salen, htons(g_global->dport + seq));
            
            /*
            ** Send the UDP datagram
            */

            ft_sendto(g_global->sendfd, g_global->sendbuf, g_global->datalen, 0, g_global->pr->sasend, g_global->pr->salen);

            /*
            ** Read the ICMP message. recv (either IPv4/6 will read and process the returned ICMP messages)
            ** If recv returns -3 that means the probe has timedout, -2 if the ICMP time exceeded error is recv
            ** or -1 if and ICMP port unreachable is recieved or the non-negative code if some other ICMP code
            ** was recieved
            */

            if ((code = (*g_global->pr->recv) (seq, &tvrecv)) == -3)
                printf(" *");
            else
            {

                /*
                ** hostname of the node sending the ICMP message
                */

                char    str[NI_MAXHOST];

                /*
                ** Compare the sock addr, only print the ip addr if different
                */

                if (sock_cmp_addr (g_global->pr->sarecv, g_global->pr->salast, g_global->pr->salen) != 0)
                {

                    /*
                    ** Get the nameinfo of the ip address, so we can print the hostname and ip addr
                    */

                    if (getnameinfo(g_global->pr->sarecv, g_global->pr->salen, str, sizeof(str), NULL, 0, 0) == 0)
                    {

                        /*
                        ** Check if we should dump the mapped IP
                        */

                        if (g_global->env->map_ip)
                            printf(" %s%s%s (%s%s%s)", C_GRN, str, C_RST, C_YEL, ft_sock_ntop_host(g_global->pr->sarecv, g_global->pr->salen), C_RST);
                        else
                            printf(" %s%s%s", C_YEL, ft_sock_ntop_host(g_global->pr->sarecv, g_global->pr->salen), C_RST);
                        
                    }
                    else
                        printf(" %s", ft_sock_ntop_host(g_global->pr->sarecv, g_global->pr->salen));

                    /*
                    **
                    */

                    ft_memcpy(g_global->pr->salast, g_global->pr->sarecv, g_global->pr->salen);

                }

                /*
                ** Calculate the RTT
                */

                ft_tv_subtract(&tvrecv, &rec->rec_tv);

                /*
                ** RTT in milliseconds
                */

                rtt = tvrecv.tv_sec * 1000.0 + tvrecv.tv_usec / 1000.0;

                /*
                ** Print with precision of 3
                */

                printf(" %.3f ms", rtt);

                /*
                ** Port unreachable at destination
                */

                if (code == -1)
                    done++;
                else if (code >= 0)
                    printf(" (ICMP %s)", (*g_global->pr->icmpcode) (code));

            }

            /*
            ** flush stdout
            */

            fflush(stdout);

        }

        /*
        ** Newline for each hop
        */

        printf("\n");

    }

}