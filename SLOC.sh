#!/bin/sh
# A simple help script to compute total SLOC from all sub projects

DIR=`pwd`
SRCS="*/src"
TEMPFILE="src-temp-file-for-sloccount"

for i in $SRCS; do
    DIRNAME="$DIR/$i"
    sloccount $DIRNAME | grep '(SLOC)' |grep -o '[0-9]*' >> $TEMPFILE
done

echo -n "Total SLOCcount : "
awk '{s+=$1} END {printf "%d",s}' src-temp-file-for-sloccount
echo " (generated using David A. Wheeler's 'SLOCCount'.)"
rm $TEMPFILE