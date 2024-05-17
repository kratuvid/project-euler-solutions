#!/bin/sh

mkdir build &>/dev/null

set -e

exe="build/$(basename -s .cpp "$1")"
if [ ! -e "$exe" ] || [ "$1" -nt "$exe" ]; then
    g++ "$1" -o "$exe"
fi
./"$exe" ${@:2}
