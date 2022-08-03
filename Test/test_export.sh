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

# EXPORT TESTS

# printf "\n/--------------\n"
# exec_test 'export L=15'
# printf "\--------------\n"
# printf "\n/--------------\n"
# exec_test 'export A=''\n'
# printf "\--------------\n"
# printf "\n/--------------\n"
# exec_test 'export 'A'=''\n'
# printf "\--------------\n"
# printf "\n/--------------\n"
# exec_test 'export 'A'=\'
# printf "\--------------\n"
# printf "\n/--------------\n"
# exec_test 'export 'A'=$\n'
# printf "\--------------\n"
# printf "\n/--------------\n"
# exec_test 'export 'A'='\t'\n'
# printf "\--------------\n"
# printf "\n/--------------\n"
# exec_test 'export 'A'='a'\n'
# printf "\--------------\n"
# printf "\n/--------------\n"
# exec_test 'export A=a B=b C=c'
# printf "\--------------\n"
# printf "\n/--------------\n"
# exec_test 'export A=a B=b C=c D=d E=e F=f G=g H=h I=i J=j K=k L=l M=m N=n O=o P=p Q=q R=r S=s T=t U=u V=v W=w X=x Y=y Z=z'
# printf "\--------------\n"
# printf "\n/--------------\n"
# exec_test 'export BONJOURJESUIS=a'
# printf "\--------------\n"
# printf "\n/--------------\n"
# exec_test 'export bonjourjesuis=a'
# printf "\--------------\n"
# printf "\n/--------------\n"
# exec_test 'export bO_nJq123o__1ju_je3234sui__a=a'
# printf "\--------------\n"
# printf "\n/--------------\n"
# exec_test 'export a0123456789=a'
# printf "\--------------\n"
# printf "\n/--------------\n"
# exec_test 'export abcdefghijklmnopqrstuvwxyz=a'
# printf "\--------------\n"
# printf "\n/--------------\n"
# exec_test 'export __________________________=a'
# printf "\--------------\n"
# printf "\n/--------------\n"
# exec_test 'export _bonjour_=a'
# printf "\--------------\n"
# printf "\n/--------------\n"
# exec_test 'export _=a'
# printf "\--------------\n"
printf "\n/--------------\n"
exec_test 'export 1=a'
printf "\--------------\n"
printf "\n/--------------\n"
exec_test 'export BONJOURJESUIS =a\n'
printf "\--------------\n"
printf "\n/--------------\n"
exec_test 'export BONJOURJESUIS= a\n'
printf "\--------------\n"
printf "\n/--------------\n"
exec_test 'export BONJOUR\\JESUIS=a\n'
printf "\--------------\n"
printf "\n/--------------\n"
exec_test 'export BONJOUR$JESUIS=a\n'
printf "\--------------\n"
printf "\n/--------------\n"
exec_test 'export BONJOUR\|JESUIS=a\n'
printf "\--------------\n"
printf "\n/--------------\n"
exec_test 'export BONJOUR\0JESUIS=a\n'
printf "\--------------\n"
printf "\n/--------------\n"
exec_test 'export BONJOUR\0JESUIS=a\n'
printf "\--------------\n"
printf "\n/--------------\n"
exec_test 'export \B\O\N\ \ \ \ \ \ \ JOURJESUIS=a\n'
printf "\--------------\n"
printf "\n/--------------\n"
exec_test 'export \B\O\N\ \ \ \ \ \ \ JOURJESUIS=a\n'
printf "\--------------\n"
printf "\n/--------------\n"
exec_test 'export A=\B\O\N\ \ \ \ \ \ \ JOURJESUIS'
printf "\--------------\n"
printf "\n/--------------\n"
exec_test 'export A='bonjour je suis charles''
printf "\--------------\n"
printf "\n/--------------\n"
exec_test 'export A="bonjour je suis charles"; echo $A\n'
printf "\--------------\n"
printf "\n/--------------\n"
exec_test 'export A=====a'
printf "\--------------\n"
printf "\n/--------------\n"
exec_test 'export A=a=a=a=a=a'
printf "\--------------\n"
printf "\n/--------------\n"
exec_test 'export A B C'
printf "\--------------\n"
printf "\n/--------------\n"
exec_test 'export A 'asdf ' B ' asdf asdf asd f' ' asdf ' '' 'asdf ' C'
printf "\--------------\n"
printf "\n/--------------\n"
exec_test 'export A B C'
printf "\--------------\n"
printf "\n/--------------\n"
exec_test 'export 'AH@'=nop\n'
printf "\--------------\n"
printf "\n/--------------\n"
exec_test 'export "AH"=nop\n'
printf "\--------------\n"
printf "\n/--------------\n"
exec_test 'export 'AH&'=nop\n'
printf "\--------------\n"

echo

