#include <traceroute.h>

/*
** Raw sockets allow sending of IP datagrams as a user process
** but to send said datagrams, a raw socket must be created
** with superuser permissions
**
** If SU set, function will return to caller
** If fail to set SU, program will exit
*/

void        ft_set_superuser(void)
{

    uid_t   uid;

    /*
    ** Get UID
    */

    uid = getuid();

    /*
    ** Check that the UID is root
    */

    if (uid == ROOT_UID)
    {

        /*
        ** Set UID
        */

        if (setuid(uid) < 0)
        {

            /*
            ** an error has occured
            */

            printf("ft_ping:%s unable to setuid to root\n%s", C_RED, C_RST);

        }
        else
            return ;

    }
    else
    {

        /*
        ** Set UID 
        */

        printf("ft_ping:%s program must be run with SU privieges to create raw socket%s\n", C_RED, C_RST);
    
    }
    exit(EXIT_FAILURE);
    
}