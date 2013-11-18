#!/bin/sh
DIR=`pwd`

# Please keep this list in the compilation order
SUBP="logger client services network meta server website"

for i in $SUBP; do
    DIRNAME=$DIR/$i
    LOG=log-release-all-$i.log
    cd $DIRNAME
    echo -n "Creating "
    pwd

      autoreconf > $LOG
      ./configure >> $LOG
      make dist-bzip2 >> $LOG

done