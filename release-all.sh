#!/bin/bash
DIR=`pwd`

# Please keep this list in the compilation order
SUBP="logger client services network meta server website"

# Check the exit status of a command
#   $1 the quoted exit status of the command to be tested (i.e. "$?")
#   $2 the message to be printed if the ommand failed
function check_status
{
    if [ "$1" != "0" ]; then
	echo $2
	exit 1
    fi
}

for i in $SUBP; do
    DIRNAME=$DIR/$i
    LOG=log-release-all-$i.log
    cd $DIRNAME
    PWD=$i
      echo "Creating $PWD"
      rm -f *.tar.bz2
      autoreconf > $LOG
      check_status "$?" "Autoreconf failed for $PWD failed"
      ./configure >> $LOG
      check_status "$?" "./configure failed for $PWD failed"
      make dist-bzip2 >> $LOG
      check_status "$?" "make dist-bzip2 failed for $PWD failed"
done