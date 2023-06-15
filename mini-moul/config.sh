#constants
readonly GREEN='\033[38;5;84m'
readonly RED='\033[38;5;197m'
readonly BLUE='\033[38;5;45m'
readonly PURPLE='\033[38;5;63m'
readonly PINK='\033[38;5;207m'
readonly BLACK='\033[38;5;0m'
readonly BG_GREEN='\033[48;5;84m'
readonly BG_RED='\033[48;5;197m'
readonly GREY='\033[38;5;8m'
readonly BOLD='\033[1m'
readonly DEFAULT='\033[0m'
readonly CHECKMARK='\xE2\x9C\x93'

#functions
run_norminette() {
    pushd $1 >>/dev/null
    if command -v norminette &>/dev/null; then
        norminette ${@:3} $2
    else
        echo "norminette not found, skipping norminette checks"
    fi
    popd >>/dev/null
    return $?
}

ccw() {
    cc -Wall -Werror -Wextra $@
    return $?
}
