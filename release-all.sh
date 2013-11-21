#!/bin/bash
DIR=`pwd`
TMP=$DIR/release-all.tmp

# Please keep this list in the compilation order
SUBP="logger client services " #network meta server website"

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

rm -fr $TMP && mkdir $TMP

# Create tar-bzip2 archive of all subprojects
for i in $SUBP; do
    DIRNAME=$DIR/$i
    LOG=$DIR/log-release-all-$i.log
    cd $DIRNAME
    PWD=$i
      echo "Creating $PWD"
      rm -f *.tar.bz2 $LOG 
      autoreconf > $LOG 2> /dev/null
      check_status "$?" "Autoreconf failed for $PWD failed"
      ./configure >> $LOG
      check_status "$?" "./configure failed for $PWD failed"
      make dist-bzip2 >> $LOG
      check_status "$?" "make dist-bzip2 failed for $PWD failed"
      mv *.tar.bz2 $TMP
done

# Decompress all archives in temp dir
cd $TMP
archives=`ls`
for i in $archives; do
    echo "Decompressing $i"
    tar -xf $i && rm -fr $i
    
done