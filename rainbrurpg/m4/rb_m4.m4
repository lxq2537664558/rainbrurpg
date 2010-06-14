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


AC_DEFUN([RB_CHECK_M4],[
  AC_ARG_VAR([TOOL_M4], [Define the path to the m4 executable])
  AC_PATH_PROG(TOOL_M4, m4, [no])
  case $TOOL_M4 in
    no)
      dnl Nothing
      m_was_found=false
      ;;    
    *)   
      AC_DEFINE([HAVE_M4], [], [Defines if the m4 tool was found])
      AC_DEFINE(HAVE_M4)
      m_was_found=true
      ;;
  esac  
  AM_CONDITIONAL(M4_FOUND, test x$m_was_found = xtrue)
])
