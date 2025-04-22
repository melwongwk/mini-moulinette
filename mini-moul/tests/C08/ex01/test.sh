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
	
	if ! grep -q "# *ifndef *FT_BOOLEAN_H" "$assignment/ft_boolean.h"; then
		printf "${RED}    Missing or incorrect include guard macro.${DEFAULT}\n"
		printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		exit 6
	fi
	
	if ! grep -q "t_bool[[:space:]]\+ft_is_even" "$assignment/ft_boolean.h"; then
		printf "${RED}    ft_is_even is not declared properly in the header.${DEFAULT}\n"
		printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		exit 7
	fi
	
	if ! grep -q "void[[:space:]]\+ft_putstr" "$assignment/ft_boolean.h"; then
		printf "${RED}    ft_putstr is not declared properly in the header.${DEFAULT}\n"
		printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		exit 7
	fi
	
	if ! run_norminette -R CheckDefine ${files_dir[@]}; then
		printf "${RED}    $assignment_name failed norminette.${DEFAULT}\n"
		printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		exit 8
	fi
	
	if ! (ccw -o test1 $assignment/main.c); then
		printf "${RED}    $assignment_name cannot compile.${DEFAULT}\n"
		printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		exit 12
	fi
	
	score_false=0

	for arg_count in 1 2 3 4; do
		args=()
		for i in $(seq 1 $arg_count); do
			args+=("arg$i")
		done

		if [ $((arg_count % 2)) -eq 0 ]; then
			expected_msg="I have an even number of arguments."
		else
			expected_msg="I have an odd number of arguments."
		fi
		
		buffer=$(./test1 "${args[@]}")

		if [ "$buffer" != "$expected_msg" ]; then
			printf "    ${RED}[arg_count=$arg_count] Expected \"$expected_msg\", got \"$buffer\"\n${DEFAULT}"
			score_false=1
		else
			printf "  ${GREEN}${CHECKMARK}${GREY} [arg_count=$arg_count] output \"$buffer\" as expected\n${DEFAULT}"
		fi
	done

	rm -f test1

	if [ $score_false = 0 ]; then
		printf "${BG_GREEN}${BLACK}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		exit 0
	else
		printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		exit 16
	fi
}

main