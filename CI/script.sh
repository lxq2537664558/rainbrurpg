#!/bin/sh -e

# The '-e' flag in the shebang should make fail the script if
# an error occurs.

export LD_LIBRARY_PATH="/usr/local/lib:$LD_LIBRARY_PATH"
sudo ldconfig

# Trying to fix 'no member named 'max_align_t' in the global namespace'
if [ "$CXX" = "clang++" ]; then
    export CXXFLAGS="-stdlib=libc++"
#    export LDFLAGS="-fdefine-sized-deallocation"
fi

mkdir ./build
cd build
cmake ..
make
make check
