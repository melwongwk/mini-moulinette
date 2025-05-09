#!/bin/bash

source ../../config.sh

readonly PROJECT_DIR=$1
readonly assignment=$2
readonly assignment_id="$(basename "$assignment")"
readonly assignment_name="ft_list_push_back"
readonly SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"

main() {
	# Copy source files from student's folder into local test dir
	cp "$PROJECT_DIR/$assignment"/* "$SCRIPT_DIR"

	# Run norminette
	if ! run_norminette "$PROJECT_DIR/$assignment"; then
		printf "${RED}    $assignment_name failed norminette.${DEFAULT}\n"
		printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		rm -f "$SCRIPT_DIR/ft_list_push_back.c" "$SCRIPT_DIR"/*.h
		exit 8
	fi

	# Compile test and source
	if ! cc -o "$SCRIPT_DIR/test_exe" "$SCRIPT_DIR/test.c" "$SCRIPT_DIR/ft_list_push_back.c" 2> "$SCRIPT_DIR/log"; then
		cat "$SCRIPT_DIR/log"
		rm -f "$SCRIPT_DIR/ft_list_push_back.c" "$SCRIPT_DIR"/*.h "$SCRIPT_DIR"/test_exe "$SCRIPT_DIR"/log
		exit 12 # Compilation Error
	fi

	# Run the test
	if "$SCRIPT_DIR/test_exe"; then
		printf "${BG_GREEN}${BLACK}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		rm -f "$SCRIPT_DIR/ft_list_push_back.c" "$SCRIPT_DIR"/*.h "$SCRIPT_DIR"/test_exe "$SCRIPT_DIR"/log
		exit 0
	else
		printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		rm -f "$SCRIPT_DIR/ft_list_push_back.c" "$SCRIPT_DIR"/*.h "$SCRIPT_DIR"/test_exe "$SCRIPT_DIR"/log
		exit 16 # Test failed
	fi
}

main
