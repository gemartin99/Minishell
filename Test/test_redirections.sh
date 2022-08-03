

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

printf "$BOLDYELLOW \nREDIRECTIONS TEST$RESET\n\n"

# REDIR TESTS
printf "1. 'echo bonjour > test'"
exec_test "echo bonjour > test"
exec_test "cat test"

# printf "2. 'echo > test bonjour'"
# exec_test "echo > test bonjour"
# exec_test "cat test"

# printf "3. '> test echo bonjour'"
# exec_test "> test echo bonjour"
# exec_test "cat test"

# printf "4. 'echo bonjour >> test'"
# exec_test "echo bonjour >> test"
# exec_test "cat test"

# printf "5. 'echo >> test bonjour'"
# exec_test "echo >> test bonjour"
# exec_test "cat test"

# printf "6. '>> test echo bonjour'"
# exec_test ">> test echo bonjour"
# exec_test "cat test"

# printf "7. '[SETUP echo bonjour > test] cat < test'"
# exec_test "echo bonjour > test"
# exec_test "cat < test"

# printf "8. 'echo > test'sticked' bonjour'"
# exec_test "echo > test'sticked' bonjour"
# exec_test "cat teststicked"

# printf "9. '> test'sticked' echo bonjour'"
# exec_test "> test'sticked' echo bonjour"
# exec_test "cat teststicked"

# printf "10. 'echo bonjour >> test'sticked''"
# exec_test "echo bonjour >> test'sticked'"
# exec_test "cat teststicked"

# printf "11. 'echo >> test'sticked' bonjour'"
# exec_test "echo >> test'sticked' bonjour"
# exec_test "cat teststicked"

# printf "12. '>> test'sticked' echo bonjour'"
# exec_test ">> test'sticked' echo bonjour"
# exec_test "cat teststicked"

# printf "13. '[SETUP echo bonjour > test'sticked'] cat < test'sticked' '"
# exec_test "echo bonjour > test'sticked'"
# exec_test "cat < test'sticked'"

# printf "14. '[SETUP echo bonjour > test'sticked'] < test'sticked' cat '"
# exec_test "echo bonjour > test'sticked'"
# exec_test "< test'sticked' cat '"

# printf "15. 'echo > test"sticked" bonjour'"
# exec_test "echo > test"sticked" bonjour"
# exec_test "cat teststicked"

# printf "16. 'echo >> test"sticked" bonjour '"
# exec_test "echo >> test"sticked" bonjour "
# exec_test "cat teststicked"

# printf "17. '>> test"sticked" echo bonjour  '"
# exec_test ">> test"sticked" echo bonjour "
# exec_test "cat test"sticked""

# printf "18. '[SETUP echo bonjour > test"sticked"] < test"sticked" cat'"
# exec_test "echo bonjour > test"sticked""
# exec_test "< test"sticked" cat"

# printf "19. 'echo > test'yo'"sticked" bonjour'"
# exec_test "echo > test'yo'"sticked" bonjour"
# exec_test "cat testyosticked"

# printf "20. '> test'yo'"sticked" echo bonjour'"
# exec_test "> test'yo'"sticked" echo bonjour"
# exec_test "cat testyosticked"

# printf "21. 'echo bonjour >> test'yo'"sticked"'"
# exec_test "echo bonjour >> test'yo'"sticked""
# exec_test "cat testyosticked"

# printf "22. '>> test'yo'"sticked" echo bonjour'"
# exec_test ">> test'yo'"sticked" echo bonjour"
# exec_test "cat testyosticked"

# printf "23. 'echo bonjour > test > je > suis'"
# exec_test "echo bonjour > test > je > suis"
# exec_test "cat suis"

# printf "24. 'echo > test > je bonjour > suis'"
# exec_test "echo > test > je bonjour > suis"
# exec_test "cat suis"

# printf "25. '> test echo bonjour > je > suis'"
# exec_test "> test echo bonjour > je > suis"
# exec_test "cat suis"

# printf "26. 'echo bonjour >> test > je >> suis'"
# exec_test "echo bonjour >> test > je >> suis"
# exec_test "cat suis"

# printf "27. 'echo >> test bonjour > je > suis'"
# exec_test "echo >> test bonjour > je > suis"
# exec_test "cat suis"

# printf "28. 'echo bonjour>test>je>suis'"
# exec_test "echo bonjour>test>je>suis"
# exec_test "cat suis"

# printf "29. 'echo bonjour>test>je>suis'"
# exec_test "echo bonjour>test>je>suis"
# exec_test "cat suis"

# printf "30. 'echo bonjour>>test>je>>suis'"
# exec_test "echo bonjour>>test>je>>suis"
# exec_test "cat suis"

# printf "31. '[SETUP echo bonjour > test; echo salut > je] cat<test<je'"
# exec_test "echo bonjour > test"
# exec_test "echo salut > je"
# exec_test "cat<test<je"

# printf "32. 'echo bonjour > a'b'c'd'e'f'g'h'i'j'k'l'm'n'o'p'q'r's't'u'v'w'x'y'z''"
# exec_test "echo bonjour > a'b'c'd'e'f'g'h'i'j'k'l'm'n'o'p'q'r's't'u'v'w'x'y'z'"
# exec_test "cat abcdefghijklmnopqrstuvwxyz"

# printf "33. 'echo bonjour > a"b"c"d"e"f"g"h"i"j"k"l"m"n"o"p"q"r"s"t"u"v"w"x"y"z"'"
# exec_test "echo bonjour > a"b"c"d"e"f"g"h"i"j"k"l"m"n"o"p"q"r"s"t"u"v"w"x"y"z""
# exec_test "cat abcdefghijklmnopqrstuvwxyz"

# printf "34. 'echo bonjour > a'b'c"d"e'f'g"h"i'j'k"l"m'n'o"p'q'r"s't'u"v"w"x"y'z' '"
# exec_test "echo bonjour > a'b'c"d"e'f'g"h"i'j'k"l"m'n'o"p'q'r"s't'u"v"w"x"y'z' "
# exec_test "cat a'b'c"d"e'f'g"h"i'j'k"l"m'n'o"p'q'r"s't'u"v"w"x"y'z'"

# printf "35. '> file'"
# exec_test "> file"
# exec_test "cat file"

# printf "36. '[SETUP echo bonjour > file] < file '"
# exec_test "echo bonjour > file"
# exec_test "< file"

echo     
# [SETUP echo bonjour > file] < file                                                                                                        [FAIL]
# >                                                                                                                                         [FAIL]
# >>                                                                                                                                        [FAIL]
# <                                                                                                                                         [FAIL]
# echo >                                                                                                                                    [FAIL]
# echo >>                                                                                                                                   [FAIL]
# echo <                                                                                                                                    [FAIL]
# > test                                                                                                                                    [FAIL]
# >> test                                                                                                                                   [FAIL]
# [SETUP touch test] < test                                                                                                                 [FAIL]
# echo foo >>> bar                                                                                                                          [FAIL]
# echo foo >>>> bar                                                                                                                         [FAIL]
# echo foo >>>>> bar                                                                                                                        [FAIL]
# [SETUP echo bonjour > bar] cat << < bar                                                                                                   [FAIL]
# [SETUP echo bonjour > bar] cat << << bar                                                                                                  [FAIL]
# [SETUP echo bonjour > bar] cat <<<<< bar                                                                                                  [FAIL]
# cat < doesnotexist                                                                                                                        [FAIL]
# [SETUP echo a > a] echo bonjour >> a                                                                                                      [PASS]
# [SETUP echo a > a] echo bonjour >> a >> a                                                                                                 [PASS]
# [SETUP echo a > a] echo bonjour > a                                                                                                       [PASS]
# [SETUP echo a > a] echo bonjour > a >> a
