# include <traceroute.h>

/*
** get time of the day wrapper
*/

void    ft_gettimeofday(struct timeval *tv, void *foo)
{
	if (gettimeofday(tv, foo) == -1)
		ft_fatal_error("gettimeofday error");
	return ;
}

/*
** calloc wrapper
*/

void *ft_calloc(size_t n, size_t size)
{
	void	*ptr;

	if ((ptr = calloc(n, size)) == NULL)
        ft_fatal_error("calloc error");
	return (ptr);
}

/*
** sendto wrapper
*/

void	ft_sendto(int fd, const void *ptr, size_t nbytes, int flags, const struct sockaddr *sa, socklen_t salen)
{
	if (sendto(fd, ptr, nbytes, flags, sa, salen) != (ssize_t)nbytes)
	{
		
		ft_fatal_error("invalid argument");
	}
	return ;
}

/*
**
*/

void	ft_bind(int fd, const struct sockaddr *sa, socklen_t salen)
{
	if (bind(fd, sa, salen) < 0)
		ft_fatal_error("bind error");
}

/*
**
*/

void	sock_set_port(struct sockaddr *sa, socklen_t salen, int port)
{

	if (!(salen > 0))
		ft_fatal_error("empty sockaddr");

	switch (sa->sa_family) {
		case AF_INET: {
			struct sockaddr_in	*sin = (struct sockaddr_in *) sa;

			sin->sin_port = port;
			return ;
		}
		case AF_INET6: {
			struct sockaddr_in6	*sin6 = (struct sockaddr_in6 *) sa;

			sin6->sin6_port = port;
			return ;
		}
	}

    return ;
}

int sock_cmp_addr(const struct sockaddr *sa1, const struct sockaddr *sa2, socklen_t salen)
{

	if (!(salen > 0))
		ft_fatal_error("empty sockaddr");

	if (sa1->sa_family != sa2->sa_family)
		return(-1);

	switch (sa1->sa_family) {
		case AF_INET: {
			return(memcmp( &((struct sockaddr_in *) sa1)->sin_addr,
						&((struct sockaddr_in *) sa2)->sin_addr,
						sizeof(struct in_addr)));
		}
		case AF_INET6: {
			return(memcmp( &((struct sockaddr_in6 *) sa1)->sin6_addr,
						&((struct sockaddr_in6 *) sa2)->sin6_addr,
						sizeof(struct in6_addr)));
		}
	}
    return (-1);
}

int	ft_socket(int domain, int type, int protocol)
{
	int fd;

	fd = -1;
	if ((fd = socket(domain, type, protocol)) < 0)
		ft_fatal_error("socket error");
	return (fd);
}