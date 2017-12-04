# ft_traceroute

This project is about recoding the command traceroute, for the opportunity to deepen my knowledge in the network (TCP / IP) by tracking the paths that an IP packet will take between two machines.

## Getting Started

To use the progam for learning or use clone it locally.

### Prerequisites

What things you need to install the software and how to install them

```
gcc or clang compiler
```

### Installing

Installing just requires a clone or download


```
git clone https://github.com/afullstopdot/ft_traceroute.git on terminal or download the zip straight from here.
```

## Compiling the library

For use

### Break down into end to end tests

Compile the library for use, using the Makefile

```
make all
```

Remove the object files

```
make clean
```

Remove the libft library

```
make fclean
```

Remove the library and recompile

```
make re
```

## traceroute usage

```
usage: ./traceroute [ -m <maxttl> -f <startttl> -q <nprobes> -v (verbose) -n (IP Address != Map) -h (help) ] <hostname>\n
```

Where “hostname” is the host you want to traceroute

```
verbose : verbose output
```
```
help : display usage
```
```
maxttl : number of hops to host
```
```
startttl : first ttl to start, defaults to 1
```
```
nprobes : sets the number of probe packets to be sent for each hop
```
```
map ip address : do not map an ip address when displaying info
```

## Authors

* **Andre Marques** - *All* - [afullstopdot](https://github.com/afullstopdot)
* **** - *All* - [afullstopdot](https://github.com/afullstopdot)

## Resources

```
Unix Network Programming Vol 1, 3rd version
```

## Notes

```
ft_traceroute was built with IPv6 support
```

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Disclaimer

This message pertains to the students of 42 and WTC (WeThinkCode_).

Copying this work as is, without understanding and being able to implement your own work defeats the pedagogy and subsequently is cheating.

Goodluck!
