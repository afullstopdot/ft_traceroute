#include <traceroute.h>

/*
** Check for -v verbose arg, set to TRUE if passed
*/

static int          get_verbose(char **argv)
{

    int             count;

    count = 1;
    while (argv[count])
    {

        if (ft_strequ(argv[count], A_VERBOSE))
            return (TRUE);
        count++;

    }
    return (FALSE);

}

/*
** Check for -m ttl arg, set maximum ttl if passed
*/

static int          get_ttl(char **argv, int argc)
{

    int             count;

    count = 1;
    while (argv[count])
    {

        if (ft_strequ(argv[count], A_TTL))
        {

            /*
            ** if -m specified, argc should be greated than 2
            */

            if (!(argc > 3))
                dump_usage();

            if (argv[count + 1])
                return (ft_atoi(argv[count + 1]));

        }
        count++;

    }
    return (30);

}

/*
** get ttl start
*/

static int          get_ttl_start(char **argv, int argc)
{

    int             count;

    count = 1;
    while (argv[count])
    {

        if (ft_strequ(argv[count], A_TTL_START))
        {

            /*
            ** if -f specified, argc should be greated than 2
            */

            if (!(argc > 3))
                dump_usage();

            if (argv[count + 1])
                return (ft_atoi(argv[count + 1]));

        }
        count++;

    }
    return (1);

}

/*
** get number of probes on each ttl setting
*/

static int          get_nprobes(char **argv, int argc)
{

    int             count;

    count = 1;
    while (argv[count])
    {

        if (ft_strequ(argv[count], A_NPROBES))
        {

            /*
            ** if -q specified, argc should be greated than 2
            */

            if (!(argc > 3))
                dump_usage();

            if (argv[count + 1])
                return (ft_atoi(argv[count + 1]));

        }
        count++;

    }
    return (3);

}

/*
** get whether or not to map IP Addresses when displaying
*/

static int          get_mapip(char **argv)
{

    int             count;

    count = 1;
    while (argv[count])
    {

        if (ft_strequ(argv[count], A_MAPIP))
            return (FALSE);
        count++;

    }
    return (TRUE);

}

/*
** Check if -h help arg, dump usage and exit
*/

static  int         get_help(char **argv)
{

    int             count;
    
        count = 1;
        while (argv[count])
        {
    
            if (ft_strequ(argv[count], A_HELP))
            {
                dump_usage();
            }
            count++;
    
        }

        return (FALSE);    

}

/*
** Get hostname
*/

static  char        *get_host(char **argv, int argc)
{

    if (argv[argc - 1])
    {

        if (!ft_strchr(argv[argc - 1], '-'))
        {

            return (ft_strdup(argv[argc - 1]));

        }

    }
    return (NULL);    

}

/*
** Initialize ping environment
*/

int                 init_env(int argc, char **argv, t_env *env)
{

    unsigned int    verbose;
    unsigned int    help;
    unsigned int    ttl;
    unsigned int    ttl_start;
    unsigned int    nprobes;
    unsigned int    map_ip;
    char            *host;

    /*
    ** Traceroute requires hostname
    */

    if (argc < 2)
        return (FALSE);

    /*
    ** Make sure if args is greater than 2, that arg 1 is - prefixed
    */

    if (argc > 2)
    {
        if (!ft_strchr(argv[1], '-'))
            dump_usage();
    }

    /*
    ** If verbose dump ICMP_TIME_EXCEEDED code and type
    */

    verbose = get_verbose(argv);

    /*
    ** Dump usage
    */

    help = get_help(argv);

    /*
    ** Set number of hops, default 30
    */

    ttl = get_ttl(argv, argc);

    /*
    ** Set start of hops, default 1
    */

    ttl_start = get_ttl_start(argv, argc);

    /*
    ** Set number of probes for each TTL setting, default 30
    */

    nprobes = get_nprobes(argv, argc);

    /*
    ** Map IP Address for displaying, defaut TRUE
    */

    map_ip = get_mapip(argv);

    /*
    ** Get hostname
    */

    if (!(host = get_host(argv, argc)))
        return (FALSE);

    /*
    ** Set env to default
    */

    env->verbose = verbose;
    env->help = help;
    env->ttl = ttl;
    env->ttl_start = ttl_start;
    env->map_ip = map_ip;
    env->host = host;

    /*
    ** malloc global
    */

    if (!(g_global = (t_global *)malloc(sizeof(t_global))))
        ft_fatal_error("failed to malloc global var");

    /*
    ** Set global defaults
    */

    g_global->datalen = sizeof(t_rec);

    /*
    ** Max TTL / Hops
    */

    g_global->max_ttl = ttl;

    /*
    ** Number of probes
    */

    g_global->nprobes = nprobes;

    /*
    ** Destination port (unlikely value because we dont want the destination port to process the udp probes)
    */

    g_global->dport = 32768 + 666;

    /*
    ** Update global env
    */

    g_global->env = env;

    /*
    ** If we got this far, everything worked out
    */

    return (TRUE);

}