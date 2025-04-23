source ../../config.sh

readonly PROJECT_DIR=$1
readonly assignment=$2
readonly assignment_id="$(basename "$assignment")"
readonly assignment_name="ft_show_tab.c"
readonly files=("ft_show_tab.c" "../ex04/ft_strs_to_tab.c")
readonly files_dir=$(for file in "${files[@]}"; do echo -n "$assignment/$file "; done)

main() {
	for file in ${files[@]}; do
		if [ ! -f "$PROJECT_DIR/$assignment/$file" ]; then
			printf "${RED}    $(basename $file) is not submitted.${DEFAULT}\n"
			printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
			exit 4
		else
			\cp $PROJECT_DIR/$assignment/$file $assignment
		fi
	done
	if ! output=$(run_norminette ${files_dir[@]}); then
		echo "$output"
		printf "${RED}    $assignment_name failed norminette.${DEFAULT}\n"
		printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		exit 8
	else
		# Print norminette OK only for the main assignment file
		echo "$output" | grep "$(basename $assignment_name)"
	fi

	if ! (ccw -o test1 $assignment/test.c ${files_dir[@]}); then
		printf "${RED}    $assignment_name cannot compile.${DEFAULT}\n"
		printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		exit 12
	else
		score_false=0
		args=("AAAA" "BBB" "CC")
		buffer=$(./test1 ${args[@]})
		expected=$'AAAA\n4\naAAA\nBBB\n3\nBBB\nCC\n2\nCC'
		if [ "$buffer" != "$expected" ]; then
			printf "    ${RED}[1] ./test ${args[@]} Expected \"$expected\", got \"$buffer\"\n${DEFAULT}"
			score_false=1
		else
			printf "${GREEN}${CHECKMARK}${GREY} [1] ./test with args: \"${args[*]}\"\n"
			printf "    Output matched expected result.\n${DEFAULT}"
		fi
		rm test1
		if [ $score_false = 0 ]; then
			printf "\n${BG_GREEN}${BLACK}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
			exit 0
		else
			printf "\n${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
			exit 16
		fi
	fi
}

main
