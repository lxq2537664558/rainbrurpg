#  Copyright 2006-2012 Jerome PASQUIER
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

# The final program is called "myapp"
bin_PROGRAMS = rainbrurpg-tools-ftpclient

#add_libs = $(shell pkg-config --libs glib-2.0 sigc++-2.0)

rainbrurpg_tools_ftpclient_LDADD = -L$(top_srcdir)/common/.libs \
				   -lrainbrurpg-common 		\
				   $(GLIB_LIBS)			\
				   $(SIGC_LIBS)			\
				   $(GNET_LIBS)

INCLUDES = -I$(top_srcdir)/common 		\
	   $(GLIB_CFLAGS)			\
	   $(SIGC_CFLAGS)			\
	   $(GNET_CFLAGS)

rainbrurpg_tools_ftpclient_SOURCES = main.cpp			\
				     ftpclientwindow.cpp