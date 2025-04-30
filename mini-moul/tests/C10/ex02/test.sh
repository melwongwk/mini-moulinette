#!/bin/bash

source ../../config.sh

readonly PROJECT_DIR=$1
readonly assignment=$2
readonly assignment_id="$(basename "$assignment")"
readonly assignment_name="tail"

main() {
	# Copy source files
	cp "$PROJECT_DIR/$assignment"/* "$assignment"

	# Run norminette and suppress output if failed
	if ! run_norminette "$PROJECT_DIR/$assignment"; then
		printf "${RED}    $assignment_name failed norminette.${DEFAULT}\n"
		printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		exit 8
	fi

	# Run make silently
	if ! (cd "$assignment" && make -s clean && make -s && make -s fclean && make -s && make -s clean); then
		printf "${RED}    $assignment_name cannot be made.${DEFAULT}\n"
		printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		exit 12
	fi

	# Check if binary exists
	if [ ! -f "$assignment/ft_tail" ]; then
		printf "${RED}    $assignment_name binary not found.${DEFAULT}\n"
		printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		exit 16
	fi

	# Initialize score flag
	score_false=0

	# Create test files
	dd if=/dev/urandom of=test1.dat bs=1M count=2 &>/dev/null
	dd if=/dev/urandom of=test2.dat bs=1M count=2 &>/dev/null
	dd if=/dev/urandom of=test3.dat bs=1M count=2 &>/dev/null
	dd if=/dev/urandom of=test7.dat bs=100 count=1 &>/dev/null
	touch emptyfile.dat  # Create an empty file for Test 6
	mv "$assignment/ft_tail" "$assignment/tail"

	# Test 1: Basic file tail
	if diff -U3 <(./"$assignment"/tail -c 10 test1.dat 2>&1) <(tail -c 10 test1.dat 2>&1); then
		printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 1: Basic file tail.${DEFAULT}\n"
	else
		printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 1: Basic file tail.${DEFAULT}\n"
		score_false=1
	fi

	# Test 2: Tail from stdin
	output_ft_tail=$(echo "Hello from stdin!" | ./"$assignment"/tail -c 6 - 2>&1)
	output_tail=$(echo "Hello from stdin!" | tail -c 6 - 2>&1)
	if diff -U3 <(echo "$output_ft_tail") <(echo "$output_tail"); then
		printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 2: Tail from stdin.${DEFAULT}\n"
	else
		printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 2: Tail from stdin.${DEFAULT}\n"
		score_false=1
	fi

	# Test 3: Nonexistent file
	if diff -U3 <(./"$assignment"/tail -c 10 nofile.dat 2>&1) <(tail -c 10 nofile.dat 2>&1); then
		printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 3: Nonexistent file.${DEFAULT}\n"
	else
		printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 3: Nonexistent file.${DEFAULT}\n"
		score_false=1
	fi

	# Test 4: Multiple files
	if diff -U3 <(./"$assignment"/tail -c 10 test1.dat test2.dat 2>&1) <(tail -c 10 test1.dat test2.dat 2>&1); then
		printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 4: Multiple files.${DEFAULT}\n"
	else
		printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 4: Multiple files.${DEFAULT}\n"
		score_false=1
	fi

	# Test 5: Stdin between files
	output_ft_tail=$(echo "Content for stdin" | ./"$assignment"/tail -c 10 test1.dat - test2.dat 2>&1)
	output_tail=$(echo "Content for stdin" | tail -c 10 test1.dat - test2.dat 2>&1)

	if diff -U3 <(echo "$output_ft_tail") <(echo "$output_tail"); then
		printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 5: Stdin between files.${DEFAULT}\n"
	else
		printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 5: Stdin between files.${DEFAULT}\n"
		score_false=1
	fi
	
	# Test 6: Empty file
	if diff -U3 <(./"$assignment"/tail -c 10 emptyfile.dat 2>&1) <(tail -c 10 emptyfile.dat 2>&1); then
		printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 6: Empty file.${DEFAULT}\n"
	else
		printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 6: Empty file.${DEFAULT}\n"
		score_false=1
	fi

	# Test 7: Small file
	if diff -U3 <(./"$assignment"/tail -c 1000 test4.dat 2>&1) <(tail -c 1000 test4.dat 2>&1); then
		printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 7: Small file.${DEFAULT}\n"
	else
		printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 7: Small file.${DEFAULT}\n"
		score_false=1
	fi

	# Cleanup
	rm -f test1.dat test2.dat test3.dat test7.dat emptyfile.dat

	# Final score output
	if [ $score_false = 0 ]; then
		printf "${BG_GREEN}${BLACK}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		exit 0
	else
		printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		exit 16
	fi
}

main
