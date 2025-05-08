#!/bin/bash

source ../../config.sh

readonly PROJECT_DIR=$1
readonly assignment=$2
readonly assignment_id="$(basename "$assignment")"
readonly assignment_name="do-op"

run_test() {
	local description=$1
	local actual_cmd=$2
	local expected_output=$3
	local stream=${4:-stdout}  # default to stdout

	local actual_output

	if [[ "$stream" == "stderr" ]]; then
		actual_output=$(eval "$actual_cmd" 2>&1 1>/dev/null)
	else
		actual_output=$(eval "$actual_cmd" 2>/dev/null)
	fi

	if [[ "$actual_output" == "$expected_output" ]]; then
		printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name $description.${DEFAULT}\n"
	else
		printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name $description.${DEFAULT}\n"
		score_false=1
	fi
}

main() {
	rm -rf "$assignment"
	mkdir -p "$assignment"
	cp -r "$PROJECT_DIR/$assignment"/* "$assignment"

	if ! run_norminette "$PROJECT_DIR/$assignment"; then
		printf "${RED}    $assignment_name failed norminette.${DEFAULT}\n"
		printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		exit 8
	fi

	if ! (cd "$assignment" && make -s clean && make -s && make -s fclean && make -s && make -s clean); then
		printf "${RED}    $assignment_name cannot be made.${DEFAULT}\n"
		printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		exit 12
	fi

	if [ ! -f "$assignment/do-op" ]; then
		printf "${RED}    $assignment_name binary not found.${DEFAULT}\n"
		printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		exit 16
	fi

	score_false=0

	# Basic operator tests
	run_test "Addition" "./$assignment/do-op 1 + 1" "2"
	run_test "Subtraction" "./$assignment/do-op 10 - 3" "7"
	run_test "Multiplication" "./$assignment/do-op 6 '*' 7" "42"
	run_test "Division" "./$assignment/do-op 20 / 4" "5"
	run_test "Modulo" "./$assignment/do-op 22 % 5" "2"

	# Argument errors
	run_test "No arguments" "./$assignment/do-op" ""
	run_test "Too many arguments" "./$assignment/do-op 1 + 2 extra" ""

	# Invalid operator/operand
	run_test "Invalid operator" "./$assignment/do-op 1 p 1" "0"
	run_test "Invalid right operand" "./$assignment/do-op 1 + toto3" "1"
	run_test "Invalid left operand" "./$assignment/do-op toto3 + 4" "4"
	run_test "Invalid operands and operator" "./$assignment/do-op foo plus bar" "0"

	# Division/modulo by zero (check stderr)
	run_test "Division by zero" "./$assignment/do-op 25 / 0" "Stop : division by zero" "stderr"
	run_test "Modulo by zero" "./$assignment/do-op 25 % 0" "Stop : modulo by zero" "stderr"

	# Mixed/complex value parsing
	run_test "Complex operand parsing" "./$assignment/do-op 42amis - --+-20toto12" "62"

	# Edge cases
	run_test "INT_MAX + 1" "./$assignment/do-op 2147483647 + 1" "2147483648"
	run_test "INT_MIN - 1" "./$assignment/do-op -2147483648 - 1" "-2147483649"
	run_test "Overflow multiply" "./$assignment/do-op 46341 '*' 46341" "2147488281"

	# Bonus: chained/extra symbols
	run_test "Chained operators" "./$assignment/do-op 1 + + 2" ""
	run_test "Extra whitespace" "./$assignment/do-op  3   '*'     3  " "9"
	run_test "Empty string as operand" "./$assignment/do-op \"\" + 4" "4"
	run_test "Empty string as both" "./$assignment/do-op \"\" + \"\"" "0"
	run_test "Operator as word" "./$assignment/do-op 3 plus 5" "0"
	run_test "Only operator symbol" "./$assignment/do-op + + +" "0"

	# Final result
	if [ $score_false = 0 ]; then
		printf "${BG_GREEN}${BLACK}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		exit_code=0
	else
		printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		exit_code=16
	fi

	# Cleanup
	rm -rf "$assignment"
	exit $exit_code
}

main
