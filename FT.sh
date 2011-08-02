#!/bin/sh
# -*- mode: shell-script -*-
#
# Get File Time for all */ROADMAP files (DOES NOT WORK)
#

DIR=`pwd`
FILES="*/ROADMAP"
ORGINSTALL="/usr/share/emacs/site-lisp/org-mode/org-install.el"
TEMPFILE="roadmap-temp-file-for-sum"

for i in $FILES; do
    FILENAME="$DIR/$i"
    cat $FILENAME >> $TEMPFILE
done


emacs -Q --batch -l ft.el |grep 'Total'

rm $TEMPFILE