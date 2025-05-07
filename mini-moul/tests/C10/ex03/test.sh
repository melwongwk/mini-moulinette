#!/bin/bash

source ../../config.sh

readonly PROJECT_DIR=$1
readonly assignment=$2
readonly assignment_id="$(basename "$assignment")"
readonly assignment_name="hexdump"

run_test() {
	local description=$1
	local cmd1=$2
	local cmd2=$3

	if diff -U3 <(eval "$cmd1") <(eval "$cmd2"); then
		printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name $description.${DEFAULT}\n"
	else
		printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name $description.${DEFAULT}\n"
		score_false=1
	fi
}

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

	if [ ! -f "$assignment/ft_hexdump" ]; then
		printf "${RED}    $assignment_name binary not found.${DEFAULT}\n"
		printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		exit 16
	fi

	mv "$assignment/ft_hexdump" "$assignment/hexdump"
	score_false=0

	# Prepare files
	echo -n "Hello World" > file1.txt
	echo -n "1234567890ABCDEF" > file2.txt
	touch emptyfile.txt
	head -c 64 /bin/ls > binary_test.bin
	yes "A" | head -c 1024 > longfile.txt
	echo -n "aaaabbbb" > a1.txt
	echo -n "ccccdddd" > a2.txt
	echo -n "1234567890abcdef" > exact16.txt
	echo -n "1234567890abcde" > size15.txt
	head -c 32 /dev/zero > allzeros.bin
	printf "\x01\x02\x03\x04\x05\x06\x07\x08\x0B\x0C\x0E\x0F" > nonprintables.bin

	# Run tests
	run_test "Test 1: Basic file" \
		"./$assignment/hexdump -C file1.txt 2>&1" \
		"hexdump -C file1.txt 2>&1"

	run_test "Test 2: Multiple files" \
		"./$assignment/hexdump -C file1.txt file2.txt 2>&1" \
		"hexdump -C file1.txt file2.txt 2>&1"

	run_test "Test 3: Nonexistent file" \
		"./$assignment/hexdump -C nonexistent.txt 2>&1" \
		"hexdump -C nonexistent.txt 2>&1"

	run_test "Test 4: Empty file" \
		"./$assignment/hexdump -C emptyfile.txt 2>&1" \
		"hexdump -C emptyfile.txt 2>&1"

	run_test "Test 5: Stdin input" \
		"echo 'stdin test' | ./$assignment/hexdump -C" \
		"echo 'stdin test' | hexdump -C"

	run_test "Test 6: Directory input" \
		"./$assignment/hexdump -C . 2>&1" \
		"hexdump -C . 2>&1"

	run_test "Test 7: Binary file" \
		"./$assignment/hexdump -C binary_test.bin 2>&1" \
		"hexdump -C binary_test.bin 2>&1"

	run_test "Test 8: No arguments (stdin)" \
		"echo 'input' | ./$assignment/hexdump -C" \
		"echo 'input' | hexdump -C"

	run_test "Test 9: Long file (1024 bytes)" \
		"./$assignment/hexdump -C longfile.txt 2>&1" \
		"hexdump -C longfile.txt 2>&1"

	run_test "Test 10: Similar content files" \
		"./$assignment/hexdump -C a1.txt a2.txt 2>&1" \
		"hexdump -C a1.txt a2.txt 2>&1"
		
	run_test "Test 11: Mixed existing and missing files" \
		"./$assignment/hexdump -C a1.txt missing1.txt a2.txt missing2.txt 2>&1" \
		"hexdump -C a1.txt missing1.txt a2.txt missing2.txt 2>&1"
	
	run_test "Test 12: File exactly 16 bytes" \
		"./$assignment/hexdump -C exact16.txt 2>&1" \
		"hexdump -C exact16.txt 2>&1"

	run_test "Test 13: File size not multiple of 16" \
		"./$assignment/hexdump -C size15.txt 2>&1" \
		"hexdump -C size15.txt 2>&1"

	run_test "Test 14: All non-printable bytes" \
		"./$assignment/hexdump -C nonprintables.bin 2>&1" \
		"hexdump -C nonprintables.bin 2>&1"

	run_test "Test 15: Stdin from cat multiple files" \
		"cat a1.txt a2.txt | ./$assignment/hexdump -C" \
		"cat a1.txt a2.txt | hexdump -C"

	# Cleanup
	rm -f file1.txt file2.txt emptyfile.txt binary_test.bin longfile.txt \
		a1.txt a2.txt exact16.txt size15.txt allzeros.bin nonprintables.bin

	if [ $score_false = 0 ]; then
		printf "${BG_GREEN}${BLACK}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		exit 0
	else
		printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		exit 16
	fi
}

main
