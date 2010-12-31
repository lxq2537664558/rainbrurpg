dnl Copyright 2006-2011 Jerome PASQUIER
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

dnl Define the all Option 
dnl
dnl Provides the --enable-all to enable all the 'enable like'
dnl ./configure script options
dnl
dnl If we set this options, we should set 'build_tests' to 'yes' to
dnl enable CPPUNIT search
dnl
dnl This option is not used anymore
dnl
AC_DEFUN([RB_OPTION_ALL],
[
  AC_ARG_ENABLE(all, AC_HELP_STRING([--enable-all],
    [Build the whole package. It is a convenience option that build
	the client, the server, the editor and the tools.
       (default=no)]),
    [build_all=$enableval], 
    [build_all=no])

  AC_MSG_CHECKING([if we should build RainbruRPG-all])

  case $build_all in
    yes)
      RB_CHECK_LIBSLANG
      all=true
      build_tests=yes
      AC_MSG_RESULT(yes)
      AC_DEFINE(BUILD_SERVER)
      AC_DEFINE(BUILD_EDITOR)
      ;;
    *)
      all=false
      AC_MSG_RESULT(no)
      ;;
  esac
  AM_CONDITIONAL([RB_OPTION_ALL_FLAGS], [test x$all = xtrue])
  AM_CONDITIONAL([BUILD_LIB_DESIGN], [test x$all = xtrue])
])
