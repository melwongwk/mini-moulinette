source ~/mini-moulinette/mini-moul/config.sh

trap handle_sigint SIGINT

function handle_sigint {
  echo "${RED}Script aborted by user. Cleaning up..."
  rm -R ../mini-moul
  echo ""
  echo "${GREEN}Cleaning process done.${DEFAULT}"
  exit 1
}

function help {
  cat <<EOF
Usage: mini [-h] [-d proj_dir] proj_id

Test runner for 42 piscine assignments that simulates moulinette.

Avaliable options:

-h        Print this help and exit
-d        Set project directory (default to .)
proj_id   Project ID (e.g. C02)
EOF
}

function main {
  if [ ! -d $1 ]; then
    echo "$1: No such file or directory" >&2
    exit 1
  fi
  pushd $1 >>/dev/null
  cp -R ~/mini-moulinette/mini-moul mini-moul
  cd mini-moul
  ./test.sh "$2"
  rm -R ../mini-moul
  popd >>/dev/null
  exit $?
}

OPTIONS=h,d:

test_dir=$(pwd)
while getopts $OPTIONS option; do
  case $option in
  h)
    help
    exit 0
    ;;
  d)
    test_dir=$OPTARG
    ;;
  \?)
    help
    exit 1
    ;;
  esac
done

args=(${@:OPTIND})

main $test_dir ${args[@]}
