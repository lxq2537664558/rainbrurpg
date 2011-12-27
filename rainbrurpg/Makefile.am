#  Copyright 2006-2011 Jerome PASQUIER
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

# To make the HTML version of the texinfo help
# You need the texinfo package

# The sources
SUBDIRS = doc po ext src

# The data files
SUBDIRS+= config data media mapdata

# Bug ?
# RainbruRPG.html

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = terminalapi-1.0.pc

EXTRA_DIST= config.rpath m4/ChangeLog RainbruRPG.lsm.in  \
	   RainbruRPG.info 				 \
	   RainbruRPG.spec.in				 \
	   Doxyfile

#  if you write a self-test script named `chk', uncomment the
#  following and add `chk' to the EXTRA_DIST list
#TESTS=chk

#  build and install the .info pages
info_TEXINFOS = RainbruRPG.texi
RainbruRPG_TEXINFOS = gpl.texi

#  install the man pages
man_MANS=RainbruRPG.6        \
	 RainbruRPG-server.6 \
	 RainbruRPG-editor.6

ACLOCAL_AMFLAGS = -I m4
