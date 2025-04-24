source ../../config.sh

readonly PROJECT_DIR=$1
readonly assignment=$2
readonly assignment_id="$(basename "$assignment")"
readonly assignment_name="Makefile"
readonly files=("Makefile")
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

#	if ! run_norminette $PROJECT_DIR/$assignment; then
#		printf "${RED}    $assignment_name failed norminette.${DEFAULT}\n"
#		printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
#		exit 8
#	fi

	cd $assignment

	# Run basic make
	if ! (make > /dev/null); then
		cd ..
		printf "${RED}    $assignment_name cannot be executed.${DEFAULT}\n"
		printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		exit 16
	else
		echo "make passed ✅"
	fi

	# Check libft.a exists
	if [ ! -f libft.a ]; then
		cd ..
		printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		exit 16
	fi

	# Test make clean
	make clean > /dev/null
	if ls srcs/*.o >/dev/null 2>&1; then
		printf "${RED}    clean rule didn't remove object files.${DEFAULT}\n"
		exit 20
	else
		echo "make clean passed ✅"
	fi

	# Test make fclean
	make fclean > /dev/null
	if [ -f libft.a ]; then
		printf "${RED}    fclean rule didn't remove libft.a.${DEFAULT}\n"
		exit 21
	else
		echo "make fclean passed ✅"
	fi

	# Test make re
	make re > /dev/null
	if [ ! -f libft.a ]; then
		printf "${RED}    re didn't produce libft.a.${DEFAULT}\n"
		exit 23
	else
		echo "make re passed ✅"
	fi

	rm libft.a

	printf "${BG_GREEN}${BLACK}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
	cd ..
	exit 0
}

main
