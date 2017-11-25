#include <traceroute.h>

/*
** dump the correct usage
*/

void    dump_usage(void)
{

	/*
	** Dump the program usage
	*/

    printf("usage: traceroute [ -m <maxttl> -v ] <hostname>\n");

    /*
    ** Exit
    */

	exit(EXIT_SUCCESS);
}