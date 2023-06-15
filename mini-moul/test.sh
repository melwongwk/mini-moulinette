source config.sh

#utils
ex_ind=0
index2=0

#variables
marks=0
questions=0
dirname_found=0
break_score=0
score_false=0
available_assignments=()
result=""
readonly SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)
readonly PROJECT_DIR="$SCRIPT_DIR/.."

main() {
    pushd tests >/dev/null
    start_time=$(date +%s)
    for dir in ./*; do
        dirname="$(basename "$dir")"
        available_assignments+=($dirname)

        if [ -d "$dir" ] && [ "$dirname" == "$1" ]; then
            dirname_found=1
            print_header
            printf "${GREEN} Generating test for ${1}...\n${DEFAULT}"
            space
            dirname_found=1
            ex_ind=0
            pushd $dir >/dev/null
            for assignment in ./*; do
                ((questions++))
                assignment_id="$(basename "$assignment")"
                assignment_name=$(ls $assignment/*.c | head -n 1)
                assignment_name=$(basename $assignment_name)
                assignment_name=${assignment_name%.c}

                if [ -f $assignment/test.sh ]; then
                    bash $assignment/test.sh $PROJECT_DIR $assignment
                    case $? in
                    0)
                        update_result "OK"
                        ;;
                    4)
                        update_result "EF"
                        ;;
                    8)
                        update_result "NE"
                        ;;
                    12)
                        update_result "CE"
                        ;;
                    16)
                        update_result "KO"
                        ;;
                    *)
                        printf "${RED}    $assignment_name test exit with unknown code ($?).${DEFAULT}\n"
                        update_result "??"
                        ;;
                    esac
                    space
                elif [ ! -d "$PROJECT_DIR/$assignment" ]; then
                    printf "${RED}    $assignment_name is not submitted.${DEFAULT}\n"
                    printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
                    space

                    update_result "EF"
                elif ! run_norminette $PROJECT_DIR $assignment; then
                    printf "${RED}    $assignment_name failed norminette.${DEFAULT}\n"
                    printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
                    space

                    update_result "NE"
                elif ! (
                    ccw -o test1 $(ls $assignment/*.c | head -n 1) $PROJECT_DIR/$assignment/*.c &>test.log ||
                        ccw -o test1 $(ls $assignment/*.c | head -n 1) &>test.log
                ); then
                    cat test.log
                    printf "${RED}    $assignment_name cannot compile.${DEFAULT}\n"
                    printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
                    space

                    update_result "KO"
                else
                    cat test.log
                    rm test1

                    score_false=0
                    if [ -d "$assignment" ]; then
                        index2=0

                        for test in $assignment/*.c; do
                            test_name="$(basename "$test")"
                            ((index2++))
                            if (
                                cc -o ${test%.c} $test $PROJECT_DIR/$assignment/*.c 2>/dev/null ||
                                    cc -o ${test%.c} $test 2>/dev/null
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
                            update_result "OK"
                        else
                            printf "${BG_RED}${BOLD} FAIL ${DEFAULT}${PURPLE} $assignment_id/${DEFAULT}$assignment_name\n"
                            update_result "KO"
                        fi
                        space
                    else
                        printf "${RED}    $assignment_name test does not exist.${DEFAULT}\n"
                    fi
                fi
                ((ex_ind++))
            done
            popd >/dev/null
            break
        fi
    done
    popd >/dev/null

    if [ $dirname_found = 0 ]; then
        printf "${RED}Sorry. Tests for $1 isn't available yet. Consider contributing at Github.${DEFAULT}\n"
        printf "Available assignment tests: ${PURPLE}${available_assignments[*]}${DEFAULT}\n"
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

space() {
    printf "\n"
}

update_result() {
    if [ $ex_ind -gt 0 ]; then
        result+=", "
    fi
    if [[ $1 = "OK" ]]; then
        if [ $break_score = 0 ]; then
            ((marks++))
        fi
        result+=${GREEN}
    else
        break_score=1
        result+=${RED}
    fi
    result+="$assignment_id: "
    result+=$1
    result+=${DEFAULT}
}

print_footer() {
    printf "${PURPLE}-----------------------------------${DEFAULT}\n"
    space
    PERCENT=$((100 * marks / questions))
    printf "Result:        ${result}\n"
    if [ $PERCENT -ge 50 ]; then
        printf "Final score:   ""${GREEN}$(echo $PERCENT)/100${DEFAULT}\n"
        printf "Status:        ""${GREEN}passed${DEFAULT}\n"
    else
        printf "Final score:   ""${RED}$(echo $PERCENT)/100${DEFAULT}\n"
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

if [ "${1}" = "" ]; then
    printf "Please select an assignment. e.g. './test.sh C01'\n"
    exit 1
fi
main "$@"
printf "$DEFAULT"
exit
