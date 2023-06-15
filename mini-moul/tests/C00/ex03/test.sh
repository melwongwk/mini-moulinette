source ~/mini-moulinette/mini-moul/config.sh

readonly PROJECT_DIR=$1
readonly assignment=$2
readonly assignment_id="$(basename "$assignment")"
readonly assignment_name="ft_print_numbers"
readonly files=("$PROJECT_DIR/$assignment/ft_print_numbers.c")

main() {
    for file in ${files[@]}; do
        if [ ! -f "$file" ]; then
            printf "${RED}    $(basename $file) is not submitted.${DEFAULT}\n"
            printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
            exit 4
        fi
    done
    if ! run_norminette $PROJECT_DIR $files -R CheckForbiddenSourceHeader; then
        printf "${RED}    $assignment_name failed norminette.${DEFAULT}\n"
        printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
        exit 8
    elif ! (ccw -o test1 $assignment/main.c $files); then
        printf "${RED}    $assignment_name cannot compile.${DEFAULT}\n"
        printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
        exit 12
    else
        rm test1

        score_false=0
        index2=0
        for test in $assignment/*.c; do
            test_name="$(basename "$test")"
            ((index2++))
            checks=$((checks + 1))
            if (
                ccw -o ${test%.c} $test $files 2>/dev/null ||
                    ccw -o ${test%.c} $test 2>/dev/null
            ); then
                if ./${test%.c} = 0; then
                    printf "${GREEN}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
                else
                    printf "${RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name/$test_name${DEFAULT}\n"
                    score_false=1
                fi
                rm ${test%.c}
            else
                printf "    ""${GREY}[$(($index2 + 1))] $test_name ${RED}FAILED${DEFAULT}\n"
            fi
        done
        if [ $score_false = 0 ]; then
            printf "${BG_GREEN}${BLACK}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
            exit 0
        else
            printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
            exit 16
        fi
    fi
}

main
