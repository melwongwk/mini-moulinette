source ../../config.sh

readonly PROJECT_DIR=$1
readonly assignment=$2
readonly assignment_id="$(basename "$assignment")"
readonly assignment_name="hexdump"

main() {
	cp $PROJECT_DIR/$assignment/* $assignment
	if ! run_norminette $PROJECT_DIR/$assignment; then
		printf "${RED}    $assignment_name failed norminette.${DEFAULT}\n"
		printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		exit 8
	elif ! (cd $assignment && make clean && make && make fclean && make && make clean && ls -la ft_hexdump); then
		printf "${RED}    $assignment_name cannot be make.${DEFAULT}\n"
		printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		exit 12
	else
		if [ ! -f "$assignment/ft_hexdump" ]; then
			printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
			exit 16
		fi
		score_false=0
		dd if=/dev/urandom of=test1.dat bs=1m count=2
		dd if=/dev/urandom of=test2.dat bs=1m count=2
		dd if=/dev/urandom of=test3.dat bs=1m count=2
		mv $assignment/ft_hexdump $assignment/hexdump
		if diff -U3 <(./$assignment/hexdump test1.dat 2>&1) <(hexdump test1.dat 2>&1); then
			printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
		else
			printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
			score_false=1
		fi
		if diff -U3 <(./$assignment/hexdump -C test1.dat 2>&1) <(hexdump -C test1.dat 2>&1); then
			printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
		else
			printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
			score_false=1
		fi
		if diff -U3 <(./$assignment/hexdump <test1.dat 2>&1) <(hexdump <test1.dat 2>&1); then
			printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
		else
			printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
			score_false=1
		fi
		if diff -U3 <(./$assignment/hexdump a 2>&1) <(hexdump a 2>&1); then
			printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
		else
			printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
			score_false=1
		fi
		if diff -U3 <(./$assignment/hexdump -C a 2>&1) <(hexdump -C a 2>&1); then
			printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
		else
			printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
			score_false=1
		fi
		if diff -U3 <(./$assignment/hexdump a 2>&1 1>/dev/null) <(hexdump a 2>&1 1>/dev/null); then
			printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
		else
			printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
			score_false=1
		fi
		if diff -U3 <(./$assignment/hexdump test1.dat test2.dat 2>&1) <(hexdump test1.dat test2.dat 2>&1); then
			printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
		else
			printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
			score_false=1
		fi
		if diff -U3 <(./$assignment/hexdump -C test1.dat test2.dat 2>&1) <(hexdump -C test1.dat test2.dat 2>&1); then
			printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
		else
			printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
			score_false=1
		fi
		if diff -U3 <(./$assignment/hexdump test1.dat a test2.dat 2>/dev/null) <(hexdump test1.dat a test2.dat 2>/dev/null); then
			printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
		else
			printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
			score_false=1
		fi
		if diff -U3 <(./$assignment/hexdump -C test1.dat a test2.dat 2>/dev/null) <(hexdump -C test1.dat a test2.dat 2>/dev/null); then
			printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
		else
			printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
			score_false=1
		fi
		if diff -U3 <(./$assignment/hexdump test1.dat a test2.dat 2>&1 1>/dev/null) <(hexdump test1.dat a test2.dat 2>&1 1>/dev/null); then
			printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
		else
			printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
			score_false=1
		fi
		if diff -U3 <(./$assignment/hexdump test1.dat test2.dat a 2>/dev/null) <(hexdump test1.dat test2.dat a 2>/dev/null); then
			printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
		else
			printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
			score_false=1
		fi
		if diff -U3 <(./$assignment/hexdump -C test1.dat test2.dat a 2>/dev/null) <(hexdump -C test1.dat test2.dat a 2>/dev/null); then
			printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
		else
			printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
			score_false=1
		fi
		if diff -U3 <(./$assignment/hexdump test1.dat test2.dat a 2>&1 1>/dev/null) <(hexdump test1.dat test2.dat a 2>&1 1>/dev/null); then
			printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
		else
			printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
			score_false=1
		fi
		if diff -U3 <(./$assignment/hexdump a test1.dat test2.dat 2>/dev/null) <(hexdump a test1.dat test2.dat 2>/dev/null); then
			printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
		else
			printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
			score_false=1
		fi
		if diff -U3 <(./$assignment/hexdump -C a test1.dat test2.dat 2>/dev/null) <(hexdump -C a test1.dat test2.dat 2>/dev/null); then
			printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
		else
			printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
			score_false=1
		fi
		if diff -U3 <(./$assignment/hexdump a test1.dat test2.dat 2>&1 1>/dev/null) <(hexdump a test1.dat test2.dat 2>&1 1>/dev/null); then
			printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
		else
			printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
			score_false=1
		fi
		chmod -r test1.dat
		if diff -U3 <(./$assignment/hexdump a test1.dat 2>&1 1>/dev/null) <(hexdump a test1.dat 2>&1 1>/dev/null); then
			printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
		else
			printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
			score_false=1
		fi
		if diff -U3 <(./$assignment/hexdump -C a test1.dat 2>&1 1>/dev/null) <(hexdump -C a test1.dat 2>&1 1>/dev/null); then
			printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
		else
			printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
			score_false=1
		fi
		rm $assignment/hexdump ./test*.dat
		if [ $score_false = 0 ]; then
			printf "${BG_GREEN}${BLACK}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
			exit 0
		else
			printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
			exit 16
		fi
	fi
}

main
