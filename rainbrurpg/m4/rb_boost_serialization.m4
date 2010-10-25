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

dnl Checks for the Boost.Serialization lib and headers
dnl
dnl
AC_DEFUN([RB_CHECK_BOOST_SERIALIZATION],
[
  if test $rb_cross_compil_host == "win32"
  then	
    echo "Adding Boost.Serialization flags for "mingw32msvc""
    CFLAGS="$CFLAGS -I$rb_cross_compil_prefix/include/"
    LDFLAGS="$LDFLAGS -lboost_serialization-1_34_1$DLL_EXT"
  else
    AC_CHECK_LIB(boost_serialization, main, [], [
      echo "Error! You need to have Boost.Serialization installed."
      exit -1
    ])
    AC_CHECK_HEADER([boost/serialization/serialization.hpp], [], [
      echo "Error! Cannot find the Boost.Serialization headers."
      exit -1
    ])
  fi
])
