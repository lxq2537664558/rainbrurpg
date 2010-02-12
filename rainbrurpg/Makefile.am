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

# To make the HTML version of the texinfo help
# You need the texinfo package

# The sources
SUBDIRS = po ext common maincore ogreGui client

# The data files
SUBDIRS+= config data media mapdata

# Bug ?
# RainbruRPG.html

if BUILD_LIB_DESIGN
  SUBDIRS+=design
endif

if RB_OPTION_EDITOR_FLAGS
  SUBDIRS+=editor
endif

if RB_OPTION_SERVER_FLAGS
  SUBDIRS+=server
endif

if RB_OPTION_TOOLS_FLAGS
  SUBDIRS+=tools
endif

if RB_OPTION_TESTS_FLAGS
  SUBDIRS+=tests
endif

if RB_OPTION_EXAMPLES_FLAGS
  SUBDIRS+=examples
endif

if RB_OPTION_TAPI_FLAGS
  SUBDIRS+=terminalapi
endif

if RB_OPTION_ALL_FLAGS
  SUBDIRS+=terminalapi editor server tools tests examples
endif 

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = terminalapi-1.0.pc

EXTRA_DIST= config.rpath m4/ChangeLog RainbruRPG.lsm.in  \
	   RainbruRPG.texinfo \
	   RainbruRPG.spec.in \
	   Doxyfile

#  if you write a self-test script named `chk', uncomment the
#  following and add `chk' to the EXTRA_DIST list
#TESTS=chk

#  build and install the .info pages
info_TEXINFOS = RainbruRPG.texinfo
RainbruRPG_TEXINFOS = gpl.texinfo

#  install the man pages
man_MANS=RainbruRPG.6        \
	 RainbruRPG-server.6 \
	 RainbruRPG-editor.6

ACLOCAL_AMFLAGS = -I m4
