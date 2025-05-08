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

	# Test 5: Empty file
	touch test5.txt
	"$assignment/ft_cat" test5.txt > output5.txt
	if [ ! -s output5.txt ]; then
		printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 5: Empty file handled correctly.${DEFAULT}\n"
	else
		printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 5: Empty file output not empty.${DEFAULT}\n"
		score_false=1
	fi

	# Test 6: Binary file
	head -c 512 /bin/ls > test6.bin
	"$assignment/ft_cat" test6.bin > output6.bin
	if cmp -s test6.bin output6.bin; then
		printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 6: Binary file displayed correctly.${DEFAULT}\n"
	else
		printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 6: Binary file mismatch.${DEFAULT}\n"
		score_false=1
	fi

	# Test 7: File with no permission
	echo "No permission" > test7.txt
	chmod 000 test7.txt
	output=$("$assignment/ft_cat" test7.txt 2>&1)
	chmod 644 test7.txt
	if echo "$output" | grep -q "Permission denied"; then
		printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 7: Permission denied error.${DEFAULT}\n"
	else
		printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 7: No error for permission denied.${DEFAULT}\n"
		score_false=1
	fi

	# Test 8: Many small files
	for i in {1..10}; do echo "line $i" > test8_$i.txt; done
	cat test8_*.txt > expected8.txt
	"$assignment/ft_cat" test8_*.txt > output8.txt
	if cmp -s output8.txt expected8.txt; then
		printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 8: Multiple small files concatenated.${DEFAULT}\n"
	else
		printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 8: Small file concat mismatch.${DEFAULT}\n"
		score_false=1
	fi

	# Test 9: Directory as argument
	mkdir test9_dir
	output=$("$assignment/ft_cat" test9_dir 2>&1)
	if echo "$output" | grep -q "Is a directory"; then
		printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 9: Directory error handled.${DEFAULT}\n"
	else
		printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 9: No error for directory input.${DEFAULT}\n"
		score_false=1
	fi

	# Test 10: Mix of existing and missing files
	echo "File exists" > test10.txt
	output=$("$assignment/ft_cat" test10.txt does_not_exist_2.txt 2>&1)
	if echo "$output" | grep -q "No such file or directory" && echo "$output" | grep -q "File exists"; then
		printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 10: Mixed valid and missing files handled.${DEFAULT}\n"
	else
		printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 10: Mixed file error/output incorrect.${DEFAULT}\n"
		score_false=1
	fi

	# Cleanup
	rm -f test1.dat output1.dat test2a.txt test2b.txt output2.dat expected2.dat
	rm -f test4.txt test5.txt output5.txt test6.bin output6.bin test7.txt
	rm -f test8_*.txt expected8.txt output8.txt
	rm -rf test9_dir test10.txt

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
