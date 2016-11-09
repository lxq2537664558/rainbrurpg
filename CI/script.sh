#!/bin/sh -e

# The '-e' flag in the shebang should make fail the script if
# an error occurs.

mkdir ./build
cd build
cmake ..
make
make check
