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

# This is a 'libtool convenience library' containing some helpers that can be
# used in unit tests.

noinst_LTLIBRARIES = libtesthelpers.la 

libtesthelpers_ladir = $(includedir)/testhelpers
libtesthelpers_la_HEADERS = 	\
  OgreMinimalSetup.hpp

libtesthelpers_la_SOURCES =  	\
  OgreMinimalSetup.cpp

library_includedir=$(includedir)/$(GENERIC_LIBRARY_NAME)/$(LIB_COMMON_NAME)
library_include_HEADERS = $(h_sources)
INCLUDES = -I$(top_srcdir)/src/common/		\
	   -I$(top_srcdir)/src/maincore/	\
	   $(OGRE_CFLAGS)			\
	   $(CFLAGS)

libtesthelpers_la_LIBADD = $(OGRE_LIBS) $(LDFLAGS)

# Dummy render system
pkg_LTLIBRARIES = RenderSystem_Dummy.la
pkgdir=$(prefix)/lib/OGRE/
RenderSystem_Dummy_la_SOURCES = DummyRenderSystem.cpp
RenderSystem_Dummy_la_LDFLAGS = -module -avoid-version
RenderSystem_Dummy_la_LIBTOOLFLAGS = --tag=disable-static

# The executable created here is just used for memory checking using `valgrind`
bin_PROGRAMS=ogreminimalsetup
ogreminimalsetup_SOURCES=main.cpp
ogreminimalsetup_LDADD= libtesthelpers.la $(OGRE_LIBS)

# Boost.Test based unit tests
bin_PROGRAMS+=rainbrurpg-tests-libtesthelpers
TESTS=rainbrurpg-tests-libtesthelpers
rainbrurpg_tests_libtesthelpers_SOURCES= \
	OgreMinimalSetupTest.cpp	 \
	main-tests.cpp
rainbrurpg_tests_libtesthelpers_LDADD= libtesthelpers.la $(OGRE_LIBS)