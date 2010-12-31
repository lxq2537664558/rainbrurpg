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
include(m4sugar/m4sugar.m4)
include(m4sugar/m4sh.m4)
m4_divert(1000)dnl Needed so output something
dnl m4_define([UML_DEBUG], [1])
dnl
dnl Only populate the dot graph header
dnl
dnl Takes no arguments
dnl
m4_define([GRAPH_HEADER], [dnl
  fontname = "Bitstream Vera Sans"
  fontsize = 8

  node [[
    fontname = "Bitstream Vera Sans"
    fontsize = 8
    shape = "record"
    style = "filled"
    fillcolor = "#FFFFFF"
  ]]

  edge [[
    fontname = "Bitstream Vera Sans"
    fontsize = 8
    arrowhead = "ediamond"
  ]]

])
dnl
dnl Declares a class in the UML diagram
dnl
dnl Parameters:
dnl   $1 The class name
dnl   $2 List of members
dnl   $3 List of functions
dnl   $4 An optional text added at the end of the class name (used 
dnl      for templates)
m4_define([class], [dnl
  $1 [[
    label = < <table width = "100%" border="0" align="left" CELLPADDING="0" CELLSPACING="0">
	 <TR><td align="center" CELLPADDING="5">
	   <FONT POINT-SIZE="10">$1 $4</FONT>
	 </td></TR>
	 $2         
	 $3
	 </table> >
    margin = 0, 0
  ]]
])
dnl
dnl Declares members or functions of a class
dnl
dnl An issue can produce an error whith some members containing commas (,).
dnl Please replace commas with &#44; HTML code.
dnl
dnl $1 A list of members
dnl
m4_define([members], [dnl
  <TR><TD><table width = "100%" border="1" CELLPADDING="0" CELLSPACING="2"
    m4_ifdef([UML_DEBUG], [bgcolor="red"], [])
  >
  m4_foreach([var], $1,dnl
  <!-- 'var' member defifinition -->
  <TR><td align="left" border="0" CELLPADDING="0" CELLSPACING="0">var</td></TR>
  )
  </table>
  </TD>
  </TR>
])

dnl
dnl Declares a member virtual
dnl
dnl Please ensure you quote the member with ([ and ]) to
dnl avoid m4 complaining about 'end of file in argument list'.
dnl
m4_define([virtual], [dnl
<FONT FACE="DejaVu italic">$1</FONT>
])

dnl
dnl Define a member property (as a comment) in curly brackets
dnl
dnl $1 The property text
m4_define([PROP], [dnl
  &#123; $1 &#125;
])dnl

dnl
dnl Defines a note linked an entity
dnl
dnl Dot does not support word wrap, so if you need multi lines
dnl you chould use </BR>
dnl 
dnl $1 The entity's name
dnl $2 The comment as a list of lines
dnl
m4_define([note], [dnl
  node [[
    shape = "note"
    style = "filled"
    fillcolor = "#FFFFCC"
  ]]
	
  edge [[
    arrowhead = "none"
    style = "dotted"
  ]]

  $1_Comment [[
    label = <
      <table width = "100%" border="0" CELLPADDING="0" CELLSPACING="2" align="left"><tr><td>
$2
      </td></tr></table>
    >
  ]]

  $1_Comment -> $1 [constraint = false]

  GRAPH_HEADER
])
dnl
dnl Defines a relation
dnl
dnl $1 entity
dnl $2 entity to be linked to $1
m4_define([relation],[dnl
  edge [[
    arrowtail = "empty"
    arrowhead = "none"
    style = "solid"
  ]]
  $1 -> $2
])
dnl
dnl Defines a relation
dnl
dnl $1 entity
dnl $2 entity to be linked to $1
m4_define([relation_m],[dnl
  edge [[
    arrowtail = "empty"
    arrowhead = "none"
    style = "solid"
  ]]
  node [[
     shape = "none"    
  ]]
  /// HERE
  m4_foreach([myvar], [$2], [
    $1 -> myvar;
  ])
])
dnl
dnl Defines an implemented class
dnl
dnl   $1 The class name
dnl   $2 List of members
dnl   $3 List of functions
dnl   $4 An optional text added at the end of the class name (used 
dnl      for templates)
dnl
m4_define([implemented_class], [dnl
  node [[
    shape = "record"
    style = "filled"
    fillcolor = "#DDDDDD"
  ]]
	
  class([$1], [$2], [$3], [$4])

  GRAPH_HEADER
])
