#include <traceroute.h>

/*
** Print a description string corresponding to an ICMP "destination unreachable" error
**
** The IPv4 function is similar, albeit longer,
** as there are more ICMPv4 "destination unreachable" codes
*/

const char      *icmpcode_v4(int code)
{
    static char errbuf[100];

    switch (code)
    {
        case  0:
            return (ft_strdup("network unreachable"));
        case  1:
            return (ft_strdup("host unreachable"));
        case  2:
            return (ft_strdup("protocol unreachable"));
        case  3:
            return (ft_strdup("port unreachable"));
        case  4:
            return (ft_strdup("fragmentation required but DF bit set"));
        case  5:
            return (ft_strdup("source route failed"));
        case  6:
            return (ft_strdup("destination network unknown"));
        case  7:
            return (ft_strdup("destination host unknown"));
        case  8:
            return (ft_strdup("source host isolated (obsolete)"));
        case  9:
            return (ft_strdup("destination network administratively prohibited"));
        case 10:
            return (ft_strdup("destination host administratively prohibited"));
        case 11:
            return (ft_strdup("network unreachable for TOS"));
        case 12:
            return (ft_strdup("host unreachable for TOS"));
        case 13:
            return (ft_strdup("communication administratively prohibited by filtering"));
        case 14:
            return (ft_strdup("host recedence violation"));
        case 15:
            return (ft_strdup("precedence cutoff in effect"));
        default:
            sprintf(errbuf, "[unknown code %d]", code);
            return (errbuf);
	}
}

const char      *icmpcode_v6(int code)
{
    static char errbuf[100];

    switch (code)
    {
        case  ICMP6_DST_UNREACH_NOROUTE:
            return (ft_strdup("no route to host"));
        case  ICMP6_DST_UNREACH_ADMIN:
            return (ft_strdup("administratively prohibited"));
        // case  ICMP6_DST_UNREACH_NOTNEIGHBOR:
        //     return (ft_strdup("not a neighbor"));
        case  ICMP6_DST_UNREACH_ADDR:
            return (ft_strdup("address unreachable"));
        case  ICMP6_DST_UNREACH_NOPORT:
            return (ft_strdup("port unreachable"));
        default:
            sprintf(errbuf, "[unknown code %d]", code);
            return errbuf;
	}
}