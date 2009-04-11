#
#  Copyright 2006-2008 Jerome PASQUIER
#
#  This file is part of RainbruRPG.
#
#  RainbruRPG is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  RainbruRPG is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with RainbruRPG; if not, write to the Free Software
#  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
#  02110-1301  USA
#
#

# Do not call this file directly, please use library/make_dll.sh instead.

#
# Modifications :
# - 29 oct 2008 : echoing the create_dll() command line.
# - 09 oct 2008 : Starting implementation
#

#!/bin/sh 

# Global var
IS_INITIALIZED=0

#
# Show an error message in red
#
# Parameter :
#   $1 The error message
#
error(){
    echo -en "\\033[1;31m"
    echo -n "Error : $1"
    echo -en "\\033[m\\n"
}

#
# Show a step name in green
#
# Parameter :
#   $1 The step name
#
step(){
    echo -en "\\033[1;32m"
    echo -n "$1"
    echo -en "\\033[m\\n"
}

#
# initialize the script
#
# 
#
init(){
    step "init() called"
    DLLWRAP=i586-mingw32msvc-dllwrap
    DLLTOOL=i586-mingw32msvc-dlltool
    LD=i586-mingw32msvc-ld
    CXX=i586-mingw32msvc-g++
    GCC=i586-mingw32msvc-gcc
    IS_INITIALIZED=1
    GLOBAL_LDFLAGS="-L/usr/lib/gcc/i586-mingw32msvc/4.2.1-sjlj/"
    GLOBAL_LDFLAGS=$GLOBAL_LDFLAGS" -lmsvcrt -lmingwex -lstdc++ -lcrtdll -lgcc -lkernel32"
    GLOBAL_LDFLAGS=$GLOBAL_LDFLAGS" -lmingw32 -laclui"
    GLOBAL_LDFLAGS=$GLOBAL_LDFLAGS" -lmsvcr80 -lntdll"
}

#
# Check if this script has been initialized and exit if not
#
check_initialized(){
    if [ $IS_INITIALIZED != 1 ]; then
	error "create_dll.sh is not initialized !"
	exit 1
    fi
}

#
# Get the library name and set it in the LIB_NAME variable
#
# The library name is taken from the lib*.a file. Example : 
# If I found a libfoo.a, the library name is foo.
#
get_library_name(){
    check_initialized
    step "Check for library canonical name"
    echo "  library name is "$LIB_NAME
}

#
# Get the object list and set it in the OBJ_LIST variable
#
# The object list is taken from the lib$LIB_NAME.a archive.
#
get_object_list(){
    check_initialized
    step "Get object list"
    OBJ_LIST=(`ar t lib$LIB_NAME.a`)
    echo "  object list contains "${#OBJ_LIST[*]}" objects"
}

#
# Uses dllwrap tool to create the shared library
#
create_dll(){
    check_initialized
    step "Creating shared library(.libs/$LIB_NAME.dll)"

# ============== OLD COMMAND
#    echo "  Command line is '$DLLWRAP --output-def $LIB_NAME.def --driver-name=$CXX -o $LIB_NAME.dll ${OBJ_LIST[@]:0} $LIBADD'"
#    $DLLWRAP --output-def $LIB_NAME.def --driver-name=$CXX \
#	-o $LIB_NAME.dll ${OBJ_LIST[@]:0} $LIBADD
# ============== OLD COMMAND

#echo $LD -shared --output-def $LIB_NAME.def --out-implib $LIB_NAME.dll.a -o $LIB_NAME.dll ${OBJ_LIST[@]:0} $LIBADD $GLOBAL_LDFLAGS

  #  $LD -shared --output-def $LIB_NAME.def --out-implib $LIB_NAME.dll.a -o $LIB_NAME.dll ${OBJ_LIST[@]:0} $LIBADD $GLOBAL_LDFLAGS

$CXX -Wall -shared ${OBJ_LIST[@]:0} -o $LIB_NAME.dll -Wl,--out-implib,$LIB_NAME.a $LIBADD

}

#
# Run the scipt
#
# param $1 The LIBADD parameter (-l -L etc...)
#
run(){
    LIB_NAME=$1
    LIBADD=$2

    init
    cd .libs
    get_library_name
    get_object_list
    create_dll
}