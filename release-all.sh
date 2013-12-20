#!/bin/bash
DIR=`pwd`
GLV=`./stats.pl -v` # Global version
TMP=$DIR/rainbrurpg-$GLV

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
      check_status "$?" "Autoreconf failed for '$PWD'"
      ./configure >> $LOG
      check_status "$?" "./configure failed for '$PWD'"
      make dist-bzip2 >> $LOG
      check_status "$?" "make dist-bzip2 failed for '$PWD'"
      mv *.tar.bz2 $TMP
done

# Decompress all archives in temp dir
cd $TMP
archives=`ls`
for i in $archives; do
    echo "Decompressing $i"
    tar -xf $i && rm -fr $i
    rm -fr $i
done

# Create a README file
echo "Creating README file"
cat <<EOF > README
This is a complete archive of RainbruRPG $GLV. To be
able to build it, you must compile and install sub-projects in this order :

EOF

for i in $SUBP; do
    echo "  $i" >> README
done

cat <<EOF >> README

To fully compile and install a package, you should run
  autoreconf
  ./configure
  make
  make install (as root or with sudo)

For more informations, please see individual package's INSTALL file.
EOF

# Create final archive
cd $DIR
tar -cjf $TMP-src.tar.bz2 rainbrurpg-$GLV/

