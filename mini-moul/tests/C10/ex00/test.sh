source ~/mini-moulinette/mini-moul/config.sh

readonly PROJECT_DIR=$1
readonly assignment=$2
readonly assignment_id="$(basename "$assignment")"
readonly assignment_name="display_file"

main() {
	cp $PROJECT_DIR/$assignment/* $assignment
	if ! run_norminette $PROJECT_DIR/$assignment; then
		printf "${RED}    $assignment_name failed norminette.${DEFAULT}\n"
		printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		exit 8
	elif ! (cd $assignment && make clean && make && make fclean && make && make clean && ls -la ft_display_file); then
		printf "${RED}    $assignment_name cannot be make.${DEFAULT}\n"
		printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		exit 12
	else
		if [ ! -f "$assignment/ft_display_file" ]; then
			printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
			exit 16
		fi
		score_false=0
		dd if=/dev/urandom of=test.dat bs=1m count=2
		if diff -U3 <($assignment/ft_display_file test.dat) <(cat test.dat); then
			printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
		else
			printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
			score_false=1
		fi
		if diff -U3 <($assignment/ft_display_file) <(echo "File name missing."); then
			printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
		else
			printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
			score_false=1
		fi
		if diff -U3 <($assignment/ft_display_file a b) <(echo "Too many arguments."); then
			printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
		else
			printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
			score_false=1
		fi
		if diff -U3 <($assignment/ft_display_file A) <(echo "Cannot read file."); then
			printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
		else
			printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
			score_false=1
		fi
		rm $assignment/ft_display_file ./test.dat
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
