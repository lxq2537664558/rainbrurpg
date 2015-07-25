#!/bin/sh   

export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:/usr/local/lib"
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
