source ../../config.sh

readonly PROJECT_DIR=$1
readonly assignment=$2
readonly assignment_id="$(basename "$assignment")"
readonly assignment_name="ft_boolean.h"
readonly files=("ft_boolean.h")
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
	if ! run_norminette -R CheckDefine ${files_dir[@]}; then
		printf "${RED}    $assignment_name failed norminette.${DEFAULT}\n"
		printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		exit 8
	elif ! (ccw -o test1 $assignment/main.c); then
		printf "${RED}    $assignment_name cannot compile.${DEFAULT}\n"
		printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		exit 12
	else
		score_false=0
		args=("AAA" "AAA")
		buffer=$(./test1 ${args[@]})
		expected='I have an even number of arguments.'
		if [ "$buffer" != "$expected" ]; then
			printf "    ${RED}[1] ./test ${args[@]} Expected \"$expected\", got \"$buffer\"\n${DEFAULT}"
			score_false=1
		else
			printf "  ${GREEN}${CHECKMARK}${GREY} [1] ./test ${args[@]} output \"$buffer\" as expected\n${DEFAULT}"
		fi
		args=("AAA")
		buffer=$(./test1 ${args[@]})
		expected='I have an odd number of arguments.'
		if [ "$buffer" != "$expected" ]; then
			printf "    ${RED}[2] ./test ${args[@]} Expected \"$expected\", got \"$buffer\"\n${DEFAULT}"
			score_false=1
		else
			printf "  ${GREEN}${CHECKMARK}${GREY} [2] ./test ${args[@]} output \"$buffer\" as expected\n${DEFAULT}"
		fi
		rm test1
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
