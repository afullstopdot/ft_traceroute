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

    rec = NULL;

    /*
    **
    */

    ft_set_superuser();

    /*
    **
    */

    g_global->recvfd = socket(g_global->pr->sasend->sa_family, SOCK_RAW, g_global->pr->icmpproto);

    /*
    **
    */

    setuid(getuid());

    /*
    **
    */

    if (g_global->pr->sasend->sa_family == AF_INET6 && g_global->env->verbose == 0)
    {

        /*
        **
        */

        struct icmp6_filter myfilt;

        /*
        **
        */

        ICMP6_FILTER_SETBLOCKALL (&myfilt);

        /*
        **
        */

        ICMP6_FILTER_SETPASS (ICMP6_TIME_EXCEEDED, &myfilt);

        /*
        **
        */

        ICMP6_FILTER_SETPASS (ICMP6_DST_UNREACH, &myfilt);

        /*
        **
        */

        setsockopt (g_global->recvfd, IPPROTO_IPV6, ICMP6_FILTER, &myfilt, sizeof (myfilt));

    }

    /*
    **
    */

    g_global->sendfd = socket(g_global->pr->sasend->sa_family, SOCK_DGRAM, 0);

    /*
    **
    */

    g_global->pr->sabind->sa_family = g_global->pr->sasend->sa_family;

    /*
    **
    */

    g_global->sport = (getpid() & 0xffff) | 0x800;

    /*
    **
    */

    sock_set_port(g_global->pr->sabind, g_global->pr->salen, htons(g_global->sport));

    /*
    **
    */

    ft_bind(g_global->sendfd, g_global->pr->sabind, g_global->pr->salen);

    /*
    **
    */

    sig_alrm(SIGALRM);

    /*
    **
    */

    seq = 0;
    done = 0;

    /*
    **
    */

    for (g_global->ttl = 1; g_global->ttl <= g_global->max_ttl && done == 0; g_global->ttl++)
    {

        /*
        **
        */

        setsockopt(g_global->sendfd, g_global->pr->ttllevel, g_global->pr->ttloptname, &g_global->ttl, sizeof(int));

        /*
        **
        */

        bzero(g_global->pr->salast, g_global->pr->salen);

        /*
        **
        */

        printf("%2d ", g_global->ttl);

        /*
        **
        */

        fflush(stdout);

        /*
        **
        */

        for (g_global->probe = 0; g_global->probe < g_global->nprobes; g_global->probe++)
        {

            /*
            **
            */

            g_global->rec = (t_rec *) g_global->sendbuf;

            /*
            **
            */

            g_global->rec->rec_seq = ++seq;

            /*
            **
            */

            g_global->rec->rec_ttl = g_global->ttl;

            /*
            **
            */

            ft_gettimeofday(&g_global->rec->rec_tv, NULL);

            /*
            **
            */

            ft_sendto(g_global->sendfd, g_global->sendbuf, g_global->datalen, 0, g_global->pr->sasend, g_global->pr->salen);

            /*
            **
            */

            if ((code = (*g_global->pr->recv) (seq, &tvrecv)) == -3)
                printf(" *");
            else
            {

                /*
                **
                */

                char    str[NI_MAXHOST];

                /*
                **
                */

                if (sock_cmp_addr (g_global->pr->sarecv, g_global->pr->salast, g_global->pr->salen) != 0)
                {

                    /*
                    **
                    */

                    if (getnameinfo(g_global->pr->sarecv, g_global->pr->salen, str, sizeof(str), NULL, 0, 0) == 0)
                        printf(" %s (%s)", str, ft_sock_ntop_host(g_global->pr->sarecv, g_global->pr->salen));
                    else
                        printf(" %s", ft_sock_ntop_host(g_global->pr->sarecv, g_global->pr->salen));

                    /*
                    **
                    */

                    ft_memcpy(g_global->pr->salast, g_global->pr->sarecv, g_global->pr->salen);

                }

                /*
                **
                */

                ft_tv_subtract(&tvrecv, &rec->rec_tv);

                /*
                **
                */

                rtt = tvrecv.tv_sec * 1000.0 + tvrecv.tv_usec / 1000.0;

                /*
                **
                */

                printf(" %.3f ms", rtt);

                /*
                **
                */

                if (code == -1) /* port unreachable; at destination */
                    done++;
                else if (code >= 0)
                    printf(" (ICMP %s)", (*g_global->pr->icmpcode) (code));

            }

            /*
            **
            */

            fflush(stdout);

        }

        /*
        **
        */

        printf("\n");

    }

}