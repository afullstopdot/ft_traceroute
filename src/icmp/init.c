#include <traceroute.h>

/*
** Initialize proto struct for IPv4
*/

void	ft_init_proto_ipv4(t_proto *proto_v4)
{

    /*
    ** print a description string corresponding
    ** to an ICMPv4 destination unreachable" error
    */

    proto_v4->icmpcode = icmpcode_v4;

    /*
    ** Read and process ICMPv4 messages
    */

    proto_v4->recv = recv_v4;

    /*
    ** Socket{} for sending
    */

    proto_v4->sasend = NULL;

    /*
    ** Socket{} for recv
    */

    proto_v4->sarecv = NULL;

    /*
    ** Socket{} for recv
    */

    proto_v4->salast = NULL;

    /*
    ** Socket{} for bidning source port
    */

    proto_v4->sabind = NULL;

    /*
    ** length of Socket{}s
    */

    proto_v4->salen = 0;

    /*
    ** ICMP protocol (IPv4)
    */

    proto_v4->icmpproto = IPPROTO_ICMP;

    /*
    ** setsockopt {} level to set TTL
    */

    proto_v4->ttllevel = IPPROTO_IP;

    /*
    ** setsockopt {} name to set TTL
    */

    proto_v4->ttloptname = IP_TTL;

}

/*
** Initialize proto struct for IPv6
*/

void	ft_init_proto_ipv6(t_proto *proto_v6)
{

	/*
    ** print a description string corresponding
    ** to an ICMPv6 destination unreachable" error
    */

    proto_v6->icmpcode = icmpcode_v6;
    
    /*
    ** Read and process ICMPv6 messages
    */

    proto_v6->recv = recv_v6;

    /*
    ** Socket{} for sending
    */

    proto_v6->sasend = NULL;

    /*
    ** Socket{} for recv
    */

    proto_v6->sarecv = NULL;

    /*
    ** Socket{} for recv
    */

    proto_v6->salast = NULL;

    /*
    ** Socket{} for bidning source port
    */

    proto_v6->sabind = NULL;

    /*
    ** length of Socket{}s
    */

    proto_v6->salen = 0;

    /*
    ** ICMP protocol (IPv6)
    */

    proto_v6->icmpproto = IPPROTO_ICMPV6;

    /*
    ** setsockopt {} level to set TTL
    */

    proto_v6->ttllevel = IPPROTO_IPV6;

    /*
    ** setsockopt {} name to set TTL
    */

    proto_v6->ttloptname = IPV6_UNICAST_HOPS;

}