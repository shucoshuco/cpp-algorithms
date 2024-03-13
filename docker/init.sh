#!/bin/bash

SOURCE=${BASH_SOURCE[0]}
while [ -L "$SOURCE" ]; do # resolve $SOURCE until the file is no longer a symlink
    DIR=$(cd -P "$(dirname "$SOURCE")" >/dev/null 2>&1 && pwd)
    SOURCE=$(readlink "$SOURCE")
    [[ $SOURCE != /* ]] && SOURCE=$DIR/$SOURCE # if $SOURCE was a relative symlink, we need to resolve it relative to the path where the symlink file was located
done
DIR=$(cd -P "$(dirname "$SOURCE")" >/dev/null 2>&1 && pwd)

PROJ_ROOT=/app
BUILD_DIR=/build

set -e
printf "\033c"
mkdir -p ${BUILD_DIR} # create if it doesn't exist
cd ${BUILD_DIR}
cmake -DDEBUG=1 /app
printf "\033c"

echo "Executed at $(TZ=Europe/Madrid date)"
make
printf "\033c"

echo "Executed at $(TZ=Europe/Madrid date)"
echo ""
echo "Running lib tests"
echo "--------------------------"
./lib_tests
echo ""
echo "Running app tests"
echo "--------------------------"
./tests
set +e
