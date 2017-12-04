#include <traceroute.h>

/*
** dump the correct usage
*/

void    dump_usage(void)
{

	/*
	** Dump the program usage
	*/

    printf("usage: traceroute [ -m <maxttl> -f <startttl> -q <nprobes> -v (verbose) -n (IP Address != Map) -h (help) ] <hostname>\n");

    /*
    ** Exit
    */

	exit(EXIT_SUCCESS);
}