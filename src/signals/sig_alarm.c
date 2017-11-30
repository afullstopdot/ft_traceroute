#include <traceroute.h>

int gotalarm;

/*
** SIGALRM signal handler
*/

void    sig_alrm (int signo)
{

    /*
    ** silence compiler
    */

    if (signo != SIGALRM)
        return ;

    /*
    ** set flag to note that alarm occurred
    */

    gotalarm = 1;

    /*
    ** Interrupt the recvfrom
    */

    return ;

}