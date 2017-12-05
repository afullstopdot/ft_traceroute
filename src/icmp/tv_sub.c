#include <traceroute.h>

/*
** tv-suvtractfunction, subtracts two timeval structures
** storing the result in the first structure
*/

void    ft_tv_subtract(struct timeval *out, struct timeval *in)
{

    if ((out->tv_usec -= in->tv_usec) < 0)
    {

        --out->tv_sec;
        out->tv_usec += 1000000;

    }
    out->tv_sec -= in->tv_sec;

}