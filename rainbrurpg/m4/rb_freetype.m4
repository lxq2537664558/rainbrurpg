dnl Copyright 2006-2010 Jerome PASQUIER
dnl 
dnl This file is part of RainbruRPG.
dnl
dnl RainbruRPG is free software; you can redistribute it and/or modify
dnl it under the terms of the GNU General Public License as published by
dnl the Free Software Foundation; either version 2 of the License, or
dnl (at your option) any later version.
dnl
dnl RainbruRPG is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl GNU General Public License for more details.
dnl
dnl You should have received a copy of the GNU General Public License
dnl along with RainbruRPG; if not, write to the Free Software
dnl Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
dnl 02110-1301  USA

dnl Check the Freetype library
dnl
dnl In GNU/Linux platform : It search for the freetype-config tool
dnl    and get the FREETYPE_LIBS and FREETYPE_CFLAGS from it.
dnl
dnl In Win32 cross-compilation: It simply add flags according to the 
dnl    cross-compil prefix passed to the RB_HANDLE_CROSS_COMPIL macro.
dnl
AC_DEFUN([RB_CHECK_FREETYPE],
[

  if test $rb_cross_compil_host == "win32"
  then	
    echo "Adding libfreetype flags for mingw32msvc"
    FREETYPE_CFLAGS="-I$rb_cross_compil_prefix/include/freetype/"
    FREETYPE_LIBS="-lfreetype6$DLL_EXT"
  else
    dnl Get the correct executable
    AC_PATH_TOOL(FREETYPE_CONFIG, freetype-config, -1)
    
    dnl Check for the precense of freetype-config
    if test $FREETYPE_CONFIG -eq -1
    then
      echo "Error! You need Freetype $1 installed. Cannot find the freetype-config tool."
      exit -1
    fi

    dnl check for version of freetype using freetype-config
    echo -n "checking if Freetype version is at least v$1... "
    FREETYPE_VERSION=`$FREETYPE_CONFIG --version`
    if test "${FREETYPE_VERSION:0:4}" == "$1"
    then 
      echo "yes"
    else
      echo "no"
      echo -n "Error! You need at least FreeType v$1. "
      echo "The version I found is $FREETYPE_VERSION."
      exit -1
    fi

    dnl Getting compiler flags
    FREETYPE_CFLAGS=`$FREETYPE_CONFIG --cflags`
    echo "$FREETYPE_CONFIG --cflags"
    FREETYPE_LIBS=`$FREETYPE_CONFIG --libs`
  fi

  AC_SUBST(FREETYPE_CFLAGS)
  AC_SUBST(FREETYPE_LIBS)
])
