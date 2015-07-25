#!/bin/sh -e

# The '-e' flag in the shebang should make fail the script if
# an error occurs.

export LD_LIBRARY_PATH="/usr/local/lib:$LD_LIBRARY_PATH"
sudo ldconfig

list="logger network services meta client server"   
for element in $list    
do   
    cd $element
    automake --add-missing
    autoreconf
    ./configure
    make
    sudo make install
    cd ..
done
