readonly MINI_PATH="$(dirname "$(realpath "$0")")"
function append_line_if_exists {
    # https://stackoverflow.com/a/3557165
    grep -qsxF "$1" "$2" ||
        echo "$1" >>"$2"
}
read -r -d '' MINI_ALIAS_SCRIPT <<EOM
alias mini='${MINI_PATH}/mini-moul.sh'
EOM
read -r -d '' ALIAS_FILE_SCRIPT <<EOM
if [ -f ~/.aliases ]; then
    source ~/.aliases
fi
EOM
append_line_if_exists "$MINI_ALIAS_SCRIPT" ~/.aliases
case "$SHELL" in
*/zsh)
    append_line_if_exists "$ALIAS_FILE_SCRIPT" ~/.zshrc
    ;;
*/bash)
    append_line_if_exists "$ALIAS_FILE_SCRIPT" ~/.bash_aliases
    ;;
*)
    printf 'Unknown shell, failed to install.\n' >&2
    exit 1
    ;;
esac
printf 'Run `source ~/.aliases` or restart the terminal to proceed.\n'
