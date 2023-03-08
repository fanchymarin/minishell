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
rm -rf leaks/*
make re -C ../ > /dev/null
cp ../minishell .
chmod 755 minishell

function exec_test()
{
	TEST1=$(echo $@ | valgrind --log-file="leaks/$@" ./minishell 2>&-)

	printf "$CYAN \"$@\" $RESET"
	echo
	echo
	printf "$TEST1\n"
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
echo
printf "$BOLDMAGENTA	ENV EXPANSIONS\n"
exec_test 'echo $TEST'
exec_test 'echo "$TEST"'
exec_test "echo '$TEST'"
exec_test 'echo "$TEST$TEST$TEST"'
exec_test 'echo "$TEST$TEST=lol$TEST"'
exec_test 'echo "   $TEST lol $TEST"'
exec_test 'echo $TEST$TEST$TEST'
exec_test 'echo $TEST$TEST=lol$TEST""lol'
exec_test 'echo    $TEST lol $TEST'
exec_test 'echo "test "" test" " test      "'
exec_test 'echo "$=TEST"'
exec_test 'echo "$"'
exec_test 'echo "$?TEST"'
exec_test 'echo $TEST $TEST'
exec_test 'echo "$T1TEST"'
echo
echo
printf "$BOLDMAGENTA	ENV EXPANSIONS\n"
ENV_SHOW="env | sort | grep -v SHLVL | grep -v _="
exec_test 'export ='
exec_test 'export 1TEST= '
exec_test $ENV_SHOW
exec_test 'export TEST'
exec_test $ENV_SHOW
exec_test 'export ""=""'
exec_test $ENV_SHOW
exec_test 'export TES=T=""'
exec_test $ENV_SHOW
exec_test 'export TE+S=T=""'
exec_test $ENV_SHOW
exec_test 'export TEST=LOL'
exec_test 'echo $TEST'
exec_test $ENV_SHOW
exec_test 'export TEST=LOL'
exec_test 'echo $TEST$TEST$TEST=lol$TEST'
exec_test 'export TEST=LOL; export TEST+=LOL'
exec_test 'echo $TEST'
exec_test $ENV_SHOW
exec_test 'export TEST="ls       -l     - a"'
exec_test 'echo $TEST'
exec_test '$LS'
exec_test $ENV_SHOW

# # MULTI TESTS
# exec_test 'echo testing multi ; echo "test 1 ; | and 2" ; cat tests/lorem.txt | grep Lorem'

rm out* minishell
