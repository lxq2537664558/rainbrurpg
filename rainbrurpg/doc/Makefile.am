#  Copyright 2006-2010 Jerome PASQUIER
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

# This makefile generates PNG images from text files using the dot tool.
# The dot tool should be automatically foung by the configure script

SOURCES=

if DOT_FOUND
  SOURCES+=ogregui-uml.png

endif 

# Defines the dot suffixe
SUFFIXES = .dot

all: $(SOURCES)


# Reminder for internal vars
# $@ The target name
# $< First dependency name
# $^ Dependencies list
# $? List of deps most recent than target
# $* File name without suffix
.dot.png: $*.dot.in
	$(TOOL_M4) -I ../m4/ -I /usr/share/autoconf $*.dot.in > $*.dot
	$(TOOL_DOT) -T png -o $*.png $*.dot


clean-local:
	rm -fr $(SOURCES)