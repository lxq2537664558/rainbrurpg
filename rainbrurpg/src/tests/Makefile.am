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

# The final program is called "rainbrurpg-tests"
bin_PROGRAMS = rainbrurpg-tests

rainbrurpg_tests_LDADD = -L$(top_srcdir)/src/common/.libs		\
	                 -L$(top_srcdir)/src/terminalapi/.libs		\
			 -lrainbrurpg-common 				\
			 -lrainbrurpg-terminalapi 			\
			 $(GNET_LIBS)					\
			 $(RPG_LIB_ADD)					\
			 $(CPPUNIT_LIBS)				\
			 $(SIGC_LIBS)

# Defines the subdirectories of tests/ that contain individuals tests
#
# These directories are relative from src/tests/
# It is needed because each library's test suite will include his
# files from these directories
#
TESTS_DIRS = -Itapi/		\
	     -Icommon/

INCLUDES = -I$(top_srcdir)/ext/ 			\
	   -I$(top_srcdir)/src/common/ 			\
	   -I$(top_srcdir)/src/terminalapi/   		\
	   $(TESTS_DIRS)				\
	   $(GNET_CFLAGS) 				\
	   $(CPPUNIT_CFLAGS)				\
	   $(SIGC_CFLAGS)				\
	   -DTEXT_OUTPUT

rainbrurpg_tests_SOURCES = main.cpp			\
			   tapitestsuite.cpp		\
			   commontestsuite.cpp
