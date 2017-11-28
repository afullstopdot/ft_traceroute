#include <traceroute.h>

/*
** Set global to NULL 
*/

t_global			*g_global = NULL;

/*
** Start of program
*/

int                 main(int argc, char **argv)
{

	/*
	** Program environment
	*/

    t_env			*env;

    /*
    ** IPv4 proto
    */
    
    t_proto         proto_v4;

    /*
    ** IPv6 proto
    */

    t_proto         proto_v6;

    /*
    ** destination addrinfo{}
    */

    struct addrinfo *ai;

    /*
    ** destination host
    */

    char            *h;

    /*
    ** Allocate some memory for 
    */

    if (!(env = (t_env *)malloc(sizeof(t_env))) || !(g_global = (t_global *)malloc(sizeof(t_global))))
    	ft_fatal_error("failed to dynamically allocate memory");
    
    /*
    ** initialize server options
    */
    
    if (init_env(argc, argv, env))
    {

        /*
        ** Initialize proto_ipv4
        */

        ft_init_proto_ipv4(&proto_v4);

        /*
        ** Initiliaze proto_ipv6
        */

        ft_init_proto_ipv6(&proto_v6);

        /*
        ** Set pid
        */

        g_global->pid = getpid();

        /*
        **
        */

        signal(SIGALRM, sig_alrm);

        /*
        **
        */

        ai = ft_host_serv(g_global->env->host, NULL, 0, 0);

        /*
        **
        */

        h = ft_sock_ntop_host(ai->ai_addr, ai->ai_addrlen);

        /*
        **
        */

        printf("traceroute to %s (%s) : %d hops max, %d data bytes\n",
            ai->ai_canonname ? ai->ai_canonname : h, h, g_global->max_ttl, g_global->datalen);

        /*
        ** Initialize according to protocol
        */

        if (ai->ai_family == AF_INET)
        {

            g_global->pr = &proto_v4;

        }
        else if (ai->ai_family == AF_INET6)
        {

            g_global->pr = &proto_v6;

            /*
            ** Check if the destination IPv6 is V4Mapped
            */

            if (IN6_IS_ADDR_V4MAPPED(&(((struct sockaddr_in6 *) ai->ai_addr)->sin6_addr)))
                ft_fatal_error("cannot traceroute IPv4-mapped IPv6 address");

        }
        else
            ft_fatal_error("unknown address family");

        /*
        ** Set destination address
        */

        g_global->pr->sasend = ai->ai_addr;

        /*
        **
        */

        g_global->pr->sarecv = ft_calloc(1, ai->ai_addrlen);

        /*
        **
        */

        g_global->pr->salast = ft_calloc(1, ai->ai_addrlen);

        /*
        **
        */

        g_global->pr->sabind = ft_calloc(1, ai->ai_addrlen);

        /*
        **
        */

        g_global->pr->salen = ai->ai_addrlen;

        /*
        **
        */

        traceloop();

    }
    else
        dump_usage();
    return (0);
}
