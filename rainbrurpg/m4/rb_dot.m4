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


AC_DEFUN([RB_CHECK_DOT],[
  AC_ARG_VAR([TOOL_DOT], [Define if we have found the dot tool])
  AC_PATH_PROG(TOOL_DOT, dot, [no])
  case $TOOL_DOT in
    no)
      dnl Nothing
      dot_was_found=false
      ;;    
    *)   
      AC_DEFINE([HAVE_DOT], [], [Defines if the dot tool was found])
      AC_DEFINE(HAVE_DOT)
      dot_was_found=true
      ;;
  esac  
  AM_CONDITIONAL(DOT_FOUND, test x$dot_was_found = xtrue)
])