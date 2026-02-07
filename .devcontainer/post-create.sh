#!/bin/bash

set -e

complete_setup() {
    touch /workdir/setup_complete
}

is_setup_complete() {
    [ -f /workdir/setup_complete ]
}

setup() {
    if [ ! -d /workdir/.west ]; then
        west init -l
    else
        echo "West already initialized."
    fi

    echo "Adding extra modules and calling \`west\` to update SDK..."
    west config manifest.project-filter -- +nanopb
    west update
    west zephyr-export
    ./scripts/placeholder.sh
    complete_setup
}

# Skip if already initialized
if is_setup_complete; then
    echo "Setup already completed."
else
    setup
fi
