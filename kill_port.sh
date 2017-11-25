# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    close_port.sh                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amarquez <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/25 18:06:36 by amarquez          #+#    #+#              #
#    Updated: 2017/07/25 18:50:15 by amarquez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## target name

target='server'

## ansi colors

RED='\033[0;31m'
YELLOW='\033[0;33m'
GREEN='\033[0;32m'
NC='\033[0m'

## ask for port number

printf "${YELLOW}Enter port number to be close: ${NC}";

## assign port number

read -p "" port

## check if valid port number

if [ "$port" -eq "$port" ] 2>/dev/null; then

	# get output from lsof ( including PID )

	printf "${YELLOW}Looking for port :[ ${port} ] PID${NC}\n"
	pid="$(lsof -i :$port | grep $target | cut -d ' ' -f 3)"

	# check if pid is a num

	if [ "$pid" -eq "$pid" ] 2>/dev/null; then

		## kill pid

		printf "${GREEN}PID found, killing process: ${NC}"
		kill $pid

	else

		printf "${RED}Unable to find PID, bye${NC}\n"

	fi

else

	# not a valid port number

	printf "${RED}Not a valid port number, bye\n${NC}";

fi
