source ../../config.sh

readonly PROJECT_DIR=$1
readonly assignment=$2
readonly assignment_id="$(basename "$assignment")"
readonly assignment_name="ft.h"
readonly files=("ft.h")
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
	if ! run_norminette ${files_dir[@]}; then
		printf "${RED}    $assignment_name failed norminette.${DEFAULT}\n"
		printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		exit 8
	fi
	
	if ! (ccw -Wall -Wextra -Werror -o test1 $assignment/main.c $assignment/ft.c); then
		printf "${RED}    $assignment_name cannot compile.${DEFAULT}\n"
		printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		exit 12
	else
		./test1 > output.txt
		
expected_output="Z
Hello, 42!
Length: 10
Cmp1: 0
Cmp2: -1
Cmp3: 1
Swapped: a=2 b=1"

		# Normalize ft_strcmp outputs to just their sign
		actual_output=$(sed -E 's/Cmp1: [^ ]+/Cmp1: 0/; s/Cmp2: [^ ]+/Cmp2: -1/; s/Cmp3: [^ ]+/Cmp3: 1/' output.txt)
		expected_output=$(echo "$expected_output" | sed 's/^[[:space:]]*//;s/[[:space:]]*$//')
		
		# Trim any leading/trailing spaces from the actual output as well
		actual_output=$(echo "$actual_output" | sed 's/^[[:space:]]*//;s/[[:space:]]*$//')

		# Compare the outputs
		if [ "$actual_output" != "$expected_output" ]; then
			echo "Output doesn't match expected results."
			echo "Expected:"
			echo "$expected_output"
			echo "Actual:"
			echo "$actual_output"
			printf "${RED}    Output doesn't match expected results.${DEFAULT}\n"
			printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
			rm -f test1 output.txt
			exit 16
		fi
		rm -f test1 output.txt
		printf "${BG_GREEN}${BLACK}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		exit 0
	fi
}

main
