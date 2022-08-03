

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

function exec_test()
{
	TEST1=$(./minishell -c "$@" 2>&1)
	ES_1=$?
	TEST2=$(echo $@ "; exit" | bash )
	ES_2=$?
	if [ "$TEST1" == "$TEST2" ] && [ "$ES_1" == "$ES_2" ]; then
		printf " $BOLDGREEN%s$RESET" "✓ "
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

# ECHO TESTS
exec_test 'echo test tout'
exec_test 'echo test      tout'
exec_test 'echo -n test tout'
exec_test 'echo -n -n -n test tout'
exec_test 'echo'
exec_test 'echo echo'
exec_test 'eCho '
exec_test 'eChO'
exec_test 'eCHO'
exec_test 'ECHO'
exec_test 'echo rhobebou'
exec_test 'echo stop barking'
exec_test 'echo "bonjour"'
exec_test 'echo bonjour'
exec_test 'echo 'bonjour''
exec_test 'echo -n bonjour'
exec_test 'echo -nn bonjour'
exec_test 'echo -n -n -n bonjour'
exec_test 'echo -n -n -n bonjour'
exec_test 'echo "-n" bonjour'
exec_test 'echo -n"-n" bonjour'
exec_test 'echo "-nnnn" bonjour'
exec_test 'echo "-n -n -n"-n bonjour'
exec_test 'echo "-n '-n'" bonjour'
exec_test 'echo ~'
exec_test 'echo "~"'
exec_test 'echo '~''
exec_test 'echo ~123'
exec_test 'echo 123~'
exec_test 'echo ~/123'
exec_test 'echo ~/123/456'
exec_test 'echo $USER'
exec_test 'echo "$USER"'
exec_test 'echo "'$USER'"'
exec_test 'echo " '$USER' "'
exec_test 'echo text"$USER"'
#exec_test 'echo text"'$USER'" ' $USER '' #flashea
exec_test 'echo "text"   "$USER"    "$USER"' 
#exec_test 'echo '              $USER          '' #flashea
exec_test 'echo               text "$USER"            "$USER"text'
exec_test 'echo ''''''''''$USER'''''''''''
exec_test 'echo """"""""$USER""""""""'
#exec_test 'echo $USER'$USER'text oui oui     oui  oui $USER oui      $USER ''' #funciona igual al bash
exec_test 'echo $USER '' $USER $USER '' $USER '' $USER -n $USER'
#exec_test 'echo ' \' ' \' #dan bien
#exec_test 'echo '\" ' " \"\""' #dan bien
exec_test 'echo "$USER""$USER""$USER"'
exec_test 'echo '$USER' "$USER" "text text"'
exec_test 'echo '$USER''
exec_test 'echo "$USER""Users/$USER/file""'$USER'"'$USER''
exec_test 'echo "$USER$USER$USER"'
exec_test 'echo '$USER'"$USER"'$USER''
exec_test 'echo '"$USER"''$USER'"""$USER"'
#exec_test 'echo " $USER  "'$PWD'' # funciona bien en la linea
#exec_test 'echo " $USER  \$ "'$PWD'' # funciona bien en la linea
exec_test 'echo $USER=4'
exec_test 'echo $USER=thallard'
exec_test 'echo $USER'
exec_test 'echo $?'
exec_test 'echo $USER213'
exec_test 'echo $USER$12USER$USER=4$USER12'
exec_test 'echo $USER $123456789USER $USER123456789'
exec_test 'echo $USER $9999USER $8888USER $7777USER'
exec_test 'echo $USER $USER9999 $USER8888 $USER7777'
exec_test 'echo $USER $USER9999 $USER8888 $USER7777 "$USER"'
exec_test 'echo "$USER=12$USER"'
exec_test 'echo "$9USER" "'$USER=12$SOMETHING'"'
exec_test 'echo $PWD/file'
exec_test 'echo "$PWD/file"'
exec_test 'echo "text" "text$USER" ... "$USER"'
exec_test 'echo $PWD'
exec_test 'echo $?HELLO'
exec_test 'echo "hola" $?a'


