# include <traceroute.h>

/*
** Convert IPv4/IPv6 addresses from binary to text form
*/

char                    *sock_ntop_host(const struct sockaddr *sa, socklen_t salen)
{

    if (!sa)
        ft_fatal_error("sockaddr null");

    /*
    ** for IPv6
    */

    struct sockaddr_in6 *sin6;

    /*
    ** for IPv4
    */

    struct sockaddr_in  *sin;

    /*
    ** Unix domain is the largest size
    */

    static char         str[128];

    /*
    ** Check if family is IPv4
    */

    if (sa->sa_family == AF_INET)
    {

        /*
        ** set sockaddr_in
        */

        sin = (struct sockaddr_in *) sa;

        /*
        ** Convert address to text form
        */

        if (inet_ntop(AF_INET, &sin->sin_addr, str, sizeof(str)) == NULL)
            return (NULL);

        /*
        **
        */

        return (str);

    }
    else if (sa->sa_family == AF_INET6)
    {

        /*
        ** set sockaddr to IPv6 {}
        */

        sin6 = (struct sockaddr_in6 *) sa;

        /*
        ** Convert address to text form
        */

        if (inet_ntop(AF_INET6, &sin6->sin6_addr, str, sizeof(str)) == NULL)
            return(NULL);

        /*
        **
        */

        return (str);

    }
    else
    {

        /*
        ** IPv6
        */

        snprintf(str, sizeof(str), "sock_ntop_host: unknown AF_xxx: %d, len %d", sa->sa_family, salen);

        /*
        ** Return error
        */

        return (str);

	}

    return (NULL);
}

/*
** Wrapper for sock_ntop_host
*/

char                    *ft_sock_ntop_host(const struct sockaddr *sa, socklen_t salen)
{
    char                *ptr;

    /*
    ** If it fails, exit program
    */

	if ((ptr = sock_ntop_host(sa, salen)) == NULL)
        ft_fatal_error("sock_ntop_host error");

    /*
    ** return text form of address
    */

	return (ptr);
}