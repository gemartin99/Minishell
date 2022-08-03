# MINISHELL-TESTER

RESET="\033[0m"
BLACK="\033[30m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"
CYAN="\033[36m"
WHITE="\033[37m"

BOLDBLACK="\033[1m\033[30m"
BOLDRED="\033[1m\033[31m"
BOLDGREEN="\033[1m\033[32m"
BOLDYELLOW="\033[1m\033[33m"
BOLDBLUE="\033[1m\033[34m"
BOLDMAGENTA="\033[1m\033[35m"
BOLDCYAN="\033[1m\033[36m"
BOLDWHITE="\033[1m\033[37m"

# Compile and set executable rights
make -C ../ > /dev/null
cp ../minishell .
chmod 777 minishell

function rem_d()
{
	FILE=d
	if [ -d "$FILE" ]; then
	    $(chmod 777 d; rm -rf d/)
	fi
}

function exec_test()
{
	rem_d
	printf $GREEN"mini: $RESET"
	TEST1=$(./minishell -c "$@")
	ES_1=$?
	rem_d
	printf $GREEN"\nbash: $RESET"
	TEST2=$(bash -c "$@; exit" 1>&2)
	ES_2=$?
	if [ "$TEST1" == "$TEST2" ] && [ "$ES_1" == "$ES_2" ]; then
		printf " \n$BOLDGREEN%s$RESET" "✓ "
	else
		printf " $BOLDRED%s$RESET" "✗ "
	fi
	printf "$CYAN \"$@\" $RESET"
	if [ "$TEST1" != "$TEST2" ]; then
		echo
		echo
		printf $BOLDRED"Your output : \n%.20s\n$BOLDRED$TEST1\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
		printf $BOLDGREEN"Expected output : \n%.20s\n$BOLDGREEN$TEST2\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
	fi
	if [ "$ES_1" != "$ES_2" ]; then
		echo
		echo
		printf $BOLDRED"Your exit status : $BOLDRED$ES_1$RESET\n"
		printf $BOLDGREEN"Expected exit status : $BOLDGREEN$ES_2$RESET\n"
	fi
	echo
	sleep 0.1
}

printf "$BOLDMAGENTA __  __ _____ _   _ _____  _____ _    _ ______ _      _      \n"
printf "|  \/  |_   _| \ | |_   _|/ ____| |  | |  ____| |    | |     \n"
printf "| \  / | | | |  \| | | | | (___ | |__| | |__  | |    | |     \n"
printf "| |\/| | | | | . \` | | |  \___ \|  __  |  __| | |    | |     \n"
printf "| |  | |_| |_| |\  |_| |_ ____) | |  | | |____| |____| |____ \n"
printf "|_|  |_|_____|_| \_|_____|_____/|_|  |_|______|______|______|\n$RESET"
echo

# CD TESTS
printf "\n/--------------\n"
exec_test 'cd'
printf "\--------------\n"

printf "\n/--------------\n"
exec_test 'cd .'
printf "\--------------\n"

printf "\n/-------------\n"
exec_test 'cd -'
printf "\--------------\n"

printf "\n/--------------\n"
exec_test 'cd ~'
printf "\--------------\n"

printf "\n/--------------\n"
exec_test 'cd $PWD'
printf "\--------------\n"

printf "\n/--------------\n"
exec_test 'cd $PWD hi' 
printf "\--------------\n"

printf "\n/--------------\n"
exec_test 'cd 123123'
printf "\--------------\n"

printf "\n/--------------\n"
exec_test 'cd $OLDPWD'
printf "\--------------\n"

printf "\n/--------------\n"
exec_test 'cd libft'
printf "\--------------\n"

printf "\n/--------------\n"
exec_test 'cd nada'
printf "\--------------\n"

printf "\n/--------------\n"
exec_test 'cd ../..'
printf "\--------------\n"

printf "\n/--------------\n"
exec_test 'cd ../../..'
printf "\--------------\n"

printf "\n/--------------\n"
exec_test 'cd \'' '' '
printf "\--------------\n"

printf "\n/--------------\n"
exec_test 'cd 'd' '
printf "\--------------\n"

printf "\n/--------------\n"
exec_test 'cd /'
printf "\--------------\n"

printf "\n/--------------\n"
exec_test 'cd //'
printf "\--------------\n"

printf "\n/--------------\n"
exec_test 'cd ///'
printf "\--------------\n"

printf "\n/--------------\n"
exec_test 'cd /home'
printf "\--------------\n"

printf "\n/--------------\n"
exec_test 'cd //home'
printf "\--------------\n"

printf "\n/--------------\n"
exec_test 'Cd .'
printf "\--------------\n"

printf "\n/--------------\n"
exec_test 'cD .'
printf "\--------------\n"

echo
