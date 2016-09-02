#!/bin/sh -e

# The '-e' flag in the shebang should make fail the script if
# an error occurs.

export LD_LIBRARY_PATH="/usr/local/lib:$LD_LIBRARY_PATH"
sudo ldconfig

mkdir ./build
cd build
cmake ..
make
make check
