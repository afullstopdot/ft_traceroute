#include <traceroute.h>

int gotalarm;

/*
** SIGALRM signal handler
*/

void    sig_alrm (int signo)
{

    /*
    **
    */

    if (signo != SIGALRM)
        return ;

    /*
    **
    */

    gotalarm = 1; /* set flag to note that alarm occurred */

    /*
    **
    */

    return ; /* and interrupt the recvfrom() */

}