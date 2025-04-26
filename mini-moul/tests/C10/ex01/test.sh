#!/bin/bash

source ../../config.sh

readonly PROJECT_DIR=$1
readonly assignment=$2
readonly assignment_id="$(basename "$assignment")"
readonly assignment_name="cat"

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
		printf "${RED}    $assignment_name cannot be make.${DEFAULT}\n"
		printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		exit 12
	fi

	# Check if binary exists
	if [ ! -f "$assignment/ft_cat" ]; then
		printf "${RED}    $assignment_name binary not found.${DEFAULT}\n"
		printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		exit 16
	fi

	# Initialize score flag
	score_false=0

	# Test 1: Display file content
	dd if=/dev/urandom of=test1.dat bs=1M count=1 &>/dev/null
	"$assignment/ft_cat" test1.dat > output1.dat
	if cmp -s output1.dat test1.dat; then
		printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 1: File content displayed correctly.${DEFAULT}\n"
	else
		printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 1: File content mismatch.${DEFAULT}\n"
		score_false=1
	fi

	# Test 2: Multiple files
	echo "Hello" > test2a.txt
	echo "World" > test2b.txt
	"$assignment/ft_cat" test2a.txt test2b.txt > output2.dat
	cat test2a.txt test2b.txt > expected2.dat
	if cmp -s output2.dat expected2.dat; then
		printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 2: Multiple files concatenated.${DEFAULT}\n"
	else
		printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 2: Multiple files mismatch.${DEFAULT}\n"
		score_false=1
	fi

	# Test 3: File does not exist
	output=$("$assignment/ft_cat" does_not_exist.txt 2>&1)
	if echo "$output" | grep -q "No such file or directory"; then
		printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 3: Error for non-existing file.${DEFAULT}\n"
	else
		printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 3: No error for missing file.${DEFAULT}\n"
		score_false=1
	fi

	# Test 4: Read from stdin
	echo "Test stdin input" > test4.txt
	output=$(cat test4.txt | "$assignment/ft_cat" -)
	expected=$(cat test4.txt)
	if [ "$output" = "$expected" ]; then
		printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 4: Reading from stdin.${DEFAULT}\n"
	else
		printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 4: Reading from stdin failed.${DEFAULT}\n"
		score_false=1
	fi

	# Cleanup
	rm -f test1.dat output1.dat test2a.txt test2b.txt output2.dat expected2.dat test4.txt

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
