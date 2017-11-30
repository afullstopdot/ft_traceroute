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

    verbose = get_verbose(argv);
    help = get_help(argv);
    ttl = get_ttl(argv, argc);

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
    g_global->max_ttl = ttl;
    g_global->nprobes = 3;
    g_global->dport = 32768 + 666;
    g_global->env = env;

    /*
    ** If we got this far, everything worked out
    */

    return (TRUE);

}