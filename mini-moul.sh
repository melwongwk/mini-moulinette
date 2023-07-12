source ~/.aliases
readonly MINI_PATH="$(dirname "$(realpath "$(alias mini | sed -E "s/^alias mini='(.*)'$/\1/")")")"
source $MINI_PATH/mini-moul/config.sh

trap handle_sigint SIGINT

function clean_up {
  rm -R ./mini-moul
}

function handle_sigint {
  echo "${RED}Script aborted by user. Cleaning up..."
  clean_up
  echo ""
  echo "${GREEN}Cleaning process done.${DEFAULT}"
  exit 130
}

if cp -Rf $MINI_PATH/mini-moul .; then
  ./mini-moul/test.sh "$1"
  clean_up
fi
