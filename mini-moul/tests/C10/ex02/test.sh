#!/bin/bash

source ../../config.sh

readonly PROJECT_DIR=$1
readonly assignment=$2
readonly assignment_id="$(basename "$assignment")"
readonly assignment_name="tail"

main() {
	cp "$PROJECT_DIR/$assignment"/* "$assignment"

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

	if [ ! -f "$assignment/ft_tail" ]; then
		printf "${RED}    $assignment_name binary not found.${DEFAULT}\n"
		printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		exit 16
	fi

	score_false=0
	dd if=/dev/urandom of=test1.dat bs=1M count=2 &>/dev/null
	dd if=/dev/urandom of=test2.dat bs=1M count=2 &>/dev/null
	dd if=/dev/urandom of=test3.dat bs=1M count=2 &>/dev/null
	dd if=/dev/urandom of=test7.dat bs=100 count=1 &>/dev/null
	touch emptyfile.dat
	echo "Hello World" > test8.txt
	echo "This is test 9" > test9.txt
	echo "Sample content" > test10.txt

	mv "$assignment/ft_tail" "$assignment/tail"

	# Test 1: Basic file tail
	if diff -U3 <(./"$assignment"/tail -c 10 test1.dat 2>&1) <(tail -c 10 test1.dat 2>&1); then
		printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 1: Basic file tail.${DEFAULT}\n"
	else
		printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 1: Basic file tail.${DEFAULT}\n"
		score_false=1
	fi

	# Test 2: Tail from stdin
	echo "Hello from stdin!" | ./"$assignment"/tail -c 6 2>&1 > ft_tail_output.txt
	echo "Hello from stdin!" | tail -c 6 2>&1 > tail_output.txt
	if diff -U3 ft_tail_output.txt tail_output.txt > /dev/null; then
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
	echo "Content for stdin" | ./"$assignment"/tail -c 10 test1.dat - test2.dat 2>&1 > ft_tail_output.txt
	echo "Content for stdin" | tail -c 10 test1.dat - test2.dat 2>&1 > tail_output.txt
	if diff -U3 ft_tail_output.txt tail_output.txt > /dev/null; then
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
	if diff -U3 <(./"$assignment"/tail -c 1000 test7.dat 2>&1) <(tail -c 1000 test7.dat 2>&1); then
		printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 7: Small file.${DEFAULT}\n"
	else
		printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 7: Small file.${DEFAULT}\n"
		score_false=1
	fi

	# ------------------- New Tests -------------------

	# Test 8: -c 0 (Should print nothing)
	./"$assignment"/tail -c 0 test8.txt 2>&1 > ft_tail_output.txt
	tail -c 0 test8.txt 2>&1 > tail_output.txt
	if diff -U3 ft_tail_output.txt tail_output.txt > /dev/null; then
		printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 8: -c 0 (Print nothing).${DEFAULT}\n"
	else
		printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 8: -c 0 (Print nothing).${DEFAULT}\n"
		score_false=1
	fi

	# Test 9: -c with invalid argument
	./"$assignment"/tail -c foo test10.txt 2>&1 > ft_tail_output.txt
	tail -c foo test10.txt 2>&1 > tail_output.txt
	if diff -U3 ft_tail_output.txt tail_output.txt > /dev/null; then
		printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 9: Invalid -c argument.${DEFAULT}\n"
	else
		printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 9: Invalid -c argument.${DEFAULT}\n"
		score_false=1
	fi

	# Test 10: -c with missing argument
	output_ft_tail=$(./"$assignment"/tail -c 2>&1)
	output_tail=$(tail -c 2>&1)
	if diff -U3 <(echo "$output_ft_tail") <(echo "$output_tail"); then
		printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 10: Missing -c argument.${DEFAULT}\n"
	else
		printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 10: Missing -c argument.${DEFAULT}\n"
		score_false=1
	fi

	# Test 11: File smaller than requested byte count
	output_ft_tail=$(./"$assignment"/tail -c 9999 test8.txt 2>&1)
	output_tail=$(tail -c 9999 test8.txt 2>&1)
	if diff -U3 <(echo "$output_ft_tail") <(echo "$output_tail"); then
		printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 11: More bytes than file size.${DEFAULT}\n"
	else
		printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 11: More bytes than file size.${DEFAULT}\n"
		score_false=1
	fi

	# Test 12: Directory input
	output_ft_tail=$(./"$assignment"/tail -c 10 . 2>&1)
	output_tail=$(tail -c 10 . 2>&1)
	if diff -U3 <(echo "$output_ft_tail") <(echo "$output_tail"); then
		printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 12: Directory input.${DEFAULT}\n"
	else
		printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 12: Directory input.${DEFAULT}\n"
		score_false=1
	fi

	# Test 13: Permission denied
	echo "This is a protected file" > protected.dat
	chmod 000 protected.dat
	output_ft_tail=$(./"$assignment"/tail -c 10 protected.dat 2>&1)
	output_tail=$(tail -c 10 protected.dat 2>&1)
	chmod 644 protected.dat
	rm -f protected.dat
	if diff -U3 <(echo "$output_ft_tail") <(echo "$output_tail"); then
		printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 13: Permission denied.${DEFAULT}\n"
	else
		printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 13: Permission denied.${DEFAULT}\n"
		score_false=1
	fi
	
	# Test 14: One valid and one nonexistent file
	if diff -U3 <(./"$assignment"/tail -c 10 test8.txt nofile999.dat 2>&1) <(tail -c 10 test8.txt nofile999.dat 2>&1); then
		printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 14: Valid + nonexistent file.${DEFAULT}\n"
	else
		printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 14: Valid + nonexistent file.${DEFAULT}\n"
		score_false=1
	fi

	# Test 15: Mix of valid file, empty file, and stdin
	echo "stdin content here" | ./"$assignment"/tail -c 8 test9.txt emptyfile.dat - 2>&1 > ft_tail_output.txt
	echo "stdin content here" | tail -c 8 test9.txt emptyfile.dat - 2>&1 > tail_output.txt
	if diff -U3 ft_tail_output.txt tail_output.txt > /dev/null; then
		printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 15: Valid + empty + stdin.${DEFAULT}\n"
	else
		printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 15: Valid + empty + stdin.${DEFAULT}\n"
		score_false=1
	fi

	# Test 16: Valid file, nonexistent file, valid file
	if diff -U3 <(./"$assignment"/tail -c 5 test8.txt nofile123.txt test9.txt 2>&1) <(tail -c 5 test8.txt nofile123.txt test9.txt 2>&1); then
		printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 16: Valid + missing + valid.${DEFAULT}\n"
	else
		printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 16: Valid + missing + valid.${DEFAULT}\n"
		score_false=1
	fi

	# Test 17: Stdin, valid file, stdin again
	{ echo "first stdin"; echo "second stdin"; } | ./"$assignment"/tail -c 6 - test8.txt - 2>&1 > ft_tail_output.txt
	{ echo "first stdin"; echo "second stdin"; } | tail -c 6 - test8.txt - 2>&1 > tail_output.txt
	if diff -U3 ft_tail_output.txt tail_output.txt > /dev/null; then
		printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 17: stdin + valid + stdin.${DEFAULT}\n"
	else
		printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 17: stdin + valid + stdin.${DEFAULT}\n"
		score_false=1
	fi


	# Cleanup
	rm -f test1.dat test2.dat test3.dat test7.dat test8.txt test9.txt test10.txt emptyfile.dat
	rm -f ft_tail_output.txt tail_output.txt

	if [ $score_false = 0 ]; then
		printf "${BG_GREEN}${BLACK}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		exit 0
	else
		printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		exit 16
	fi
}

main
