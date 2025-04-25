source ../../config.sh

readonly PROJECT_DIR=$1
readonly assignment=$2
readonly assignment_id="$(basename "$assignment")"
readonly assignment_name="display_file"

main() {
	# Copy source files
	cp $PROJECT_DIR/$assignment/* $assignment

	# Run norminette and suppress output if failed
	if ! run_norminette $PROJECT_DIR/$assignment; then
		printf "${RED}    $assignment_name failed norminette.${DEFAULT}\n"
		printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		exit 8
	fi

	# Run make silently
	if ! (cd $assignment && make -s clean && make -s && make -s fclean && make -s && make -s clean); then
		printf "${RED}    $assignment_name cannot be make.${DEFAULT}\n"
		printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		exit 12
	fi

	# Check if binary exists
	if [ ! -f "$assignment/ft_display_file" ]; then
		printf "${RED}    $assignment_name binary not found.${DEFAULT}\n"
		printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		exit 16
	fi
	
	# Initialize score flag
	score_false=0

	# Test 1: File content
	dd if=/dev/urandom of=test.dat bs=1M count=2 &>/dev/null
	$assignment/ft_display_file test.dat > output.dat
	if cmp -s output.dat test.dat; then
		printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 1: File content displayed correctly.${DEFAULT}\n"
	else
		printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 1: File content mismatch.${DEFAULT}\n"
		score_false=1
	fi

	# Test 2: File name missing
	output=$($assignment/ft_display_file 2>&1)
	if diff -U3 <(echo "$output") <(echo "File name missing."); then
		printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 2: Error for missing file name.${DEFAULT}\n"
	else
		printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 2: Error for missing file name.${DEFAULT}\n"
		score_false=1
	fi

	# Test 3: Too many arguments
	output=$($assignment/ft_display_file a b 2>&1)
	if diff -U3 <(echo "$output") <(echo "Too many arguments."); then
		printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 3: Error for too many arguments.${DEFAULT}\n"
	else
		printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 3: Error for too many arguments.${DEFAULT}\n"
		score_false=1
	fi

	# Test 4: Cannot read file
	output=$($assignment/ft_display_file A 2>&1)
	if diff -U3 <(echo "$output") <(echo "Cannot read file."); then
		printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 4: Error for cannot read file.${DEFAULT}\n"
	else
		printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name Test 4: Error for cannot read file.${DEFAULT}\n"
		score_false=1
	fi

	# Cleanup
	if [ -f "./ft_display_file" ]; then
		rm ./ft_display_file
	fi

	if [ -f "./test.dat" ]; then
		rm ./test.dat
	fi
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
