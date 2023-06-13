source config.sh

#utils
index=0
index2=0
assignment_data=NULL
test_data=NULL
test_error=NULL
test_name=NULL

#variables
checks=0
passed=0
marks=0
questions=0
dirname_found=0
break_score=0
score_false=0
available_assignments=""
result=""
SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)
PROJECT_DIR="$SCRIPT_DIR/.."
dirname_found=0

main() {
    pushd tests >/dev/null
    start_time=$(date +%s)
    for dir in ./*; do
        dirname="$(basename "$dir")"
        available_assignments+="$dirname "

        if [ -d "$dir" ] && [ "$dirname" == "$1" ]; then
            dirname_found=1
            print_header
            printf "${GREEN} Generating test for ${1}...\n${DEFAULT}"
            space
            dirname_found=1
            index=0
            pushd $dir >/dev/null
            for assignment in ./*; do
                questions=$((questions + 1))
                score_false=0
                assignment_name="$(basename "$assignment")"
                test_name="$(ls $assignment/*.c | head -n 1)"
                test_name="$(basename "$test_name")"

                if [ ! -d "$PROJECT_DIR/$assignment" ]; then
                    break_score=1
                    checks=$((checks + 1))
                    printf "${RED}    $test_name is not submitted.${DEFAULT}\n"
                    printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_name/${DEFAULT}$test_name\n"
                    space

                    if [ $index -gt 0 ]; then
                        result+=", "
                    fi
                    result+="${RED}$assignment_name: EF${DEFAULT}"
                elif ! run_norminette $(normpath $PROJECT_DIR/$assignment); then
                    break_score=1
                    checks=$((checks + 1))
                    printf "${RED}    $test_name failed norminette.${DEFAULT}\n"
                    printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_name/${DEFAULT}$test_name\n"
                    space

                    if [ $index -gt 0 ]; then
                        result+=", "
                    fi
                    result+="${RED}$assignment_name: NE${DEFAULT}"
                elif ! (
                    cc -Wall -Werror -Wextra -o test1 $(ls $assignment/*.c | head -n 1) $(ls $PROJECT_DIR/$assignment/*.c) &>test.log ||
                        cc -Wall -Werror -Wextra -o test1 $(ls $assignment/*.c | head -n 1) &>test.log
                ); then
                    cat test.log
                    break_score=1
                    checks=$((checks + 1))
                    printf "${RED}    $test_name cannot compile.${DEFAULT}\n"
                    printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_name/${DEFAULT}$test_name\n"
                    space

                    if [ $index -gt 0 ]; then
                        result+=", "
                    fi
                    result+="${RED}$assignment_name: KO${DEFAULT}"
                else
                    cat test.log
                    rm test1
                    checks=$((checks + 1))
                    passed=$((passed + 1))

                    if [ -d "$assignment" ]; then
                        index2=0

                        for test in $assignment/*.c; do
                            ((index2++))
                            checks=$((checks + 1))
                            if (
                                cc -o ${test%.c} $test $(ls $PROJECT_DIR/$assignment/*.c) 2>/dev/null ||
                                    cc -o ${test%.c} $test 2>/dev/null
                            ); then
                                if ./${test%.c} = 0; then
                                    passed=$((passed + 1))
                                else
                                    break_score=1
                                    score_false=1
                                fi
                                rm ${test%.c}
                            else
                                printf "    ""${GREY}[$(($index2 + 1))] $test_error ${RED}FAILED${DEFAULT}\n"
                            fi
                        done
                        print_test_result
                        space
                    else
                        printf "${RED}    $assignment_name does not exist.${DEFAULT}\n"
                    fi
                fi
                ((index++))
            done
            popd >/dev/null
            break
        fi
    done
    popd >/dev/null

    if [ $dirname_found = 0 ]; then
        printf "${RED}Sorry. Tests for $1 isn't available yet. Consider contributing at Github.${DEFAULT}\n"
        printf "Available assignment tests: ${PURPLE}$available_assignments${DEFAULT}\n"
        exit 1
    fi
    print_footer
}

print_header() {
    printf "${PINK}"
    space
    printf " ███▄ ▄███▓ ██▓ ███▄    █  ██▓\n"
    printf "▓██▒▀█▀ ██▒▓██▒ ██ ▀█   █ ▓██▒\n"
    printf "▓██    ▓██░▒██▒▓██  ▀█ ██▒▒██▒\n"
    printf "▒██    ▒██ ░██░▓██▒  ▐▌██▒░██░\n"
    printf "▒██▒   ░██▒░██░▒██░   ▓██░░██░\n"
    printf "░ ▒░   ░  ░░▓  ░ ▒░   ▒ ▒ ░▓  \n"
    printf "░  ░      ░ ▒ ░░ ░░   ░ ▒░ ▒ ░\n"
    printf "░      ░    ▒ ░   ░   ░ ░  ▒ ░\n"
    printf "       ░    ░           ░  ░  \n"
    printf "${DEFAULT}"
    printf "${BLUE}Mini moulinette ${DEFAULT}version 0.1.21 27 Feb 2023.\n"
    space
}

print_collected_files() {
    printf "Collected files:\n"
    ls ../* | grep -v "../41test:*" | grep -v "../41test" | column
}

space() {
    printf "\n"
}

print_test_result() {
    if [ $index -gt 0 ]; then
        result+=", "
    fi
    if [ $score_false = 0 ]; then
        result+="${GREEN}$assignment_name: OK${DEFAULT}"
        printf "${BG_GREEN}${BLACK}${BOLD} PASS ${DEFAULT}${PURPLE} $assignment_name/${DEFAULT}$test_name\n"
    else
        result+="${RED}$assignment_name: KO${DEFAULT}"
        printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_name/${DEFAULT}$test_name\n"
    fi
    if [ $break_score = 0 ]; then
        marks=$((marks + 1))
    fi
}

print_footer() {
    printf "${PURPLE}-----------------------------------${DEFAULT}\n"
    space
    PERCENT=$((100 * marks / questions))
    #printf "Total checks:  ""${GREEN}${passed} passed  ${DEFAULT} ""${checks} total"
    printf "Result:        ${result}\n"
    if [ $PERCENT -ge 50 ]; then
        printf "Final score:   ""${GREEN}$(echo $PERCENT | bc)/100${DEFAULT}\n"
        printf "Status:        ""${GREEN}passed${DEFAULT}\n"
    else
        printf "Final score:   ""${RED}$(echo $PERCENT | bc)/100${DEFAULT}\n"
        printf "Status:        ""${RED}FAILED${DEFAULT}\n"
    fi
    end_time=$(date +%s)
    elapsed_time=$(expr $end_time - $start_time)
    printf "${GREY}Test completed. ${PINK}Total elapsed time: ${elapsed_time}s${DEFAULT}.\n"
    printf "${BLUE}Mini moulinette is updated daily. Please remember to git pull today!\n${DEFAULT}"
    space
}

normpath() {
    # Remove all /./ sequences.
    local path=${1//\/.\//\/}

    # Remove dir/.. sequences.
    while [[ $path =~ ([^/][^/]*/\.\./) ]]; do
        path=${path/${BASH_REMATCH[0]}/}
    done

    echo $path
}

run_norminette() {
    if command -v norminette &>/dev/null; then
        norminette "$@"
        return $?
    else
        echo "norminette not found, skipping norminette checks"
    fi
    return 0
}

if [ "${1}" = "" ]; then
    printf "Please select an assignment. e.g. './test.sh C01'\n"
    exit 1
fi
main "$@"
printf "$DEFAULT"
exit
