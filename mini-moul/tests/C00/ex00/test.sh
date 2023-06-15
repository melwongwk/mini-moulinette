source ~/mini-moulinette/mini-moul/config.sh

PROJECT_DIR=$1
assignment=$2
assignment_name="$(basename "$assignment")"
test_name="$(ls $assignment/*.c | head -n 1)"
test_name="$(basename "$test_name")"

main() {
    if [ ! -f "$PROJECT_DIR/$assignment/ft_putchar.c" ]; then
        printf "${RED}    $test_name is not submitted.${DEFAULT}\n"
        printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_name/${DEFAULT}$test_name\n"
        exit 4
    elif ! run_norminette; then
        printf "${RED}    $test_name failed norminette.${DEFAULT}\n"
        printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_name/${DEFAULT}$test_name\n"
        exit 8
    elif ! (cc -Wall -Werror -Wextra -o test1 $assignment/main.c $PROJECT_DIR/$assignment/ft_putchar.c); then
        printf "${RED}    $test_name cannot compile.${DEFAULT}\n"
        printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_name/${DEFAULT}$test_name\n"
        exit 12
    else
        rm test1

        score_false=0
        index2=0

        for test in $assignment/*.c; do
            ((index2++))
            checks=$((checks + 1))
            if (
                cc -o ${test%.c} $test $PROJECT_DIR/$assignment/*.c 2>/dev/null ||
                    cc -o ${test%.c} $test 2>/dev/null
            ); then
                if ./${test%.c} = 0; then
                    true
                else
                    score_false=1
                fi
                rm ${test%.c}
            else
                printf "    ""${GREY}[$(($index2 + 1))] $test_error ${RED}FAILED${DEFAULT}\n"
            fi
        done
        if [ $score_false = 0 ]; then
            printf "${BG_GREEN}${BLACK}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_name/${DEFAULT}$test_name\n"
            exit 0
        else
            printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_name/${DEFAULT}$test_name\n"
            exit 16
        fi
    fi
}

run_norminette() {
    pushd $PROJECT_DIR >>/dev/null
    if command -v norminette &>/dev/null; then
        norminette $assignment
    else
        echo "norminette not found, skipping norminette checks"
    fi
    popd >>/dev/null
    return $?
}

main
