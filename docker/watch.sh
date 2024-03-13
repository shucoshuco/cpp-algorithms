#!/bin/bash

SOURCE=${BASH_SOURCE[0]}
while [ -L "$SOURCE" ]; do # resolve $SOURCE until the file is no longer a symlink
    DIR=$(cd -P "$(dirname "$SOURCE")" >/dev/null 2>&1 && pwd)
    SOURCE=$(readlink "$SOURCE")
    [[ $SOURCE != /* ]] && SOURCE=$DIR/$SOURCE # if $SOURCE was a relative symlink, we need to resolve it relative to the path where the symlink file was located
done
DIR=$(cd -P "$(dirname "$SOURCE")" >/dev/null 2>&1 && pwd)

PROJ_ROOT=/app

ls ${PROJ_ROOT}/CMakeLists.txt ${PROJ_ROOT}/lib/inc/* ${PROJ_ROOT}/lib/src/* ${PROJ_ROOT}/lib/tests/* ${PROJ_ROOT}/inc/* ${PROJ_ROOT}/src/* ${PROJ_ROOT}/tests/* | entr -nd "/init.sh"
