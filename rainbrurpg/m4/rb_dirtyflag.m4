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

dnl
dnl Defines the --disable-dirty-flag configure option
dnl
dnl The dirty flag feature is part of OgreGui. It should speed up the drawing 
dnl Graphical User Interface elements by pre-computing their absolute position 
dnl and size. 
dnl
dnl The dirty flag feature is enabled by default, but it can be disabled by 
dnl passing the --disable-dirty-flag
dnl
AC_DEFUN([RB_OPTION_DIRTYFLAG],
[
  AC_MSG_CHECKING([if we should disable OgreGui's dirty flag])
  AC_ARG_ENABLE(dirty-flag, AC_HELP_STRING([--disable-dirty-flag],
    [Disable the use of GUI dirty flag and precomputing that should 
    speed up drawing. (default=no)]),
    [dirty_flag=$enableval],
    [dirty_flag=yes])

  case $dirty_flag in 
      yes) AC_DEFINE([RB_DIRTY_FLAG], [], [Defined if we should enable the 
	   pre-computing and dirty flag feature of OgreGui.])
           AC_DEFINE(RB_DIRTY_FLAG, 1)
	   AC_MSG_RESULT(no)
	   ;;   
      no)  AC_MSG_RESULT(yes)
	   ;;
      *)  AC_MSG_ERROR(bad value $dirty_flag for --disable-dirty-flag) ;;
   esac
])
