#!/bin/sh   

list="logger network services meta client server"   
for element in $list    
do   
    cd $element
    autoreconf
    ./configure
    make
    sudo make install
    cd ..
done
