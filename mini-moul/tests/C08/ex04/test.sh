source ../../config.sh

readonly PROJECT_DIR=$1
readonly assignment=$2
readonly assignment_id="$(basename "$assignment")"
readonly assignment_name="ft_strs_to_tab.c"
readonly files=("ft_strs_to_tab.c")
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
	elif ! (ccw -o test1 $assignment/test.c ${files_dir[@]}); then
		printf "${RED}    $assignment_name cannot compile.${DEFAULT}\n"
		printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		exit 12
	else
		./test1
		rm test1
		printf "${BG_GREEN}${BLACK}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
		exit 0
	fi
}

main
