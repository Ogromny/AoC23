#!/bin/sh -e

if [ "$#" -lt 1 ]; then
    exit 0
fi

if command -v gcc; then
    CC="gcc"
elif command -v clang; then
    CC="clang"
elif command -v cproc; then
    CC="cproc"
fi

if [ -z "$CC" ]; then
    echo "no C compiler found"
    exit 1
fi

cd "$1"
gcc ./main.c -o main && ./main
