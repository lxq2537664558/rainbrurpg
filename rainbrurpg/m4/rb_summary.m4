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


AC_DEFUN([RB_SUMMARY],
[
echo
echo "------------------------------------------------------------------------"
echo "$PACKAGE v$VERSION-$RELEASE configuration summary"
echo "------------------------------------------------------------------------"
echo
echo "Extra modules:"
echo "  Server.......................${build_server}"
echo "  Unit tests...................${build_tests}"
echo "  Editor.......................${build_editor}"
echo "  Tools........................${build_tools}"
echo "  Examples.....................${build_examples}"
echo
echo "Optional libraries:"
echo "  TerminalAPI (deprecated).....${build_tapi}"
echo
echo "OgreGui configuration:"
echo "  Dirty-flag...................${dirty_flag}"
echo
echo "Tools:"
echo "  dot..........................${TOOL_DOT}"
echo "  m4...........................${TOOL_M4}"
])