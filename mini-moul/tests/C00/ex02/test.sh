source ~/mini-moulinette/mini-moul/config.sh

readonly PROJECT_DIR=$1
readonly assignment=$2
readonly assignment_id="$(basename "$assignment")"
readonly assignment_name="ft_print_reverse_alphabet"
readonly files=("$PROJECT_DIR/$assignment/ft_print_reverse_alphabet.c")

main() {
	for file in ${files[@]}; do
		if [ ! -f "$file" ]; then
			printf "${RED}    $(basename $file) is not submitted.${DEFAULT}\n"
			printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
			exit 4
		fi
	done
	if ! run_norminette ${files[@]} -R CheckForbiddenSourceHeader; then
		printf "${RED}    $assignment_name failed norminette.${DEFAULT}\n"
		printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		exit 8
	elif ! (ccw -o test1 $assignment/main.c $files); then
		printf "${RED}    $assignment_name cannot compile.${DEFAULT}\n"
		printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		exit 12
	else
		rm test1

		score_false=0
		if (
			ccw -o test $assignment/test.c ${files[@]} 2>/dev/null
		); then
			if ./test = 0; then
				printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name${DEFAULT}\n"
			else
				printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name${DEFAULT}\n"
				score_false=1
			fi
			rm test
		else
			printf "    ""${GREY}[1] $assignment_id/test.c ${RED}FAILED${DEFAULT}\n"
		fi
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
