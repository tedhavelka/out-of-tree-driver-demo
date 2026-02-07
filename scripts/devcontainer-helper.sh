#!/bin/bash
set -e

cd "$(dirname $0)/.."

# Ensure docker cache directory exists
DIR=$(pwd)/docker_cache
if [ ! -d "$DIR" ]; then
    mkdir -p "$DIR"
    echo "Directory $DIR created."
fi

devcontainer up --workspace-folder .

exit $?
