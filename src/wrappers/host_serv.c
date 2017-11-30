#include <traceroute.h>

/*
** Using a hostname or IP address string ft_host_serv return
** addrinfo structure containing the protocol family, either AF_INET or AF_INET6
** That is if the hostname is valid
*/

struct addrinfo     *ft_host_serv(const char *host, const char *serv, int family, int socktype)
{
	int             n;

	/*
	** The hints argument specifies criteria for selecting the
	** socket address structures returned in the list pointed to by res
	*/

	struct addrinfo hints;

	/*
	** Each network address that matches node and service, subject to any restrictions
	** imposed by hints is returned with a pointer to the start of the list in res
	*/

	struct addrinfo *res;

	/*
	** Clear hints
	*/

	bzero (&hints, sizeof (struct addrinfo));

	/*
	** After a successful name lookup, return the canonical name of the node corresponding
	** to the addrinfo structure value passed back (res)
	*/

	hints.ai_flags = AI_CANONNAME;

	/*
	** AF_UNSPEC, AF_INET, AF_INET6, etc.
	*/

	hints.ai_family = family;

	/*
	** 0, SOCK_STREAM, SOCK_DGRAM, etc.
	*/

	hints.ai_socktype = socktype;

	/*
	** get host name and service
	*/

	if ((n = getaddrinfo(host, serv, &hints, &res)) != 0)
		ft_fatal_error("failed to resolve dns");

	/*
	** return pointer to first on linked list
	*/

	return (res);
}